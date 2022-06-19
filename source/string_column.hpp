#ifndef STACK_STRING_COLUMN_HPP
#define STACK_STRING_COLUMN_HPP


#include "table_column.hpp"

/// Represents a column of strings
class StringColumn : public TableColumn {

    /// Number of rows currently in the column
    int count;

    /// The max number of values that can be saved in the column currently
    int capacity;

    /// Rows currently in the column
    Value** elements = nullptr;

    void clear();
    void expand();
    void copy(StringColumn const& other);
    void nullify(int rowCount);

public:
    StringColumn();
    StringColumn(int _count);
    StringColumn(StringColumn const& other);
    StringColumn& operator=(StringColumn const& other);
    ~StringColumn();

    Value* operator[](int index) override;

    void insert(Value* value) override;
    void update(DynamicArray<int> indexes, Value *newValue) override;
    void deleteByIndexes(DynamicArray<int> &indexes) override;
    void select(Value* value, DynamicArray<int>& indexes) const override;

    int countValue(Value* value) override;

    ColumnType columnType() override;
    int size() const override;

    void sum(std::ostream &out, DynamicArray<int> &indexes) override;
    void product(std::ostream &out, DynamicArray<int> &indexes) override;
    void maximum(std::ostream &out, DynamicArray<int> &indexes) override;
    void minimum(std::ostream &out, DynamicArray<int> &indexes) override;

    void print(std::ostream &out, int index) override;
    void print(std::ostream &out, int index, int width) override;
};


#endif //STACK_STRING_COLUMN_HPP
