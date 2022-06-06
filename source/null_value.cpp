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
