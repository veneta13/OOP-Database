#ifndef STACK_FLOAT_VALUE_HPP
#define STACK_FLOAT_VALUE_HPP

#include "value.hpp"

#include <cmath>

///Helper for floating point number comparisons
const float EPSILON = 0.00001f;


/// Represents the value of a table cell with a floating point number
class FloatValue  : public Value {
    /// The value in the cell
    float value;

public:
    FloatValue();
    FloatValue(float _value);
    FloatValue(FloatValue const& other);
    FloatValue& operator=(FloatValue const& other);
    ~FloatValue();

    float operator+(FloatValue const& other) const;
    float operator+(float other) const;

    float operator*(FloatValue const& other) const;
    float operator*(float other) const;

    bool operator>(FloatValue const& other) const;
    bool operator==(FloatValue const& other) const;
    bool operator!=(FloatValue const& other) const;
    bool operator<(FloatValue const& other) const;

    bool operator>(float other) const;
    bool operator==(float other) const;
    bool operator!=(float other) const;
    bool operator<(float other) const;

    float get() const;
    void set(float _value);
};


#endif //STACK_FLOAT_VALUE_HPP
