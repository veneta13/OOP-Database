#ifndef STACK_FLOAT_VALUE_HPP
#define STACK_FLOAT_VALUE_HPP

#include "value.hpp"

#include <cmath>

///Helper for floating point number comparisons
const double EPSILON = 0.000001f;


/// Represents the value of a table cell with a floating point number
class FloatValue : public Value {
    /// The value in the cell
    double value;

public:
    FloatValue();
    FloatValue(double _value);
    FloatValue(FloatValue const& other);
    FloatValue& operator=(FloatValue const& other);
    ~FloatValue() override;

    double operator+(FloatValue const& other) const;
    double operator+(double other) const;

    double operator*(FloatValue const& other) const;
    double operator*(double other) const;

    bool operator>(FloatValue const& other) const;
    bool operator==(FloatValue const& other) const;
    bool operator!=(FloatValue const& other) const;
    bool operator<(FloatValue const& other) const;

    bool operator>(double other) const;
    bool operator==(double other) const;
    bool operator!=(double other) const;
    bool operator<(double other) const;

    double get() const;
    void set(double _value);

    friend std::ostream& operator<<(std::ostream& out, FloatValue const& fv);
};


#endif //STACK_FLOAT_VALUE_HPP
