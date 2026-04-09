# CS351_ProjectB_CSV-Mini-Database-Query-Engine

This project is for Yuan Ze University CS351 "Artificial Intelligence Agile Development" Mini project.

A lightweight CSV mini-database and query engine. Built to explore robust CSV parsing, custom indexing mechanisms, simple query grammars, and system performance trade-offs.

## Project Overview

This project is designed for Yuan Ze University course CS351 "Artificial Intelligence Agile Development". The goal is to build a lightweight CSV mini-database and query engine, implementing core concepts of database systems through hands-on development, including:

- **Robust CSV Parsing**: Handling various CSV file formats, including quoted fields, line breaks, and edge cases.
- **Custom Indexing Mechanisms**: Designing and implementing efficient index structures to accelerate query operations.
- **Simple Query Grammar**: Defining a simple query language supporting basic operations like SELECT, WHERE, JOIN.
- **System Performance Trade-offs**: Analyzing the performance impact of different design choices, such as memory usage vs. query speed.

## Project Goals

1. **Learn Database Internals**: Gain deep understanding of database operations by implementing a mini version.
2. **Explore Performance Optimization**: Compare the performance differences between various indexing strategies and query optimization techniques.
3. **Implement Query Engine**: Design a simple yet functional query processor.
4. **Handle Real-World Data**: Use CSV as data source to process actual datasets.

## Features

### Core Features
- **CSV File Loading**: Support loading multiple CSV files as data tables.
- **Table Management**: Create, delete, and modify table structures.
- **Query Processing**:
  - SELECT statements: Select specific fields
  - WHERE clauses: Conditional filtering
  - JOIN operations: Multi-table joins
  - GROUP BY and aggregate functions: Grouping and statistics
- **Index Support**: Create B-Tree or hash indexes for fields to speed up queries.

### Advanced Features
- **Query Optimization**: Automatically select the best execution plan.
- **Performance Monitoring**: Log query execution time and resource usage.
- **Error Handling**: Robust error handling with user-friendly error messages.

## System Architecture

### Main Components
1. **Parser**: Responsible for parsing CSV files and query syntax.
2. **Storage Engine**: Manages data storage and indexing.
3. **Query Optimizer**: Selects the optimal query execution plan.
4. **Execution Engine**: Executes queries and returns results.
5. **Interface Layer**: Provides command-line or simple GUI interface.

### Data Structures
- **Table**: Column-based storage, each column containing multiple fields.
- **Index**: Support for B-Tree and hash indexes.
- **Query Plan**: Tree structure representing query execution order.

## Technical Implementation

### Programming Language
- Primarily using C++ or Java (based on course requirements).
- May integrate Python for prototyping or testing.

### Key Technologies
- **CSV Parsing**: Implement state machine or use existing libraries.
- **Index Implementation**: Custom B-Tree or use standard libraries.
- **Query Parsing**: Use recursive descent parser or parser generator.
- **Memory Management**: Efficient memory allocation and garbage collection.

### Performance Considerations
- **Time Complexity**: Analyze time complexity of different operations.
- **Space Complexity**: Optimize memory usage.
- **I/O Optimization**: Reduce disk access frequency.

## Development Plan

### Phase 1: Foundation (Week 1-2)
- Design system architecture
- Implement basic CSV parser
- Establish table structures

### Phase 2: Core Features (Week 3-4)
- Implement query parser
- Add basic query operations (SELECT, WHERE)
- Create simple indexing mechanism

### Phase 3: Advanced Features (Week 5-6)
- Add JOIN and aggregation operations
- Implement query optimizer
- Performance testing and optimization

### Phase 4: Testing and Documentation (Week 7-8)
- Write unit tests
- Performance benchmarking
- Complete project report

## Usage

### Installation and Setup
1. Clone the project: `git clone [repository URL]`
2. Build the program: `make` or appropriate build command
3. Run the program: `./csv_db`

### Basic Usage
```bash
# Load CSV file
LOAD TABLE users FROM 'users.csv'

# Execute query
SELECT name, age FROM users WHERE age > 18
```

### Example Queries
- Simple select: `SELECT * FROM table1`
- Conditional filter: `SELECT name FROM users WHERE city = 'Taipei'`
- Join operation: `SELECT u.name, o.amount FROM users u JOIN orders o ON u.id = o.user_id`

## Testing and Evaluation

### Performance Metrics
- Query execution time
- Memory usage
- Index build time
- Query processing throughput

### Test Datasets
- Use public CSV datasets for testing
- Compare performance across different dataset sizes

## Contributing

1. Fork this project
2. Create feature branch: `git checkout -b feature/new-feature`
3. Commit changes: `git commit -m 'Add new feature'`
4. Push branch: `git push origin feature/new-feature`
5. Create Pull Request

## References

- Database System Concepts - Silberschatz et al.
- CSV Format Specification (RFC 4180)
- B-Tree Data Structure Papers

## License

This project is for academic purposes, licensed under MIT.
