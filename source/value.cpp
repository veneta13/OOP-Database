#include "value.hpp"

/// Default constructor
Value::Value() = default;


/// Copy constructor
/// \param other object to copy
Value::Value(const Value &other) = default;


/// Copy assignment operator
/// \param other object to copy
/// \return the updated object
Value &Value::operator=(const Value &other) = default;


/// Destructor
Value::~Value() = default;
