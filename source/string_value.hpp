#ifndef STACK_STRING_VALUE_HPP
#define STACK_STRING_VALUE_HPP

#include "value.hpp"
#include <cstring>

/// Represents the value of a table cell with an integer
class StringValue : public Value {
    /// The value in the cell
    char* value = nullptr;

public:
    StringValue();
    StringValue(const char* _value);
    StringValue(StringValue const& other);
    StringValue& operator=(StringValue const& other);
    ~StringValue() override;

    bool operator==(StringValue const& other) const;
    bool operator!=(StringValue const& other) const;

    bool operator==(char const* other) const;
    bool operator!=(char const* other) const;

    char* get() const;
    void set(char const* _value);

    friend std::ostream& operator<<(std::ostream& out, StringValue const& sv);
};

#endif
