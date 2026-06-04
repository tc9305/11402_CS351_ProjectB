# Project B: CSV Mini Database

## Overview

This project is a simple command-line CSV mini database implemented in C++.

The goal of this project is to simulate basic database operations using a CSV file as the data source. The program can load CSV data, display records, select specific columns, filter records with simple conditions, add new rows, and save the updated data back to the CSV file.

This project was developed as part of the CS351 AI-Assisted Software Development course.

---

## Implemented Features

The current version supports the following features:

* Load data from a CSV file
* Display all records
* Select specific columns
* Filter records using simple `WHERE` conditions
* Add a new row to the table
* Save updated data back to a CSV file
* Basic error handling for invalid commands, missing files, and unknown columns

---

## Project Structure

```text
11402_CS351_ProjectB/
├── data/
│   └── students.csv
├── src/
│   └── main.cpp
├── .gitignore
└── README.md
```

---

## Sample CSV Data

The sample CSV file is located at:

```text
data/students.csv
```

Example data:

```csv
id,name,age,major,city
1,Alice,20,CS,Taipei
2,Bob,17,EE,Taoyuan
3,Charlie,22,CS,Taipei
4,Diana,19,IM,New Taipei
5,Evan,16,CS,Hsinchu
```

---

## How to Compile

Use the following command to compile the program:

```bash
g++ -std=c++17 src/main.cpp -o csv_db
```

---

## How to Run

### Windows PowerShell

```powershell
.\csv_db
```

### macOS / Linux

```bash
./csv_db
```

After running the program, the command prompt will appear:

```text
CSV Mini Database
Type HELP to see available commands.
db>
```

---

## Supported Commands

### Show Help

```text
HELP
```

### Load CSV File

```text
LOAD data/students.csv
```

### Display All Records

```text
SELECT *
```

### Select Specific Columns

```text
SELECT name, age
```

### Filter Records

```text
SELECT * WHERE age = 20
SELECT * WHERE name = 'Alice'
SELECT name, age WHERE major = CS
SELECT * WHERE age > 18
```

### Add a New Row

```text
ADD 6,Frank,21,CS,Taipei
```

### Save Data

```text
SAVE data/students.csv
```

### Exit Program

```text
EXIT
```

---

## Demo Script

The following commands can be used during the final demo:

```text
LOAD data/students.csv
SELECT *
SELECT * WHERE age = 20
SELECT * WHERE name = 'Alice'
SELECT name, age WHERE major = CS
ADD 6,Frank,21,CS,Taipei
SELECT *
SAVE data/students.csv
EXIT
```

---

## Example Output

Example command:

```text
SELECT * WHERE age = 20
```

Example output:

```text
id        name      age       major     city
----------------------------------------------------
1         Alice     20        CS        Taipei
1 row(s) returned.
```

---

## Testing

The following test cases were used to verify the program:

| Test Case               | Command                         | Expected Result                            |
| ----------------------- | ------------------------------- | ------------------------------------------ |
| Load valid CSV file     | `LOAD data/students.csv`        | CSV file is loaded successfully            |
| Display all records     | `SELECT *`                      | All rows and columns are displayed         |
| Select specific columns | `SELECT name, age`              | Only selected columns are displayed        |
| Filter numeric value    | `SELECT * WHERE age = 20`       | Only records with age 20 are displayed     |
| Filter string value     | `SELECT * WHERE name = 'Alice'` | Only Alice's record is displayed           |
| Add new row             | `ADD 6,Frank,21,CS,Taipei`      | One new row is added                       |
| Save data               | `SAVE data/students.csv`        | Updated data is saved back to the CSV file |
| Invalid column          | `SELECT score`                  | Error message is displayed                 |
| Invalid file            | `LOAD wrong.csv`                | Error message is displayed                 |

---

## Error Handling

The program includes basic error handling for:

* Loading a file that does not exist
* Using a command before loading a CSV file
* Selecting an unknown column
* Using an invalid `WHERE` condition
* Adding a row with the wrong number of values
* Entering an unknown command

Example:

```text
LOAD wrong.csv
```

Output:

```text
Error: Cannot open file: wrong.csv
```

---

## Current Limitations

This project is a simplified mini database, so it does not support all SQL features.

Current limitations:

* It only supports one loaded CSV file at a time
* It does not support full SQL syntax
* It does not support `JOIN`
* It does not support `GROUP BY`
* It does not support `UPDATE` or `DELETE`
* It does not include indexing or query optimization yet

---

## Future Improvements

Possible future improvements include:

* Support `DELETE` command
* Support `UPDATE` command
* Support more SQL-like syntax such as `INSERT INTO`
* Support multiple tables
* Add indexing for faster search
* Add automated tests
* Add GitHub Actions for continuous integration

---

## GitHub Workflow

GitHub was used to manage the development process.

The workflow includes:

* Creating and updating project files
* Tracking changes with commits
* Using `.gitignore` to exclude compiled files
* Keeping source code, sample data, and documentation organized

This commit history provides evidence of the development process and project progress.

---

## AI-Assisted Development Reflection

AI tools were used during the development process to support requirement clarification, code structure planning, debugging, and README documentation.

AI helped me:

* Break down the project requirements into smaller tasks
* Design the basic command-line interface
* Generate an initial C++ implementation
* Improve error handling
* Prepare demo commands and documentation

However, AI-generated suggestions were not used directly without testing. I manually compiled and ran the program, checked the output, and fixed issues such as command syntax and CSV formatting.

Through this project, I learned that AI can speed up software development, but the developer still needs to verify the result, test edge cases, and make sure the program actually works.

---

## Conclusion

This project demonstrates a basic CSV mini database using C++.

The final version can load CSV data, display records, filter records, add new data, and save the result. Although it is not a full SQL database, it shows the basic ideas of data loading, querying, data manipulation, file saving, and error handling.
