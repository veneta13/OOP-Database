#ifndef STACK_VALUE_HPP
#define STACK_VALUE_HPP

/// Represents the value of a table cell
class Value {
public:
    Value();
    Value(Value const& other);
    Value& operator=(Value const& other);
    virtual ~Value();
};


#endif //STACK_VALUE_HPP
