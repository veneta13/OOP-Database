#include "string_column.hpp"

/// Default constructor
StringColumn::StringColumn() {
    count = 0;
    capacity = 5;
    elements = new Value*[capacity];
}


/// Constructor with nullification
/// \param _count number of null values
StringColumn::StringColumn(int _count) {
    count = _count;
    capacity = (_count == 0) ? 5 : _count * 2;
    elements = new Value*[capacity];
    nullify(_count);
}


/// Copy constructor
/// \param other object to copy
StringColumn::StringColumn(StringColumn const &other) {
    count = 0;
    copy(other);
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
StringColumn &StringColumn::operator=(StringColumn const &other) {
    if (this != &other) {
        count = 0;
        copy(other);
    }
    return *this;
}


/// Destructor
StringColumn::~StringColumn() {
    clear();
}


/// Clear elements
void StringColumn::clear() {
    for (int i = 0; i < count; i++) {
        delete elements[i];
    }
    delete[] elements;
    elements = nullptr;
    count = 0;
}


/// Double the capacity of the column
void StringColumn::expand() {
    capacity *= 2;
    Value** temp = new Value*[capacity];
    for (int i = 0; i < count; i++) {
        temp[i] = elements[i];
    }
    delete[] elements;
    elements = temp;
}


/// Copy elements of column
/// \param other StringColumn to copy from
void StringColumn::copy(StringColumn const &other) {
    clear();
    count = other.count;
    capacity = other.capacity;
    elements = new Value*[capacity];
    for (int i = 0; i < count; i++) {
        if (typeid(*other.elements[i]) == typeid(NullValue&)) {
            elements[i] = new NullValue();
        }
        else {
            elements[i] = new StringValue(dynamic_cast<StringValue&>(*other.elements[i]));
        }
    }
}


/// Nullify the first _count elements
/// \param _count number of elements to nullify
void StringColumn::nullify(int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        elements[i] = new NullValue();
    }
}


Value *StringColumn::operator[](int index) {
    if (index < 0 || index > count - 1) {
        throw std::invalid_argument("Invalid index");
    }
    return elements[index];
}


void StringColumn::deleteByIndexes(DynamicArray<int>& indexes) {
    int deletedCount = 0;
    int newCapacity = (count - indexes.size()) * 2;
    int newCount = count;

    Value** temp = new Value*[newCapacity];

    for (int i = 0; i < count; i++) {
        if (i == indexes[deletedCount]) {
            delete elements[i];
            deletedCount++;
            continue;
        }
        temp[i - deletedCount] = elements[i];
    }

    delete[] elements;
    elements = temp;
    count = newCount - indexes.size();
    capacity = newCapacity;
}


void StringColumn::insert(Value* value) {
    if (capacity == count) { expand(); }
    if (typeid(*value) == typeid(NullValue&)) {
        elements[count] = new NullValue();
    }
    else {
        elements[count] = new StringValue(dynamic_cast<StringValue&>(*value));
    }
    count++;
}


void StringColumn::update(DynamicArray<int> indexes, Value *newValue) {
    if (typeid(*newValue) == typeid(NullValue&)) {
        for (int i = 0; i < indexes.size(); i++) {
            delete elements[indexes[i]];
            elements[indexes[i]] = new NullValue();
        }
        return;
    }

    for (int i = 0; i < indexes.size(); i++) {
        delete elements[indexes[i]];
        elements[indexes[i]] = new StringValue(*dynamic_cast<StringValue*>(newValue));
    }
}


void StringColumn::select(Value* value, DynamicArray<int>& indexes) const {
    if (typeid(*value) == typeid(NullValue&)) {
        for (int i = 0; i < count; i++) {
            if (typeid(*elements[i]) == typeid(NullValue&)) {
                indexes.push_back(i);
            }
        }
        return;
    }

    for (int i = 0; i < count; i++) {
        if (typeid(*elements[i]) == typeid(NullValue&)) { continue; }
        if (dynamic_cast<StringValue&>(*value) == dynamic_cast<StringValue&>(*elements[i])) {
            indexes.push_back(i);
        }
    }
}


int StringColumn::countValue(Value* value) {
    DynamicArray<int> indexes;
    select(value, indexes);
    return indexes.size();
}



ColumnType StringColumn::columnType() {
    return ColumnType::String;
}


int StringColumn::size() const {
    return count;
}


void StringColumn::sum(std::ostream& out, DynamicArray<int>& indexes) {
    out << "Operation is not supported for nonnumerical columns.\n";
}


void StringColumn::product(std::ostream& out, DynamicArray<int>& indexes) {
    out << "Operation is not supported for nonnumerical columns.\n";
}


void StringColumn::maximum(std::ostream& out, DynamicArray<int>& indexes) {
    out << "Operation is not supported for nonnumerical columns.\n";
}

void StringColumn::minimum(std::ostream& out, DynamicArray<int>& indexes) {
    out << "Operation is not supported for nonnumerical columns.\n";
}


void StringColumn::print(std::ostream &out, int index) {
    Value* element = operator[](index);

    if (typeid(*element) == typeid(NullValue&)) {
        out << *dynamic_cast<NullValue*>(element);
    }
    else {
        out << *dynamic_cast<StringValue*>(element);
    }
}


void StringColumn::print(std::ostream &out, int index, int width) {
    Value* element = operator[](index);

    if (typeid(*element) == typeid(NullValue&)) {
        out << std::setw(width) << *dynamic_cast<NullValue*>(element);
    }
    else {
        out << std::setw(width) << *dynamic_cast<StringValue*>(element);
    }
}
