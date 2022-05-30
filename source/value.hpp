#ifndef STACK_VALUE_HPP
#define STACK_VALUE_HPP


class Value {
public:
    Value();
    Value(Value const& other);
    Value& operator=(Value const& other);
    virtual ~Value();
};


#endif //STACK_VALUE_HPP
