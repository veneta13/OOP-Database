#include "database.hpp"

/// Default constructor
Database::Database() {
    count = 0;
    capacity = 5;
    tables = new Table*[capacity];
}


/// Copy constructor
/// \param other object to copy
Database::Database(Database const &other) {
    count = 0;
    copy(other);
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
Database &Database::operator=(Database const &other) {
    if (this != &other) {
        count = 0;
        copy(other);
    }
    return *this;
}


/// Destructor
Database::~Database() {
    clear();
}


/// Clear database
void Database::clear() {
    if (tables) {
        for (int i = 0; i < count; i++) {
            delete tables[i];
        }
    }

    delete[] tables;
    tables = nullptr;
    count = 0;
}


/// Double the capacity of the database
void Database::expand() {
    capacity *= 2;
    Table** temp = new Table*[capacity];

    for (int i = 0; i < count; i++) {
        temp[i] = tables[i];
    }

    delete[] tables;
    tables = temp;
}


/// Copy database
/// \param other Database to copy from
void Database::copy(Database const &other) {
    clear();
    count = other.count;
    capacity = other.capacity;

    tables = new Table*[capacity];

    for (int i = 0; i < count; i++) {
        tables[i] = new Table(*other.tables[i]);
    }
}


/// Search for table in database by name
/// \param name name to search by
/// \return index if the table if found, else -1
int Database::getTableByName(const char *name) const {
    for (int i = 0; i < count; i++) {
        if (strcmp(tables[i]->getName(), name) == 0) {
            return i;
        }
    }
    return -1;
}


/// Read table rows from file
/// \param in stream to read from
/// \param table table to save in
/// \param columns number of columns
/// \param rows number of rows
void Database::readRows(std::istream& in, Table* table, int columns, int rows) {
    for (int i = 0; i < rows; i++) {
        Value** values = new Value*[columns];

        for (int j = 0; j < columns; j++) {
            std::string line;
            std::getline(in, line);

            if (line == "NULL") {
                values[j] = new NullValue();
                continue;
            }

            std::istringstream linestr(line);
            if (table->getColumnType(j) == ColumnType::Integer) {
                int temp;
                linestr >> temp;
                values[j] = new IntegerValue(temp);
            }
            else if (table->getColumnType(j) == ColumnType::FloatingPoint) {
                double temp;
                linestr >> temp;
                values[j] = new FloatValue(temp);
            }
            else {
                values[j] = new StringValue(line.c_str());
            }
        }

        table->insertRow(values);
        for (int j = 0; j < columns; j++) {
            delete values[j];
        }
        delete[] values;
    }
}


/// Import table from file
/// \param in stream to read table information from
/// \return if the import was successful
bool Database::importTable(std::istream &in) {
    std::string name;
    getline(in, name);
    Table* table = new Table(name.c_str());

    int rows, columns;
    in >> columns >> rows;

    for (int i = 0; i < columns; i++) {
        int columnType;
        in >> columnType;
        if (!(columnType == 1 || columnType == 2 || columnType == 3)) {
            delete table;
            return false;
        }
        table->addColumn((ColumnType)columnType);
    }

    in.ignore();
    readRows(in, table, columns, rows);

    if (addTable(table)) {
        return true;
    }
    delete table;
    return false;
}


/// Export table information
/// \param out stream to export into
/// \param tableName name of the table to export
/// \return if the export was successful
bool Database::exportTable(std::ostream &out, char const *tableName) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    out << (*tables[tableIndex]);
    return true;
}

void Database::showTables(std::ostream &out) {
    out << "TABLES IN DATABASE:\n";
    for (int i = 0; i < count; i++) {
        out << tables[i]->getName() << "\n";
    }
}


/// Print information about the column types of a table
/// \param out stream to input result in
/// \param tableName name of the table to get information about
/// \return if such table exists in the database
bool Database::describe(std::ostream &out, const char* tableName) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    tables[tableIndex]->describe(out);
    return true;
}


/// Getter for count
/// \return the value of count
int Database::countTables() const {
    return count;
}


/// Getter for table name
/// \param index index of the table
/// \return name of the table
char* Database::getTableName(int index) const {
    return tables[index]->getName();
}


/// Print table by pages
/// \param out stream to input into
/// \param in stream to read user input from
/// \param tableName table to print
/// \return if the printing was successful
bool Database::printByPages(std::ostream &out, std::istream &in, const char* tableName) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    int page = 0;
    while (true) {
        tables[tableIndex]->showPage(out, 10, page);
        out << "Enter: 1 - next page | 2 - previous page | [] - quit\n";
        int input;
        in >> input;
        in.ignore();
        if (input == 1) { page++; }
        else if (input == 2) { page--; }
        else { return true; }
    }
}


/// Print all rows of a table containing a value in a specific column
/// \param out stream to input into
/// \param in stream to read user input from
/// \param tableName table to search in
/// \param columnIndex column to search in
/// \param value
/// \return if the printing was successful
bool Database::select(std::ostream &out, std::istream& in, char const *tableName, int columnIndex, Value* value) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    DynamicArray<int> indexes;
    tables[tableIndex]->selectElement(columnIndex, indexes, value);

    int page = 0;
    while (true) {
        tables[tableIndex]->showPage(out, indexes, 10, page);
        out << "Enter: 1 - next page | 2 - previous page | [] - quit\n";
        int input;
        in >> input;
        if (input == 1) { page++; }
        else if (input == 2) { page--; }
        else { break; }
    }
    return true;
}


