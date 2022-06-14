#ifndef STACK_TABLE_HPP
#define STACK_TABLE_HPP

#include "../source/integer_column.hpp"
#include "../source/float_column.hpp"
#include "../source/string_column.hpp"

/// Represents a table in the database
class Table {
    /// Number of columns in the table
    int columnCount;

    /// Number of rows in the table
    int rowCount;

    /// The max number of columns that can be saved in the table currently
    int capacity;

    /// The name of the table
    char* name = nullptr;

    /// The file the table is saved in
    char* file = nullptr;

    /// The columns in the table
    TableColumn** columns = nullptr;

    void clear();
    void expand();
    void copy(Table const& other);

public:
    Table();
    Table(char const* _name);
    Table(char const* _name, char const* _file);
    Table(Table const& other);
    Table& operator=(Table const& other);
    ~Table();

    void setName(char const* _name);
    char* getName() const;

    void setFile(char const* _file);
    char* getFile() const;

    void selectElement(int columnIndex, Value* value);
    void deleteElement(int columnIndex, Value* value);
    void insertRow(Value** values);
    void updateElements(int columnIndex, Value* oldValue, Value* newValue);

    void addColumn();

    int countRows(int columnIndex, Value* value);

    Table* innerJoin(Table const& other);

    void showPage(std::ostream& out, int pageSize, int currentPage);

    void sum(std::ostream& out, int columnIndex);
    void product(std::ostream& out, int columnIndex);
    void maximum(std::ostream& out, int columnIndex);
    void minimum(std::ostream& out, int columnIndex);

    friend std::ostream& operator<<(std::ostream& out, Table const& table);
};


#endif //STACK_TABLE_HPP
