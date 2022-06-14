#ifndef STACK_INTEGER_COLUMN_HPP
#define STACK_INTEGER_COLUMN_HPP


#include "table_column.hpp"

/// Represents a column of integers
class IntegerColumn : public TableColumn {

    /// Number of rows currently in the column
    int count;

    /// The max number of values that can be saved in the column currently
    int capacity;

    /// Rows currently in the column
    Value** elements = nullptr;

    void clear();
    void expand();
    void copy(IntegerColumn const& other);
    void nullify(int rowCount);

public:
    IntegerColumn();
    IntegerColumn(int _count);
    IntegerColumn(IntegerColumn const& other);
    IntegerColumn& operator=(IntegerColumn const& other);
    ~IntegerColumn();

    Value* operator[](int index) override;

    void insert(Value* value) override;
    void update(Value* oldValue, Value* newValue) override;
    void deleteByIndexes(DynamicArray<int> &indexes) override;
    void select(Value* value, DynamicArray<int>& indexes) const override;

    int countValue(Value* value) override;

    ColumnType columnType() override;

    void sum(std::ostream& out) override;
    void product(std::ostream& out) override;
    void maximum(std::ostream& out) override;
    void minimum(std::ostream& out) override;
};

#endif //STACK_INTEGER_COLUMN_HPP
