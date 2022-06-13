#ifndef STACK_TABLE_COLUMN_HPP
#define STACK_TABLE_COLUMN_HPP

#include "integer_value.hpp"
#include "float_value.hpp"
#include "string_value.hpp"
#include "null_value.hpp"
#include "dynamic_array.hpp"

/// Represents the table column interface
class TableColumn {
public:

    /// Initialize column with NULL
    /// \param rowCount number of rows in the column
    virtual void nullify(int rowCount) = 0;


    /// Update the values
    /// \param oldValue value to update
    /// \param newValue new value
    virtual void update(Value* oldValue, Value* newValue) = 0;


    /// Get the indexes of the rows containing a certain value
    /// \param value element to search for
    /// \param indexes indexes of the rows containing the element
    virtual void select(Value* value, DynamicArray<int>& indexes) const = 0;


    /// Delete selected elements
    /// \param indexes indexes to delete the element from
    virtual void deleteByIndexes(DynamicArray<int>& indexes) = 0;


    /// Insert element at last position in the column
    /// \param value element to insert
    virtual void insert(Value* value) = 0;


    /// Count the rows containing a certain element
    /// \param value element to search for
    /// \return number of rows containing the element
    virtual int count(Value* value) = 0;


    /// Print the sum of all elements of the column
    virtual void sum() = 0;


    /// Print the product of all elements of the column
    virtual void product() = 0;


    /// Print the maximal element of the column
    virtual void maximum() = 0;


    /// Print the minimal element of the column
    virtual void minimum() = 0;
};


#endif //STACK_TABLE_COLUMN_HPP
