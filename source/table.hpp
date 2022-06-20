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
    void checkColumnIndex(int columnIndex) const;
    void checkRowIndex(int rowIndex) const;
    void join(Table*& table, int columnTable1, int columnTable2, Table const& other) const;
    void printRow(std::ostream &out, int index) const;

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

    void describe(std::ostream& out);

    void addColumn(ColumnType type);
    void insertRow(Value** values);
    Value** getRow(int index) const;

    void selectElement(int columnIndex, DynamicArray<int>& indexes, Value* value) const;
    void deleteElement(int columnIndex, Value* value);
    void updateElements(int columnIndex, Value* value, DynamicArray<int>& indexes);

    int countRows(int columnIndex, Value* value) const;

    Table* innerJoin(Table const& other, int columnTable1, int columnTable2) const;

    void showPage(std::ostream& out, int pageSize, int currentPage) const;
    void showPage(std::ostream& out, DynamicArray<int> &indexes, int pageSize, int currentPage) const;

    void sum(std::ostream& out, int columnIndex, DynamicArray<int> &indexes) const;
    void product(std::ostream& out, int columnIndex, DynamicArray<int> &indexes) const;
    void maximum(std::ostream& out, int columnIndex, DynamicArray<int> &indexes) const;
    void minimum(std::ostream& out, int columnIndex, DynamicArray<int> &indexes) const;

    friend std::ostream& operator<<(std::ostream& out, Table const& table);
};


#endif //STACK_TABLE_HPP
