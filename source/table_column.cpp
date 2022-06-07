#include "table_column.hpp"

/// Default constructor
TableColumn::TableColumn() {
    count = 0;
    capacity = 5;
    elements = new Value[capacity];
}


/// Constructor with nullification
/// \param _count number of null values
TableColumn::TableColumn(int _count) {
    count = _count;
    capacity = _count * 2;
    elements = new Value[capacity];
    nullify(_count);
}


/// Copy constructor
/// \param other object to copy
TableColumn::TableColumn(TableColumn const &other) {
    copy(other);
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
TableColumn &TableColumn::operator=(TableColumn const &other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}


/// Destructor
TableColumn::~TableColumn() {
    clear();
}


/// Clear elements
void TableColumn::clear() {
    delete[] elements;
    elements = nullptr;
    count = 0;
}


/// Double the capacity of the column
void TableColumn::expand() {
    capacity *= 2;
    Value* temp = new Value[capacity];
    for (int copyIndex = 0; copyIndex < count; copyIndex++) {
        temp[copyIndex] = elements[copyIndex];
    }
    delete[] elements;
    elements = temp;
}


/// Copy elements of column
/// \param other TableColumn to copy from
void TableColumn::copy(TableColumn const &other) {
    clear();
    count = other.count;
    capacity = other.capacity;
    elements = new Value[count];
    for (int i = 0; i < count; i++) {
        elements[i] = other.elements[i];
    }
}


/// Nullify the first _count elements
/// \param _count number of elements to nullify
void TableColumn::nullify(int _count) {
    for (int i = 0; i < _count; i++) {
        elements[i] = NullValue();
    }
}

/// Delete elements at certain indexes
/// \param indexes indexes of the elements to delete
void TableColumn::deleteByIndexes(DynamicArray<int>& indexes) {
    int deletedCount = 0;
    capacity = (count - indexes.size()) * 2;
    Value* temp = new Value[capacity];

    for (int i = 0; deletedCount < indexes.size(); i++) {
        if (i == indexes[deletedCount]) {
            deletedCount++;
        }
        temp[i] = elements[i + deletedCount];
    }

    delete[] elements;
    elements = temp;
    count -= indexes.size();
}
