#ifndef STACK_INTEGER_VALUE_HPP
#define STACK_INTEGER_VALUE_HPP

#include "value.hpp"

/// Represents the value of a table cell with an integer
class IntegerValue : public Value {
    /// The value in the cell
    int value;

public:
    IntegerValue();
    IntegerValue(int _value);
    IntegerValue(IntegerValue const& other);
    IntegerValue& operator=(IntegerValue const& other);
    ~IntegerValue() override;

    int operator+(IntegerValue const& other) const;
    int operator+(int other) const;

    int operator*(IntegerValue const& other) const;
    int operator*(int other) const;

    bool operator>(IntegerValue const& other) const;
    bool operator==(IntegerValue const& other) const;
    bool operator!=(IntegerValue const& other) const;
    bool operator<(IntegerValue const& other) const;

    bool operator>(int other) const;
    bool operator==(int other) const;
    bool operator!=(int other) const;
    bool operator<(int other) const;

    int get() const;
    void set(int _value);

    friend std::ostream& operator<<(std::ostream& out, IntegerValue const& iv);
};


#endif //STACK_INTEGER_VALUE_HPP
