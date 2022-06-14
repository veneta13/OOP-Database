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
    void checkIndex(int columnIndex) const;

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

    void addColumn(ColumnType type);
    void insertRow(Value** values);

    void selectElement(int columnIndex, DynamicArray<int>& indexes, Value* value) const;
    void deleteElement(int columnIndex, Value* value);
    void updateElements(int columnIndex, Value* oldValue, Value* newValue);

    int countRows(int columnIndex, Value* value) const;

    Table* innerJoin(Table const& other) const;

    void showPage(std::ostream& out, int pageSize, int currentPage) const;
    void showPage(std::ostream& out, DynamicArray<int> &indexes) const;

    void sum(std::ostream& out, int columnIndex) const;
    void product(std::ostream& out, int columnIndex) const;
    void maximum(std::ostream& out, int columnIndex) const;
    void minimum(std::ostream& out, int columnIndex) const;

    friend std::ostream& operator<<(std::ostream& out, Table const& table);
};


#endif //STACK_TABLE_HPP
