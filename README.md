# OOP-Database
### Task for the OOP course @ FMI.


Write a program supporting operations with simple databases, consisting of **multiple tables**, each table stored in its own file.

The database should be saved in a main file (directory), which contains a list of the tables in the database.

For each table keep a name and a path to a file in which the table data is saved.


#### Supported data types


Each column of a database table has a **type**, and a single table can have columns of multiple different types at the same time. 
The application must be able to support the following column types:

- **Integer**

  _An integer, which may be preceded by a '+' or '-' sign._

- **Floating-point number**

    _A floating-point number, which may be preceded by a '+' or '-' sign._

- **Character string** 

    _A series of random characters enclosed in quotation marks._

- **Blank**

    _Empty cell, specially marked and displayed as "NULL"._


#### Commands


The application should support the following commands:


| Command                                                                          | Description                                                                                                                                               |
|----------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
| **open** _file_                                                                  | Loads the contents of a file                                                                                                                              |
| **close**                                                                        | Closes the currently open file and clears the currently loaded information                                                                                |
| **save**                                                                         | Writes the database changes back to the same file from which the data was read                                                                            |
| **save as** _file_                                                               | Saves the database changes to a different file                                                                                                            |
| **help**                                                                         | Displays brief information about the commands supported by the program                                                                                    |
| **import** _file_                                                                | Creates a new table from a file and saves it in the database                                                                                              |
| **showtables**                                                                   | Displays a list of the names of all loaded tables                                                                                                         |
| **describe** _table_                                                             | Displays information about the column types of a given table                                                                                              |
| **print** _table_                                                                | Displays all rows of a given table with page view support                                                                                                 |
| **export** _table_ _file_                                                        | Saves table information in a file                                                                                                                         |
| **select** _column_ _value_ _table_                                              | Prints all rows that contain the value in the column with the given index                                                                                 |
| **addcolumn** _table_                                                            | Inserts a new column into the table                                                                                                                       |
| **update** _table_ _search-column_ _search-value_ _target-column_ _target-value_ | Updates all rows in the table whose _search-column_ contain _search-value_ so that _target-column_ value becomes _target-value_                           |
| **delete** _table_ _column_ _value_                                              | Deletes all rows in the table whose _column_ contains _value_                                                                                             |
| **insert** _table_ _values_                                                      | Inserts a new row in the table with the corresponding values                                                                                              |
| **innerjoin** _table-1_ _column-1_ _table-2_ _column-2_                          | Performs inner join on two tables using _column-1_ and _column-2_                                                                                         |                                                                                                                                 |
| **rename** _old-table_ _new-table_                                               | Renames a table                                                                                                                                           |
| **count** _table_ _column_ _value_                                               | Counts the rows in the table where _column_ contains _value_                                                                                              |
| **aggregate** _table_ _search-column_ _value_ _target-column_ _operation_        | Performs an operation(**sum**, **product**, **maximum**, **minimum**) on the values in _target-column_ on all rows where _search-column_ contains _value_ |
