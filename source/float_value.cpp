#include "float_value.hpp"

/// Default constructor
FloatValue::FloatValue() {
    value = -1;
}


/// Constructor with parameters
/// \param _value value to set
FloatValue::FloatValue(double _value) {
    value = _value;
}


/// Copy constructor
/// \param other object to copy
FloatValue::FloatValue(const FloatValue &other) {
    value = other.value;
}


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
FloatValue &FloatValue::operator=(const FloatValue &other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}


/// Destructor
FloatValue::~FloatValue() = default;


/// Value getter
/// \return value
double FloatValue::get() const {
    return value;
}


/// Value setter
/// \param _value the updated value of value
void FloatValue::set(double _value) {
    value = _value;
}


/// Addition operator for FloatValue
/// \param other FloatValue object to add
/// \return the sum of the values
double FloatValue::operator+(const FloatValue &other) const {
    return value + other.value;
}


/// Addition operator for double
/// \param other integer to add
/// \return the sum of value and other
double FloatValue::operator+(double other) const {
    return value + other;
}


/// Multiplication operator for FloatValue
/// \param other FloatValue object to multiply
/// \return the product of the values
double FloatValue::operator*(const FloatValue &other) const {
    return value * other.value;
}


/// Multiplication operator for double
/// \param other integer to multiply
/// \return the product of value and other
double FloatValue::operator*(double other) const {
    return value * other;
}


/// Compare with equality
/// \param other FloatValue to compare to
/// \return if the current value is equal to the other
bool FloatValue::operator==(const FloatValue &other) const {
    return std::fabs(value - other.value) < EPSILON;
}


/// Compare with inequality operator
/// \param other FloatValue to compare to
/// \return if the current value is not equal to the other
bool FloatValue::operator!=(const FloatValue &other) const {
    return std::fabs(value - other.value) >= EPSILON;
}


/// Compare with greater than operator
/// \param other FloatValue to compare to
/// \return if the current value is bigger than the other
bool FloatValue::operator>(const FloatValue &other) const {
    return value > other.value;
}


/// Compare with less than operator
/// \param other FloatValue to compare to
/// \return if the current value is smaller than the other
bool FloatValue::operator<(const FloatValue &other) const {
    return value < other.value;
}


/// Compare with equality operator
/// \param other integer to compare to
/// \return if the current value is equal to the other
bool FloatValue::operator==(double other) const {
    return std::fabs(value - other) < EPSILON;
}


/// Compare with inequality operator
/// \param other integer to compare to
/// \return if the current value is not equal to the other
bool FloatValue::operator!=(double other) const {
    return std::fabs(value - other) >= EPSILON;
}


/// Compare with greater than operator
/// \param other integer to compare to
/// \return if the current value is bigger than the other
bool FloatValue::operator>(double other) const {
    return value > other;
}


/// Compare with less than operator
/// \param other integer to compare to
/// \return if the current value is smaller than the other
bool FloatValue::operator<(double other) const {
    return value < other;
}
