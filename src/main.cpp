#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Table {
    vector<string> headers;
    vector<vector<string>> rows;
    string loadedFile;
};

string trim(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

string toUpper(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return static_cast<char>(toupper(c));
    });
    return text;
}

bool startsWithIgnoreCase(const string& text, const string& prefix) {
    if (text.size() < prefix.size()) return false;
    return toUpper(text.substr(0, prefix.size())) == toUpper(prefix);
}

string removeOuterQuotes(string value) {
    value = trim(value);

    if (value.size() >= 2) {
        char first = value.front();
        char last = value.back();

        if ((first == '\'' && last == '\'') || (first == '"' && last == '"')) {
            return value.substr(1, value.size() - 2);
        }
    }

    return value;
}

vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            fields.push_back(trim(field));
            field.clear();
        } else {
            field += c;
        }
    }

    fields.push_back(trim(field));
    return fields;
}

string escapeCSVField(const string& value) {
    bool needQuotes = value.find(',') != string::npos ||
                      value.find('"') != string::npos ||
                      value.find('\n') != string::npos;

    if (!needQuotes) return value;

    string escaped = "\"";

    for (char c : value) {
        if (c == '"') {
            escaped += "\"\"";
        } else {
            escaped += c;
        }
    }

    escaped += "\"";
    return escaped;
}

int findColumnIndex(const Table& table, const string& columnName) {
    for (size_t i = 0; i < table.headers.size(); ++i) {
        if (table.headers[i] == columnName) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool isTableLoaded(const Table& table) {
    return !table.headers.empty();
}

bool loadCSV(const string& filename, Table& table) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open file: " << filename << endl;
        return false;
    }

    Table newTable;
    newTable.loadedFile = filename;

    string line;

    if (!getline(file, line)) {
        cout << "Error: CSV file is empty." << endl;
        return false;
    }

    newTable.headers = parseCSVLine(line);

    while (getline(file, line)) {
        if (trim(line).empty()) continue;

        vector<string> row = parseCSVLine(line);

        if (row.size() != newTable.headers.size()) {
            cout << "Warning: skipped a row because column count does not match header." << endl;
            continue;
        }

        newTable.rows.push_back(row);
    }

    table = newTable;

    cout << "Loaded " << table.rows.size() << " row(s) from " << filename << endl;
    return true;
}

bool saveCSV(const string& filename, const Table& table) {
    if (!isTableLoaded(table)) {
        cout << "Error: No CSV file loaded. Use LOAD <filename> first." << endl;
        return false;
    }

    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot write file: " << filename << endl;
        return false;
    }

    for (size_t i = 0; i < table.headers.size(); ++i) {
        if (i > 0) file << ",";
        file << escapeCSVField(table.headers[i]);
    }

    file << "\n";

    for (const auto& row : table.rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (i > 0) file << ",";
            file << escapeCSVField(row[i]);
        }

        file << "\n";
    }

    cout << "Saved " << table.rows.size() << " row(s) to " << filename << endl;
    return true;
}

vector<int> getSelectedColumns(const Table& table, const string& selectPart) {
    vector<int> selectedColumns;
    string part = trim(selectPart);

    if (part == "*") {
        for (size_t i = 0; i < table.headers.size(); ++i) {
            selectedColumns.push_back(static_cast<int>(i));
        }

        return selectedColumns;
    }

    stringstream ss(part);
    string columnName;

    while (getline(ss, columnName, ',')) {
        columnName = trim(columnName);

        int index = findColumnIndex(table, columnName);

        if (index == -1) {
            cout << "Error: Unknown column: " << columnName << endl;
            return {};
        }

        selectedColumns.push_back(index);
    }

    return selectedColumns;
}

void printRows(const Table& table, const vector<int>& columns, const vector<vector<string>>& rows) {
    if (columns.empty()) return;

    vector<size_t> widths;

    for (int columnIndex : columns) {
        size_t width = table.headers[columnIndex].size();

        for (const auto& row : rows) {
            if (columnIndex < static_cast<int>(row.size())) {
                width = max(width, row[columnIndex].size());
            }
        }

        widths.push_back(max<size_t>(width + 2, 10));
    }

    for (size_t i = 0; i < columns.size(); ++i) {
        cout << left << setw(static_cast<int>(widths[i])) << table.headers[columns[i]];
    }

    cout << endl;

    for (size_t width : widths) {
        cout << string(width, '-');
    }

    cout << endl;

    for (const auto& row : rows) {
        for (size_t i = 0; i < columns.size(); ++i) {
            int columnIndex = columns[i];
            string value = columnIndex < static_cast<int>(row.size()) ? row[columnIndex] : "";

            cout << left << setw(static_cast<int>(widths[i])) << value;
        }

        cout << endl;
    }

    cout << rows.size() << " row(s) returned." << endl;
}

bool isNumber(const string& value) {
    if (value.empty()) return false;

    char* endPointer = nullptr;
    strtod(value.c_str(), &endPointer);

    return *endPointer == '\0';
}

bool compareValues(const string& leftValue, const string& op, const string& rightValue) {
    if (isNumber(leftValue) && isNumber(rightValue)) {
        double leftNumber = stod(leftValue);
        double rightNumber = stod(rightValue);

        if (op == ">") return leftNumber > rightNumber;
        if (op == "<") return leftNumber < rightNumber;
        if (op == ">=") return leftNumber >= rightNumber;
        if (op == "<=") return leftNumber <= rightNumber;
        if (op == "=" || op == "==") return leftNumber == rightNumber;
        if (op == "!=") return leftNumber != rightNumber;
    } else {
        if (op == "=" || op == "==") return leftValue == rightValue;
        if (op == "!=") return leftValue != rightValue;
    }

    return false;
}

