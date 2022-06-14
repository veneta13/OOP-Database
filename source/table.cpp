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
    for (int i = 0; i < columnCount; i++) {
        delete columns[i];
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

    columns = new TableColumn*[columnCount];

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
