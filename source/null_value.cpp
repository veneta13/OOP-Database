#include "null_value.hpp"

/// Default constructor
NullValue::NullValue() = default;


/// Copy constructor
/// \param other object to copy
NullValue::NullValue(NullValue const &other) = default;


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
NullValue &NullValue::operator=(NullValue const &other) = default;


/// Destructor
NullValue::~NullValue() = default;


/// Compare with equality operator
/// \param other NullValue to compare to
/// \return true
bool NullValue::operator==(NullValue const &other) {
    return true;
}


/// Compare with inequality operator
/// \param other NullValue to compare to
/// \return false
bool NullValue::operator!=(NullValue const &other) {
    return false;
}


/// Stream insertion operator
/// \param out output stream
/// \param sv NULL to output
/// \return the stream with NULL inserted
std::ostream& operator<<(std::ostream& out, NullValue const& nv) {
    out << "NULL";
    return out;
}
