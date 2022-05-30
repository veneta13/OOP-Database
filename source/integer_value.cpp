#include "integer_value.hpp"

/// Default constructor
IntegerValue::IntegerValue() {
    value = -1;
}


/// Constructor with parameters
/// \param _value value to set
IntegerValue::IntegerValue(int _value) {
    value = _value;
}


/// Copy constructor
/// \param other object to copy
IntegerValue::IntegerValue(const IntegerValue &other) {
    value = other.value;
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
IntegerValue &IntegerValue::operator=(const IntegerValue &other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}


/// Destructor
IntegerValue::~IntegerValue() = default;


/// Value getter
/// \return value
int IntegerValue::get() const {
    return value;
}


/// Value setter
/// \param _value the updated value of value
void IntegerValue::set(int _value) {
    value = _value;
}


/// Addition operator for IntegerValue
/// \param other IntegerValue object to add
/// \return the sum of the values
int IntegerValue::operator+(const IntegerValue &other) const {
    return value + other.value;
}


/// Addition operator for int
/// \param other integer to add
/// \return the sum of value and other
int IntegerValue::operator+(int other) const {
    return value + other;
}


/// Multiplication operator for IntegerValue
/// \param other IntegerValue object to multiply
/// \return the product of the values
int IntegerValue::operator*(const IntegerValue &other) const {
    return value * other.value;
}


/// Multiplication operator for int
/// \param other integer to multiply
/// \return the product of value and other
int IntegerValue::operator*(int other) const {
    return value * other;
}


/// Compare with equality
/// \param other IntegerValue to compare to
/// \return if the current value is equal to the other
bool IntegerValue::operator==(const IntegerValue &other) const {
    return value == other.value;
}


/// Compare with inequality operator
/// \param other IntegerValue to compare to
/// \return if the current value is not equal to the other
bool IntegerValue::operator!=(const IntegerValue &other) const {
    return value != other.value;
}


/// Compare with greater than operator
/// \param other IntegerValue to compare to
/// \return if the current value is bigger than the other
bool IntegerValue::operator>(const IntegerValue &other) const {
    return value > other.value;
}


/// Compare with less than operator
/// \param other IntegerValue to compare to
/// \return if the current value is smaller than the other
bool IntegerValue::operator<(const IntegerValue &other) const {
    return value < other.value;
}


/// Compare with equality operator
/// \param other integer to compare to
/// \return if the current value is equal to the other
bool IntegerValue::operator==(int other) const {
    return value == other;
}


/// Compare with inequality operator
/// \param other integer to compare to
/// \return if the current value is not equal to the other
bool IntegerValue::operator!=(int other) const {
    return value != other;
}


/// Compare with greater than operator
/// \param other integer to compare to
/// \return if the current value is bigger than the other
bool IntegerValue::operator>(int other) const {
    return value > other;
}


/// Compare with less than operator
/// \param other integer to compare to
/// \return if the current value is smaller than the other
bool IntegerValue::operator<(int other) const {
    return value < other;
}
