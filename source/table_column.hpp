#ifndef STACK_TABLE_COLUMN_HPP
#define STACK_TABLE_COLUMN_HPP

#include "integer_value.hpp"
#include "float_value.hpp"
#include "string_value.hpp"
#include "null_value.hpp"
#include "dynamic_array.hpp"

#include <typeinfo>
#include <iomanip>

/// Represents the type of data in a column
enum ColumnType {
    Integer = 1,
    FloatingPoint = 2,
    String = 3
};


/// Represents the table column interface
class TableColumn {
public:

    /// Getter for column size
    /// \return count of rows in column
    virtual int size() const = 0;

    /// Getter for column value
    /// \param index index to get from
    /// \return the value of the row
    virtual Value* operator[](int index) = 0;

    /// Update values
    /// \param indexes indexes of rows to update
    /// \param newValue value to replace the old with
    virtual void update(DynamicArray<int> indexes, Value* newValue) = 0;


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
    virtual int countValue(Value* value) = 0;


    /// Print the sum of chosen elements
    /// \param out stream to input result in
    /// \param indexes indexes of elements to calculate
    virtual void sum(std::ostream& out, DynamicArray<int>& indexes) = 0;


    /// Print the product of chosen elements
    /// \param out stream to input result in
    /// \param indexes indexes of elements to calculate
    virtual void product(std::ostream& out, DynamicArray<int>& indexes) = 0;


    /// Print the maximal element
    /// \param out stream to input result in
    /// \param indexes indexes to search within
    virtual void maximum(std::ostream& out, DynamicArray<int>& indexes) = 0;


    /// Print the minimal element
    /// \param out stream to input result in
    /// \param indexes indexes to search within
    virtual void minimum(std::ostream& out, DynamicArray<int>& indexes) = 0;


    /// Get the type of the column
    /// \return type of values saved in the column
    virtual ColumnType columnType() = 0;


    /// Print row
    /// \param out stream to insert row in
    /// \param index index of the row to print
    /// \param width width of the stream output
    virtual void print(std::ostream &out, int index, int width) = 0;


    /// Print row
    /// \param out stream to insert row in
    /// \param index index of the row to print
    virtual void print(std::ostream &out, int index) = 0;



    /// Virtual destructor
    virtual ~TableColumn() = default;
};


#endif //STACK_TABLE_COLUMN_HPP
