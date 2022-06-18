#ifndef STACK_EXECUTOR_HPP
#define STACK_EXECUTOR_HPP


/// User interface provider
/// Implementation of the Singleton design pattern
class Executor {
    Executor();
public:
    static Executor& getInstance();

    Executor(Executor const&) = delete;
    void operator=(Executor const&) = delete;
};


#endif //STACK_EXECUTOR_HPP
