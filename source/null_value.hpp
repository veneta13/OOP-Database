#ifndef STACK_NULL_VALUE_HPP
#define STACK_NULL_VALUE_HPP

#include "value.hpp"

/// Represents NULL table cell
class NullValue : public Value {

public:
    NullValue();
    NullValue(NullValue const &other);
    NullValue &operator=(NullValue const &other);
    ~NullValue() override;
};


#endif //STACK_NULL_VALUE_HPP
