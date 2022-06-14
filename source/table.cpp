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
void Table::checkIndex(int columnIndex) const {
    if (columnIndex < 0 || columnIndex >= columnCount) {
        throw std::invalid_argument("Column with such index does not exist");
    }
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


/// Find all rows containing the value in a certain column
/// \param columnIndex column to search in
/// \param indexes storage for the indexes
/// \param value value to search for
void Table::selectElement(int columnIndex, DynamicArray<int>& indexes,  Value *value) const {
    checkIndex(columnIndex);
    columns[columnIndex]->select(value, indexes);
}


/// Delete all rows containing a value in a specific column
/// \param columnIndex index of the column
/// \param value value to search for
void Table::deleteElement(int columnIndex, Value *value) {
    checkIndex(columnIndex);
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
    checkIndex(columnIndex);
    columns[columnIndex]->update(oldValue, newValue);
}


/// Count rows containing a value in column
/// \param columnIndex column to search in
/// \param value value to search for
/// \return number of columns
int Table::countRows(int columnIndex, Value *value) const {
    checkIndex(columnIndex);
    return columns[columnIndex]->countValue(value);
}


/// Perform inner join
/// \param other table to join with
/// \return table - result of the join
Table *Table::innerJoin(Table const &other) const {
    return nullptr;
}


/// Output a page
/// \param out stream to insert in
/// \param pageSize number of rows on a page
/// \param currentPage page currently displayed
void Table::showPage(std::ostream &out, int pageSize, int currentPage) const {

}


/// Output a page
/// \param out stream to insert in
/// \param indexes rows to show
void Table::showPage(std::ostream &out, DynamicArray<int> &indexes) const {

}

/// Print the sum of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::sum(std::ostream &out, int columnIndex) const {
    checkIndex(columnIndex);
    columns[columnIndex]->sum(out);
}


/// Print the product of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::product(std::ostream &out, int columnIndex) const {
    checkIndex(columnIndex);
    columns[columnIndex]->product(out);
}


/// Print the max of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::maximum(std::ostream &out, int columnIndex) const {
    checkIndex(columnIndex);
    columns[columnIndex]->maximum(out);
}


/// Print the min of the column
/// \param out stream to input answer into
/// \param columnIndex index of the column to calculate
void Table::minimum(std::ostream &out, int columnIndex) const {
    checkIndex(columnIndex);
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
