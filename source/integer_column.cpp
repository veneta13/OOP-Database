#include "integer_column.hpp"

/// Default constructor
IntegerColumn::IntegerColumn() {
    count = 0;
    capacity = 5;
    elements = new Value*[capacity];
}


/// Constructor with nullification
/// \param _count number of null values
IntegerColumn::IntegerColumn(int _count) {
    count = _count;
    capacity = (_count == 0) ? 5 : _count * 2;
    elements = new Value*[capacity];
    nullify(_count);
}


/// Copy constructor
/// \param other object to copy
IntegerColumn::IntegerColumn(IntegerColumn const &other) {
    count = 0;
    copy(other);
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
IntegerColumn &IntegerColumn::operator=(IntegerColumn const &other) {
    if (this != &other) {
        count = 0;
        copy(other);
    }
    return *this;
}


/// Destructor
IntegerColumn::~IntegerColumn() {
    clear();
}


/// Clear elements
void IntegerColumn::clear() {
    for (int i = 0; i < count; i++) {
        delete elements[i];
    }
    delete[] elements;
    elements = nullptr;
    count = 0;
}


/// Double the capacity of the column
void IntegerColumn::expand() {
    capacity *= 2;
    Value** temp = new Value*[capacity];
    for (int i = 0; i < count; i++) {
        temp[i] = elements[i];
    }
    delete[] elements;
    elements = temp;
}


/// Copy elements of column
/// \param other IntegerColumn to copy from
void IntegerColumn::copy(IntegerColumn const &other) {
    clear();
    count = other.count;
    capacity = other.capacity;
    elements = new Value*[capacity];
    for (int i = 0; i < count; i++) {
        if (typeid(*other.elements[i]) == typeid(NullValue&)) {
            elements[i] = new NullValue();
        }
        else {
            elements[i] = new IntegerValue(dynamic_cast<IntegerValue&>(*other.elements[i]));
        }
    }
}


/// Nullify the first _count elements
/// \param _count number of elements to nullify
void IntegerColumn::nullify(int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        elements[i] = new NullValue();
    }
}


Value *IntegerColumn::operator[](int index) {
    if (index < 0 || index > count - 1) {
        throw std::invalid_argument("Invalid index");
    }
    return elements[index];
}


void IntegerColumn::deleteByIndexes(DynamicArray<int>& indexes) {
    int deletedCount = 0;
    int newCapacity = (count - indexes.size()) * 2;
    int newCount = count;

    Value** temp = new Value*[capacity];

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


void IntegerColumn::insert(Value* value) {
    if (capacity == count) { expand(); }
    if (typeid(*value) == typeid(NullValue&)) {
        elements[count] = new NullValue();
    }
    else {
        elements[count] = new IntegerValue(dynamic_cast<IntegerValue&>(*value));
    }
    count++;
}


void IntegerColumn::update(DynamicArray<int> indexes, Value *newValue) {
    if (typeid(*newValue) == typeid(NullValue&)) {
        for (int i = 0; i < indexes.size(); i++) {
            delete elements[indexes[i]];
            elements[indexes[i]] = new NullValue();
        }
        return;
    }

    for (int i = 0; i < indexes.size(); i++) {
        delete elements[indexes[i]];
        elements[indexes[i]] = new IntegerValue(*dynamic_cast<IntegerValue*>(newValue));
    }
}


void IntegerColumn::select(Value* value, DynamicArray<int>& indexes) const {
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
        if (dynamic_cast<IntegerValue&>(*value) == dynamic_cast<IntegerValue&>(*elements[i])) {
            indexes.push_back(i);
        }
    }
}


int IntegerColumn::countValue(Value* value) {
    DynamicArray<int> indexes;
    select(value, indexes);
    return indexes.size();
}



ColumnType IntegerColumn::columnType() {
    return ColumnType::Integer;
}


int IntegerColumn::size() const {
    return count;
}


void IntegerColumn::sum(std::ostream& out, DynamicArray<int>& indexes) {
    if (count < 1) {
        out << "SUM OF COLUMN: 0\n";
        return;
    }

    int sum = 0;
    for (int i = 0; i < indexes.size(); i++) {
        if (typeid(*elements[indexes[i]]) == typeid(NullValue&)) { continue; }
        sum = *dynamic_cast<IntegerValue*>(elements[indexes[i]]) + sum;
    }
    out << "SUM OF COLUMN: " << sum << "\n";
}


void IntegerColumn::product(std::ostream& out, DynamicArray<int>& indexes) {
    if (count < 1) {
        out << "PRODUCT OF COLUMN: 0\n";
        return;
    }

    int prod = 1;
    for (int i = 0; i < indexes.size(); i++) {
        if (typeid(*elements[indexes[i]]) == typeid(NullValue&)) { continue; }
        prod = *dynamic_cast<IntegerValue*>(elements[indexes[i]]) * prod;
    }
    out << "PRODUCT OF COLUMN: " << prod << "\n";
}


void IntegerColumn::maximum(std::ostream& out, DynamicArray<int>& indexes) {
    if (count < 1) {
        out << "EMPTY COLUMN - no MAX value!\n";
        return;
    }

    int max;
    bool found = false;

    for (int i = 0; i < indexes.size(); i++) {
        if (typeid(*elements[indexes[i]]) == typeid(NullValue&)) { continue; }
        max = dynamic_cast<IntegerValue*>(elements[indexes[i]])->get();
        found = true;
        break;
    }

    if (!found) {
        out << "Values contain only NULL!\n";
        return;
    }

    for (int i = 0; i < indexes.size(); i++) {
        if (typeid(*elements[indexes[i]]) == typeid(NullValue&)) { continue; }
        int current = dynamic_cast<IntegerValue*>(elements[indexes[i]])->get();
        if (max < current) { max = current; }
    }

    out << "MAX: " << max << "\n";
}

void IntegerColumn::minimum(std::ostream& out, DynamicArray<int>& indexes) {
    if (count < 1) {
        out << "EMPTY COLUMN - no MIN value!\n";
        return;
    }

    int min;
    bool found = false;

    for (int i = 0; i < indexes.size(); i++) {
        if (typeid(*elements[indexes[i]]) == typeid(NullValue&)) { continue; }
        min = dynamic_cast<IntegerValue*>(elements[indexes[i]])->get();
        found = true;
        break;
    }

    if (!found) {
        out << "Values contain only NULL!\n";
        return;
    }

    for (int i = 0; i < indexes.size(); i++) {
        if (typeid(*elements[indexes[i]]) == typeid(NullValue&)) { continue; }
        int current = dynamic_cast<IntegerValue*>(elements[indexes[i]])->get();
        if (min > current) { min = current; }
    }

    out << "MIN: " << min << "\n";
}


void IntegerColumn::print(std::ostream &out, int index) {
    Value* element = operator[](index);

    if (typeid(*element) == typeid(NullValue&)) {
        out << *dynamic_cast<NullValue*>(element);
    }
    else {
        out << *dynamic_cast<IntegerValue*>(element);
    }
}


void IntegerColumn::print(std::ostream &out, int index, int width) {
    Value* element = operator[](index);

    if (typeid(*element) == typeid(NullValue&)) {
        out << std::setw(width) << *dynamic_cast<NullValue*>(element);
    }
    else {
        out << std::setw(width) << *dynamic_cast<IntegerValue*>(element);
    }
}
