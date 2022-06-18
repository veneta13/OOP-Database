#include "executor.hpp"

Executor::Executor() {

}

Executor& Executor::getInstance() {
    static Executor instance;
    return instance;
}
