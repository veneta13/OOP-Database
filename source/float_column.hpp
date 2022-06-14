#ifndef STACK_FLOAT_COLUMN_HPP
#define STACK_FLOAT_COLUMN_HPP


#include "table_column.hpp"

/// Represents a column of floating point numbers
class FloatColumn : public TableColumn {

    /// Number of rows currently in the column
    int count;

    /// The max number of values that can be saved in the column currently
    int capacity;

    /// Rows currently in the column
    Value** elements = nullptr;

    void clear();
    void expand();
    void copy(FloatColumn const& other);
    void nullify(int rowCount);

public:
    FloatColumn();
    FloatColumn(int _count);
    FloatColumn(FloatColumn const& other);
    FloatColumn& operator=(FloatColumn const& other);
    ~FloatColumn();

    Value* operator[](int index) override;

    void insert(Value* value) override;
    void update(Value* oldValue, Value* newValue) override;
    void deleteByIndexes(DynamicArray<int> &indexes) override;
    void select(Value* value, DynamicArray<int>& indexes) const override;

    int countValue(Value* value) override;
    int size() const override;

    ColumnType columnType() override;

    void sum(std::ostream& out) override;
    void product(std::ostream& out) override;
    void maximum(std::ostream& out) override;
    void minimum(std::ostream& out) override;

    void print(std::ostream &out, int index, int width) override;
};


#endif //STACK_FLOAT_COLUMN_HPP
