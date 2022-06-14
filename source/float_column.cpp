#include "float_column.hpp"

/// Default constructor
FloatColumn::FloatColumn() {
    count = 0;
    capacity = 5;
    elements = new Value*[capacity];
}


/// Constructor with nullification
/// \param _count number of null values
FloatColumn::FloatColumn(int _count) {
    count = _count;
    capacity = _count * 2;
    elements = new Value*[capacity];
    nullify(_count);
}


/// Copy constructor
/// \param other object to copy
FloatColumn::FloatColumn(FloatColumn const &other) {
    count = 0;
    copy(other);
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
FloatColumn &FloatColumn::operator=(FloatColumn const &other) {
    if (this != &other) {
        count = 0;
        copy(other);
    }
    return *this;
}


/// Destructor
FloatColumn::~FloatColumn() {
    clear();
}


/// Clear elements
void FloatColumn::clear() {
    for (int i = 0; i < count; i++) {
        delete elements[i];
    }
    delete[] elements;
    elements = nullptr;
    count = 0;
}


/// Double the capacity of the column
void FloatColumn::expand() {
    capacity *= 2;
    Value** temp = new Value*[capacity];
    for (int i = 0; i < count; i++) {
        temp[i] = elements[i];
    }
    delete[] elements;
    elements = temp;
}


/// Copy elements of column
/// \param other FloatColumn to copy from
void FloatColumn::copy(FloatColumn const &other) {
    clear();
    count = other.count;
    capacity = other.capacity;
    elements = new Value*[count];
    for (int i = 0; i < count; i++) {
        if (typeid(*other.elements[i]) == typeid(NullValue&)) {
            elements[i] = new NullValue();
        }
        else {
            elements[i] = new FloatValue(dynamic_cast<FloatValue&>(*other.elements[i]));
        }
    }
}


/// Nullify the first _count elements
/// \param _count number of elements to nullify
void FloatColumn::nullify(int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        elements[i] = new NullValue();
    }
}


Value *FloatColumn::operator[](int index) {
    if (index < 0 || index > count - 1) {
        throw std::invalid_argument("Invalid index");
    }
    return elements[index];
}


void FloatColumn::deleteByIndexes(DynamicArray<int>& indexes) {
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


void FloatColumn::insert(Value* value) {
    if (capacity == count) { expand(); }
    if (typeid(*value) == typeid(NullValue&)) {
        elements[count] = new NullValue();
    }
    else {
        elements[count] = new FloatValue(dynamic_cast<FloatValue&>(*value));
    }
    count++;
}


void FloatColumn::update(Value* oldValue, Value* newValue) {
    DynamicArray<int> indexes;
    select(oldValue, indexes);

    if (typeid(*newValue) == typeid(NullValue&)) {
        for (int i = 0; i < indexes.size(); i++) {
            delete elements[indexes[i]];
            elements[indexes[i]] = new NullValue();
        }
        return;
    }

    for (int i = 0; i < indexes.size(); i++) {
        delete elements[indexes[i]];
        elements[indexes[i]] = new FloatValue(*dynamic_cast<FloatValue*>(newValue));
    }
}


void FloatColumn::select(Value* value, DynamicArray<int>& indexes) const {
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
        if (dynamic_cast<FloatValue&>(*value) == dynamic_cast<FloatValue&>(*elements[i])) {
            indexes.push_back(i);
        }
    }
}


int FloatColumn::countValue(Value* value) {
    DynamicArray<int> indexes;
    select(value, indexes);
    return indexes.size();
}



ColumnType FloatColumn::columnType() {
    return ColumnType::FloatingPoint;
}


void FloatColumn::sum(std::ostream& out) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        if (typeid(*elements[i]) == typeid(NullValue&)) { continue; }
        sum = *dynamic_cast<FloatValue*>(elements[i]) + sum;
    }
    out << "SUM OF COLUMN: " << sum << "\n";
}


void FloatColumn::product(std::ostream& out) {
    double prod = 1;
    for (int i = 0; i < count; i++) {
        if (typeid(*elements[i]) == typeid(NullValue&)) { continue; }
        prod = *dynamic_cast<FloatValue*>(elements[i]) * prod;
    }
    out << "PRODUCT OF COLUMN: " << prod << "\n";
}


void FloatColumn::maximum(std::ostream& out) {
    if (count == 0) {
        out << "EMPTY COLUMN - no MAX value!\n";
        return;
    }

    double max;
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (typeid(*elements[i]) == typeid(NullValue&)) { continue; }
        max = dynamic_cast<FloatValue*>(elements[i])->get();
        found = true;
        break;
    }

    if (!found) {
        out << "Column contains only NULL!\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (typeid(*elements[i]) == typeid(NullValue&)) { continue; }
        double current = dynamic_cast<FloatValue*>(elements[i])->get();
        if (max < current) { max = current; }
    }

    out << "MAX: " << max << "\n";
}

void FloatColumn::minimum(std::ostream& out) {
    if (count == 0) {
        out << "EMPTY COLUMN - no MIN value!\n";
        return;
    }

    double min;
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (typeid(*elements[i]) == typeid(NullValue&)) { continue; }
        min = dynamic_cast<FloatValue*>(elements[i])->get();
        found = true;
        break;
    }

    if (!found) {
        out << "Column contains only NULL!\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (typeid(*elements[i]) == typeid(NullValue&)) { continue; }
        double current = dynamic_cast<FloatValue*>(elements[i])->get();
        if (min > current) { min = current; }
    }

    out << "MIN: " << min << "\n";
}