/// Update rows containing a certain value
/// \param tableName table in search in
/// \param searchCol column to search in
/// \param searchVal value to search for
/// \param replaceCol column to replace in
/// \param replaceVal value to replace with
/// \return if the update was successful
bool Database::update(char const *tableName, int searchCol, Value *searchVal, int replaceCol, Value *replaceVal) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    DynamicArray<int> indexes;
    tables[tableIndex]->selectElement(searchCol, indexes, searchVal);
    tables[tableIndex]->updateElements(replaceCol, replaceVal, indexes);
    return true;
}


/// Delete all rows containing a value in a certain column
/// \param tableName table to search in
/// \param columnIndex column to search in
/// \param value value to search for
/// \return if the deletion was successful
bool Database::deleteRows(char const *tableName, int columnIndex, Value *value) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    tables[tableIndex]->deleteElement(columnIndex, value);
    return true;
}


/// Add table to database
/// \param table pointer to a table
/// \return if the table was added successfully
bool Database::addTable(Table* table) {
    if (getTableByName(table->getName()) != -1) {
        return false;
    }

    if (count == capacity) { expand(); }
    tables[count] = table;
    count++;
    return true;
}


/// Insert a new row in a table
/// \param tableName table to insert in
/// \param values values in the row
bool Database::insert(char const *tableName, Value **values) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }
    tables[tableIndex]->insertRow(values);
    return true;
}


/// Add an empty column to table
/// \param in stream to read user input from
/// \param out stream to output prompts for user into
/// \param tableName table to add column to
/// \return if the column was added successfully
bool Database::addColumn(std::istream& in, std::ostream& out,const char* tableName) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    int type;
    out << "Choose column type of the new column:\n"
        << "1 - Integer\n"
        << "2 - Floating Point\n"
        << "3 - String\n";
    in >> type;

    tables[tableIndex]->addColumn((ColumnType)type);
    return true;
}


/// Perform inner join
/// \param table1 first table to join
/// \param column1 column to join by in the first table
/// \param table2 second table to join
/// \param column2 column to join by in the second table
/// \return if the join was successful
bool Database::innerJoin(std::ostream& out, char const *table1, int column1, char const *table2, int column2) {
    int tableIndex1 = getTableByName(table1);
    int tableIndex2 = getTableByName(table2);

    if (tableIndex1 == -1 || tableIndex2 == -1) { return false; }

    Table* joinedTable= tables[tableIndex1]->innerJoin(*tables[tableIndex2], column1, column2);
    if (addTable(joinedTable)) {
        out << "NAME OF JOINED TABLE: " << joinedTable->getName() << "\n";
        return true;
    }
    delete joinedTable;
    return false;
}


/// Perform an operation in table on all rows containing a value in a certain column
/// \param out stream to insert result into
/// \param tableName name of the table
/// \param searchCol column to search for value in
/// \param value value to search for
/// \param aggregCol column to perform operation on
/// \param operation operation to perform
/// \return if such table exists
bool Database::aggregate(std::ostream &out, char const *tableName, int searchCol, Value* value, int aggregCol, Operations operation) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { return false; }

    DynamicArray<int> indexes;
    tables[tableIndex]->selectElement(searchCol, indexes, value);

    switch (operation) {
        case Sum:
            tables[tableIndex]->sum(out, aggregCol, indexes);
            break;
        case Product:
            tables[tableIndex]->product(out, aggregCol, indexes);
            break;
        case Maximum:
            tables[tableIndex]->maximum(out, aggregCol, indexes);
            break;
        case Minimum:
            tables[tableIndex]->minimum(out, aggregCol, indexes);
            break;
    }
    return true;
}


/// Change the name of a table
/// \param oldName old name of the table
/// \param newName updated name of the table
/// \return if the update was successful
bool Database::rename(char const *oldName, char const *newName) {
    int oldNameIndex = getTableByName(oldName);
    int newNameIndex = getTableByName(newName);

    if (oldNameIndex == -1 || newNameIndex != -1) {
        return false;
    }

    tables[oldNameIndex]->setName(newName);
    return true;
}


/// Getter for column type
/// \param tableName name of table to search in
/// \param columnIndex index of the column
/// \return type of the column
ColumnType Database::getColumnType(char const *tableName, int columnIndex) {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { throw std::invalid_argument("Invalid table"); }

    return tables[tableIndex]->getColumnType(columnIndex);
}


/// Count rows containing a value
/// \param tableName table to search in
/// \param columnIndex column to search in
/// \param value value to search for
/// \return count of rows
int Database::countRows(const char* tableName, int columnIndex, Value* value) const {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { throw std::invalid_argument("Invalid table"); }

    return tables[tableIndex]->countRows(columnIndex, value);
}


/// Getter for column count
/// \param tableName table to search in
/// \return number of columns
int Database::countColumns(char const *tableName) const {
    int tableIndex = getTableByName(tableName);
    if (tableIndex == -1) { throw std::invalid_argument("Invalid table"); }

    return tables[tableIndex]->countColumns();
}
