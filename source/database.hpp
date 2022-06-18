#ifndef STACK_DATABASE_HPP
#define STACK_DATABASE_HPP

#include "table.hpp"

/// Represents an aggregate operation
enum Operations{
    Sum = 1,
    Product = 2,
    Maximum = 3,
    Minimum = 4
};

/// Represents the whole database
class Database {

    /// The tables in the database
    Table** tables;

    int getTableByName(const char* name);

public:
    Database();
    Database(Database const& other);
    Database& operator=(Database const& other);
    ~Database();

    bool importTable(std::istream& in);
    bool exportTable(std::ostream& out, const char* tableName);

    void showTables(std::ostream& out);
    void describe(std::ostream& out, int tableIndex);
    void printByPages(std::ostream& out, std::istream& in);

    void select(std::ostream& out, const char* tableName, int columnIndex);
    int count(const char* tableName, int columnIndex, Value* value);

    void update(const char* tableName, int searchCol, Value* searchVal, int replaceCol, Value* replaceVal);
    void deleteRows(const char* tableName, int columnIndex, Value* value);
    void insert(const char* tableName, Value** values);

    void innerJoin(const char* table1, int column1, const char* table2, int column2);
    void aggregate(std::ostream& out, const char* tableName, int searchCol, int aggregCol, Operations operation);

    void rename(const char* oldName, const char* newName);
};


#endif //STACK_DATABASE_HPP
