#include "table.hpp"

/// Default constructor
Table::Table() {
    columnCount = 0;
    rowCount = 0;
    capacity = 5;
    name = nullptr;
    file = nullptr;
    columns = new TableColumn*[capacity];
}


/// Constructor with name
/// \param _count name of the table
Table::Table(char const* _name) {
    columnCount = 0;
    rowCount = 0;
    capacity = 5;

    name = new char[strlen(_name) + 1];
    strcpy(name, _name);

    file = nullptr;

    columns = new TableColumn*[capacity];
}


/// Constructor with name and file name
/// \param _count name of the table
/// \param _file file the table is saved in
Table::Table(char const* _name, char const* _file) {
    columnCount = 0;
    rowCount = 0;
    capacity = 5;

    name = new char[strlen(_name) + 1];
    strcpy(name, _name);

    file = new char[strlen(_file) + 1];
    strcpy(file, _file);

    columns = new TableColumn*[capacity];
}


/// Copy constructor
/// \param other object to copy
Table::Table(Table const &other) {
    columnCount = 0;
    copy(other);
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
Table &Table::operator=(Table const &other) {
    if (this != &other) {
        columnCount = 0;
        copy(other);
    }
    return *this;
}


/// Destructor
Table::~Table() {
    clear();
}


/// Clear table
void Table::clear() {
    if (columns) {
        for (int i = 0; i < columnCount; i++) {
            delete columns[i];
        }
    }

    delete[] columns;
    columns = nullptr;

    delete[] name;
    name = nullptr;

    delete[] file;
    file = nullptr;

    columnCount = 0;
    rowCount = 0;
}


/// Double the capacity of the table
void Table::expand() {
    capacity *= 2;
    TableColumn** temp = new TableColumn*[capacity];

    for (int i = 0; i < columnCount; i++) {
        temp[i] = columns[i];
    }

    delete[] columns;
    columns = temp;
}


/// Copy table
/// \param other Table to copy from
void Table::copy(Table const &other) {
    clear();
    columnCount = other.columnCount;
    rowCount = other.rowCount;
    capacity = other.capacity;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    file = new char[strlen(other.file) + 1];
    strcpy(file, other.file);

    columns = new TableColumn*[capacity];

    for (int i = 0; i < columnCount; i++) {
        if (typeid(*other.columns[i]) == typeid(IntegerColumn&)) {
            columns[i] = new IntegerColumn(dynamic_cast<IntegerColumn&>(*other.columns[i]));
        }
        else if (typeid(*other.columns[i]) == typeid(FloatColumn&)) {
            columns[i] = new FloatColumn(dynamic_cast<FloatColumn&>(*other.columns[i]));
        }
        else {
            columns[i] = new StringColumn(dynamic_cast<StringColumn&>(*other.columns[i]));
        }
    }
}


/// Check if column exists in the table
/// \param columnIndex index of the column
void Table::checkColumnIndex(int columnIndex) const {
    if (columnIndex < 0 || columnIndex >= columnCount) {
        throw std::invalid_argument("Column with such index does not exist");
    }
}


/// Check if row exists in the table
/// \param rowIndex index of the row
void Table::checkRowIndex(int rowIndex) const {
    if (rowIndex < 0 || rowIndex >= rowCount) {
        throw std::invalid_argument("Row with such index does not exist");
    }
}


/// Helper function for InnerJoin
/// \param table result of the join
/// \param columnTable1 index of the column performing join on in table 1
/// \param columnTable2 index of the column performing join on in table 2
/// \param other table to join with
void Table::join(Table*& table, int columnTable1, int columnTable2, Table const& other) const {
    DynamicArray<int> indexes;
    for (int i = 0; i < rowCount; i++) {
        other.columns[columnTable2]->select(columns[columnTable1]->operator[](i), indexes);
        if (indexes.size() > 0) {
            Value** row1 = getRow(i);
            Value** row2 = other.getRow(indexes[indexes.size()-1]);
            indexes.pop_back();

            Value** joined = new Value*[columnCount + other.columnCount - 1];
            int skipped = 0; // helper to skip adding the join column twice
            for (int j = 0; j < columnCount; j++) {
                joined[j] = row1[j];
            }
            for (int j = columnCount; j < columnCount + other.columnCount; j++) {
                if (j - columnCount == columnTable2) {
                    skipped = 1;
                }
                else {
                    joined[j - skipped] = row2[j - columnCount];
                }
            }
            table->insertRow(joined);
            delete[] row1;
            delete[] row2;
            delete[] joined;
        }
    }
}


/// Print row
/// \param out stream to input the row in
/// \param index row index to print
void Table::printRow(std::ostream &out, int index) const {
    out << "|" << std::setw(10) << index;
    for (int i = 0; i < columnCount; i++) {
        out << "|";
        columns[i]->print(out, index, 10);
    }
    out << "|\n";
}


/// Setter for table name
/// \param _name new name
void Table::setName(char const *_name) {
    delete[] name;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}


/// Getter for table name
/// \return the name of the table
char *Table::getName() const {
    return name;
}


/// Setter for table file
/// \param _file new file
void Table::setFile(char const *_file) {
    delete[] file;
    file = new char[strlen(_file) + 1];
    strcpy(file, _file);
}


/// Getter for table file
/// \return the file of the table
char *Table::getFile() const {
    return file;
}


/// Add new empty column to the table
/// \param type type of the column
void Table::addColumn(ColumnType type) {
    if (capacity == columnCount) { expand(); }

    if (type == ColumnType::Integer) {
        columns[columnCount] = new IntegerColumn(rowCount);
    }
    else if (type == ColumnType::FloatingPoint) {
        columns[columnCount] = new FloatColumn(rowCount);
    }
    else {
        columns[columnCount] = new StringColumn(rowCount);
    }
    columnCount++;
}


/// Insert a new row into the table
/// \param values values of the columns in the row
void Table::insertRow(Value** values) {
    for (int i = 0; i < columnCount; i++) {
        columns[i]->insert(values[i]);
    }
    rowCount++;
}


/// Get table row
/// \param index index of the row
/// \return array of Value pointers
Value** Table::getRow(int index) const {
    checkRowIndex(index);
    Value** row = new Value*[columnCount];

    for (int i = 0; i < columnCount; i++) {
        Value* temp = columns[i]->operator[](index);
        row[i] = temp;
    }

    return row;
}


/// Find all rows containing the value in a certain column
/// \param columnIndex column to search in
/// \param indexes storage for the indexes
/// \param value value to search for
void Table::selectElement(int columnIndex, DynamicArray<int>& indexes,  Value *value) const {
    checkColumnIndex(columnIndex);
    columns[columnIndex]->select(value, indexes);
}


/// Delete all rows containing a value in a specific column
/// \param columnIndex index of the column
/// \param value value to search for
void Table::deleteElement(int columnIndex, Value *value) {
    checkColumnIndex(columnIndex);
    DynamicArray<int> indexes;
    selectElement(columnIndex, indexes, value);
    for (int i = 0; i < columnCount; i++) {
        columns[i]->deleteByIndexes(indexes);
    }
}


/// Update table column values
/// \param columnIndex index of the column to update
/// \param oldValue value to update
/// \param newValue new value
void Table::updateElements(int columnIndex, Value *oldValue, Value *newValue) {
    checkColumnIndex(columnIndex);
    DynamicArray<int> indexes;
    columns[columnIndex]->select(oldValue, indexes);
    columns[columnIndex]->update(indexes, newValue);
}


/// Count rows containing a value in column
/// \param columnIndex column to search in
/// \param value value to search for
/// \return number of columns
int Table::countRows(int columnIndex, Value *value) const {
    checkColumnIndex(columnIndex);
    return columns[columnIndex]->countValue(value);
}


/// Perform inner join
/// \param other table to join with
/// \param columnTable1 index of column to perform join on in table 1
/// \param columnTable2 index of column to perform join on in table 2
/// \return table - result of the join
Table *Table::innerJoin(Table const &other, int columnTable1, int columnTable2) const {
    if (columns[columnTable1]->columnType() != other.columns[columnTable2]->columnType()) {
        throw std::invalid_argument("Cannot perform join on columns of different types");
    }

    char newTableName[500];
    strcpy(newTableName, "Joined table - ");
    strcat(newTableName, this->name);
    strcat(newTableName, " & ");
    strcat(newTableName, other.name);

    Table* newTable = new Table(newTableName);

    for (int i = 0; i < columnCount; i++) {
        newTable->addColumn(columns[i]->columnType());
    }
    for (int i = 0; i < other.columnCount; i++) {
        if (i == columnTable2) { continue; }
        newTable->addColumn(other.columns[i]->columnType());
    }

    join(newTable, columnTable1, columnTable2, other);

    return newTable;
}


/// Output a page
/// \param out stream to insert in
/// \param pageSize number of rows on a page
/// \param currentPage page currently displayed
void Table::showPage(std::ostream &out, int pageSize, int currentPage) const {
    for (int i = 0; i < pageSize; i++) {
        printRow(out, (pageSize * currentPage) + i);
    }
}


/// Output a page
/// \param out stream to insert in
/// \param indexes rows to show
void Table::showPage(std::ostream &out, DynamicArray<int> &indexes) const {
    for (int i = 0; i < indexes.size(); i++) {
        printRow(out, indexes[i]);
    }
}

/// Print the sum of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::sum(std::ostream &out, int columnIndex) const {
    checkColumnIndex(columnIndex);
    columns[columnIndex]->sum(out);
}


/// Print the product of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::product(std::ostream &out, int columnIndex) const {
    checkColumnIndex(columnIndex);
    columns[columnIndex]->product(out);
}


/// Print the max of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::maximum(std::ostream &out, int columnIndex) const {
    checkColumnIndex(columnIndex);
    columns[columnIndex]->maximum(out);
}


/// Print the min of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::minimum(std::ostream &out, int columnIndex) const {
    checkColumnIndex(columnIndex);
    columns[columnIndex]->minimum(out);
}


/// Stream insertion operator
/// \param out output stream
/// \param w table to output
/// \return the stream with table information inserted
std::ostream &operator<<(std::ostream &out, Table const &table) {
    out << table.name << "\n"
        << table.columnCount << " "
        << table.rowCount << " ";

    for (int i = 0; i < table.columnCount; i++) {
        out << table.columns[i]->columnType() << ((i < table.columnCount - 1) ? " " : "\n");
    }

    for (int i = 0; i < table.rowCount; i++) {
        for (int j = 0; j < table.columnCount; j++) {
            table.columns[j]->print(out, i);
            out << "\n";
        }
    }

    return out;
}
