#ifndef STACK_TABLE_COLUMN_HPP
#define STACK_TABLE_COLUMN_HPP


#include "integer_value.hpp"
#include "float_value.hpp"
#include "string_value.hpp"
#include "null_value.hpp"
#include "dynamic_array.hpp"


/// Represents the type of values saved in a column
enum ColumnType {
    Integer = 1,
    FloatingPoint = 2,
    String = 3
};


enum Operations {
    Sum = 1,
    Product = 2,
    Maximum = 3,
    Minimum = 4
};


/// Represents a table column
class TableColumn {
protected:
    /// Number of rows currently in the column
    int count;

    /// The max number of values that can be saved in the column currently
    int capacity;

    /// Rows currently in the column
    Value* elements = nullptr;

    void clear();
    void expand();
    void copy(TableColumn const& other);
    void nullify(int _count);

public:
    TableColumn();
    TableColumn(int _count);
    TableColumn(TableColumn const& other);
    TableColumn& operator=(TableColumn const& other);
    virtual ~TableColumn();

    void deleteByIndexes(DynamicArray<int>& indexes);
};


#endif //STACK_TABLE_COLUMN_HPP
