#ifndef STACK_EXECUTOR_HPP
#define STACK_EXECUTOR_HPP


#include "database.hpp"
#include <fstream>


/// User interface provider
class Executor {
    /// Flag if the file was saved after last change
    bool isSaved;

    /// Name of file containing the database
    char* dbFile = nullptr;

    /// The database
    Database* database = nullptr;

    void open(std::ostream& out, std::istream& in);
    void close(std::ostream& out, std::istream& in);
    void save(std::ostream& out, std::istream& in);
    void saveas(std::ostream& out, std::istream& in);
    void import(std::ostream& out, std::istream& in);
    void showtables(std::ostream& out, std::istream& in);
    void describe(std::ostream& out, std::istream& in);
    void print(std::ostream& out, std::istream& in);
    void export_(std::ostream& out, std::istream& in);
    void select(std::ostream& out, std::istream& in);
    void addcolumn(std::ostream& out, std::istream& in);
    void update(std::ostream& out, std::istream& in);
    void delete_(std::ostream& out, std::istream& in);
    void insert(std::ostream& out, std::istream& in);
    void innerjoin(std::ostream& out, std::istream& in);
    void rename(std::ostream& out, std::istream& in);
    void count(std::ostream& out, std::istream& in);
    void aggregate(std::ostream& out, std::istream& in);
    bool exit(std::ostream& out, std::istream& in);

    Value* readValue(std::ostream& out, std::istream& in, ColumnType valueType);
    bool chooseFunction(std::ostream& out, std::istream& in);

public:
    Executor();
    Executor(Executor const& other);
    Executor& operator=(Executor const& other);
    ~Executor();

    bool enter(std::ostream& out, std::istream& in);
};


#endif //STACK_EXECUTOR_HPP
