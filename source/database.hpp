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
    /// Number of tables in the database
    int count;

    /// The max number of tables that can be saved in the database currently
    int capacity;

    /// The tables in the database
    Table** tables = nullptr;

    int getTableByName(const char* name) const;
    void clear();
    void expand();
    void copy(Database const &other);
    void readRows(std::istream& in, Table* table, int columns, int rows);

public:
    Database();
    Database(Database const& other);
    Database& operator=(Database const& other);
    ~Database();

    bool importTable(std::istream& in);
    bool exportTable(std::ostream& out, const char* tableName);

    void showTables(std::ostream& out);
    bool describe(std::ostream& out, const char* tableName);
    bool printByPages(std::ostream& out, std::istream& in, const char* tableName);

    bool select(std::ostream& out, std::istream& in, const char* tableName, int columnIndex, Value* value);

    bool update(const char* tableName, int searchCol, Value* searchVal, int replaceCol, Value* replaceVal);
    bool deleteRows(const char* tableName, int columnIndex, Value* value);

    bool addTable(Table* table);
    bool insert(const char* tableName, Value** values);
    bool addColumn(std::istream& in, std::ostream& out,const char* tableName);

    bool innerJoin(std::ostream& out, const char* table1, int column1, const char* table2, int column2);
    bool aggregate(std::ostream& out, const char* tableName, int searchCol, Value* value, int aggregCol, Operations operation);

    bool rename(const char* oldName, const char* newName);

    int countRows(const char* tableName, int columnIndex, Value* value) const;

    int countTables() const;
    int countColumns(const char* tableName) const;

    char* getTableName(int index) const;
    ColumnType getColumnType(const char* tableName, int columnIndex);
};


#endif //STACK_DATABASE_HPP
