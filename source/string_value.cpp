#include "string_value.hpp"

/// Default constructor
StringValue::StringValue() {
    value = nullptr;
}


/// Constructor with parameters
StringValue::StringValue(char const *_value) {
    value = new char [strlen(_value) + 1];
    strcpy(value, _value);
}


/// Copy constructor
/// \param other object to copy
StringValue::StringValue(StringValue const &other) {
    value = new char [strlen(other.value) + 1];
    strcpy(value, other.value);
}


/// Copy assignment operator
/// \param other object to copy
/// \return updated object
StringValue& StringValue::operator=(StringValue const &other) {
    if (this != &other) {
        delete[] value;
        value = new char [strlen(other.value) + 1];
        strcpy(value, other.value);
    }
    return *this;
}


/// Destructor
StringValue::~StringValue() {
    delete[] value;
    value = nullptr;
}


/// Value getter
/// \return value
char *StringValue::get() const {
    return value;
}


/// Value setter
/// \param _value the updated value of value
void StringValue::set(char const *_value) {
    delete[] value;
    value = new char [strlen(_value) + 1];
    strcpy(value, _value);
}


/// Compare with equality operator
/// \param other StringValue to compare to
/// \return if the current value is equal to the other
bool StringValue::operator==(StringValue const &other) const {
    if (!value || !other.value) { return false; }
    return (strcmp(value, other.value) == 0);
}


/// Compare with inequality operator
/// \param other StringValue to compare to
/// \return if the current value is not equal to the other
bool StringValue::operator!=(StringValue const &other) const {
    if (!value || !other.value) { return false; }
    return (strcmp(value, other.value) != 0);
}


/// Compare with equality operator
/// \param other string to compare to
/// \return if the current value is equal to the other
bool StringValue::operator==(char const *other) const {
    if (!value || !other) { return false; }
    return (strcmp(value, other) == 0);
}


/// Compare with equality operator
/// \param other string to compare to
/// \return if the current value is not equal to the other
bool StringValue::operator!=(char const *other) const {
    if (!value || !other) { return false; }
    return (strcmp(value, other) != 0);
}


/// Stream insertion operator
/// \param out output stream
/// \param sv string to output
/// \return the stream with string inserted
std::ostream& operator<<(std::ostream& out, StringValue const& sv) {
    out << sv.value;
    return out;
}