bool isValidOperator(const string& op) {
    return op == ">" ||
           op == "<" ||
           op == ">=" ||
           op == "<=" ||
           op == "=" ||
           op == "==" ||
           op == "!=";
}

vector<vector<string>> filterRowsByCondition(const Table& table, const string& condition, bool& success) {
    success = false;

    stringstream ss(condition);

    string columnName;
    string op;
    string value;

    ss >> columnName >> op;
    getline(ss, value);

    value = removeOuterQuotes(value);

    if (columnName.empty() || op.empty() || value.empty()) {
        cout << "Error: WHERE format should be: WHERE <column> <operator> <value>" << endl;
        return {};
    }

    if (!isValidOperator(op)) {
        cout << "Error: Unsupported operator: " << op << endl;
        return {};
    }

    int columnIndex = findColumnIndex(table, columnName);

    if (columnIndex == -1) {
        cout << "Error: Unknown column: " << columnName << endl;
        return {};
    }

    vector<vector<string>> filteredRows;

    for (const auto& row : table.rows) {
        if (columnIndex < static_cast<int>(row.size()) &&
            compareValues(row[columnIndex], op, value)) {
            filteredRows.push_back(row);
        }
    }

    success = true;
    return filteredRows;
}

void handleSelect(const Table& table, const string& command) {
    if (!isTableLoaded(table)) {
        cout << "Error: No CSV file loaded. Use LOAD <filename> first." << endl;
        return;
    }

    string queryPart = trim(command.substr(6));

    if (queryPart.empty()) {
        cout << "Error: SELECT requires columns. Example: SELECT *" << endl;
        return;
    }

    string upperQueryPart = toUpper(queryPart);
    size_t wherePosition = upperQueryPart.find(" WHERE ");

    string selectPart = queryPart;
    vector<vector<string>> rowsToPrint = table.rows;

    if (wherePosition != string::npos) {
        selectPart = trim(queryPart.substr(0, wherePosition));
        string condition = trim(queryPart.substr(wherePosition + 7));

        bool success = false;
        rowsToPrint = filterRowsByCondition(table, condition, success);

        if (!success) {
            return;
        }
    }

    vector<int> columns = getSelectedColumns(table, selectPart);
    printRows(table, columns, rowsToPrint);
}

void handleWhere(const Table& table, const string& command) {
    if (!isTableLoaded(table)) {
        cout << "Error: No CSV file loaded. Use LOAD <filename> first." << endl;
        return;
    }

    string condition = trim(command.substr(5));

    bool success = false;
    vector<vector<string>> filteredRows = filterRowsByCondition(table, condition, success);

    if (!success) {
        return;
    }

    vector<int> allColumns;

    for (size_t i = 0; i < table.headers.size(); ++i) {
        allColumns.push_back(static_cast<int>(i));
    }

    printRows(table, allColumns, filteredRows);
}

void handleAdd(Table& table, const string& command) {
    if (!isTableLoaded(table)) {
        cout << "Error: No CSV file loaded. Use LOAD <filename> first." << endl;
        return;
    }

    string valuesText = trim(command.substr(4));

    if (valuesText.empty()) {
        cout << "Error: ADD requires values. Example: ADD 6,Frank,21,CS,Taipei" << endl;
        return;
    }

    vector<string> values = parseCSVLine(valuesText);

    if (values.size() != table.headers.size()) {
        cout << "Error: ADD needs exactly " << table.headers.size() << " value(s)." << endl;
        cout << "Header columns: ";

        for (size_t i = 0; i < table.headers.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << table.headers[i];
        }

        cout << endl;
        return;
    }

    table.rows.push_back(values);
    cout << "Added 1 row." << endl;
}

void printHelp() {
    cout << "Commands:" << endl;
    cout << "  LOAD data/students.csv" << endl;
    cout << "  SELECT *" << endl;
    cout << "  SELECT name, age" << endl;
    cout << "  WHERE age > 18" << endl;
    cout << "  WHERE major = CS" << endl;
    cout << "  ADD 6,Frank,21,CS,Taipei" << endl;
    cout << "  SAVE data/students.csv" << endl;
    cout << "  HELP" << endl;
    cout << "  EXIT" << endl;
}

int main() {
    Table table;
    string command;

    cout << "CSV Mini Database" << endl;
    cout << "Type HELP to see available commands." << endl;

    while (true) {
        cout << "db> ";

        if (!getline(cin, command)) break;

        command = trim(command);

        if (command.empty()) continue;

        if (toUpper(command) == "EXIT" || toUpper(command) == "QUIT") {
            cout << "Bye!" << endl;
            break;
        } else if (toUpper(command) == "HELP") {
            printHelp();
        } else if (startsWithIgnoreCase(command, "LOAD ")) {
            string filename = trim(command.substr(5));
            loadCSV(filename, table);
        } else if (startsWithIgnoreCase(command, "SAVE")) {
            string filename = trim(command.substr(4));

            if (filename.empty()) {
                if (table.loadedFile.empty()) {
                    cout << "Error: Please provide a file name. Example: SAVE data/students.csv" << endl;
                } else {
                    saveCSV(table.loadedFile, table);
                }
            } else {
                saveCSV(filename, table);
            }
        } else if (startsWithIgnoreCase(command, "SELECT ")) {
            handleSelect(table, command);
        } else if (startsWithIgnoreCase(command, "WHERE ")) {
            handleWhere(table, command);
        } else if (startsWithIgnoreCase(command, "ADD ")) {
            handleAdd(table, command);
        } else {
            cout << "Error: Unknown command. Type HELP for command list." << endl;
        }
    }

    return 0;
}