#include "executor.hpp"

/// Default constructor
Executor::Executor() {
    dbFile = nullptr;
    database = new Database;
    isSaved = true;
}


/// Copy constructor
/// \param other executor to copy
Executor::Executor(Executor const& other) {
    if (other.dbFile) {
        dbFile = new char[strlen(other.dbFile) + 1];
        strcpy(dbFile, other.dbFile);
    }
    if (other.database) {
        database = new Database(*other.database);
    }
    isSaved = false;
}


/// Copy assignment operator
/// \param other executor to copy
/// \return the updated executor
Executor& Executor::operator=(Executor const& other) {
    if (this != &other) {
        delete[] dbFile;
        delete database;

        if (other.dbFile) {
            dbFile = new char[strlen(other.dbFile) + 1];
            strcpy(dbFile, other.dbFile);
        }
        if (other.database) {
            database = new Database(*other.database);
        }
        isSaved = false;
    }
    return *this;
}


/// Destructor
Executor::~Executor() {
    delete database;
    database = nullptr;
}


/// Read value
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
/// \param valueType type of the value to read
/// \return the value
Value* Executor::readValue(std::ostream& out, std::istream& in, ColumnType valueType) {
    out << "Enter value:\n";
    if (valueType == ColumnType::Integer) {
        int temp;
        in >> temp;
        return new IntegerValue(temp);
    }
    else if (valueType == ColumnType::FloatingPoint) {
        double temp;
        in >> temp;
        return new FloatValue(temp);
    }
    else {
        std::string line;
        std::getline(in, line);
        if (line == "NULL") {
            return new NullValue();
        }
        else {
            return new StringValue(line.c_str());
        }
    }
}


bool Executor::chooseFunction(std::ostream& out, std::istream& in) {
    std::string input;
    try {
        std::getline(in, input);
        if (input == "open") { open(out, in); }
        else if (input == "close") { close(out, in); }
        else if (input == "save") { save(out, in); }
        else if (input == "saveas") { saveas(out, in); }
        else if (input == "help") { enter(out, in); }
        else if (input == "import") { import(out, in); }
        else if (input == "showtables") { showtables(out, in); }
        else if (input == "describe") { describe(out, in); }
        else if (input == "print") { print(out, in); }
        else if (input == "export") { export_(out, in); }
        else if (input == "select") { select(out, in); }
        else if (input == "addcolumn") { addcolumn(out, in); }
        else if (input == "update") { update(out, in); }
        else if (input == "delete") { delete_(out, in); }
        else if (input == "insert") { insert(out, in); }
        else if (input == "innerjoin") { innerjoin(out, in); }
        else if (input == "rename") { rename(out, in); }
        else if (input == "count") { count(out, in); }
        else if (input == "aggregate") { aggregate(out, in); }
        else { return exit(out, in); }
        return true;
    }
    catch (std::invalid_argument const& ex) {
        std::cout << ex.what() << '\n';
        return true;
    }
}

/// User interface menu
/// \param out output stream to write the menu in
/// \param in input stream to read user input from
/// \return if the program should exit
bool Executor::enter(std::ostream& out, std::istream& in) {
    out << "\nAvailable commands:\n"
        << "- open       - Open a database file\n"
        << "- close      - Close a database file\n"
        << "- save       - Save database in file\n"
        << "- saveas     - Save database in different file\n"
        << "- help       - Print menu\n\n"
        << "- import     - Import table from file and save in database\n"
        << "- showtables - Show the names of all tables in database\n"
        << "- describe   - Show the types of the columns in a table\n"
        << "- print      - Print table\n"
        << "- export     - Export a table to file\n"
        << "- select     - Print all rows of table containing a value\n"
        << "- addcolumn  - Add column to database\n"
        << "- update     - Update value in a table\n"
        << "- delete     - Delete all rows containing a value in a table\n"
        << "- insert     - Insert a new row in a table\n"
        << "- innerjoin  - Perform innet join on two tables\n"
        << "- rename     - Rename table\n"
        << "- count      - Count all rows containing a value\n"
        << "- aggregate  - Perform operation SUM, PROD, MIN or MAX\n"
        << "- exit       - Exit\n"
        << "\nEnter command:\n";

    return chooseFunction(out, in);
}


/// Open database information from file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::open(std::ostream& out, std::istream& in) {
    std::string str;
    std::ifstream file;
    out << "Enter name of the database file:\n";
    in.ignore();
    std::getline(in, str);

    file.open(str.c_str());
    if (!file) {
        out << "File could NOT be opened!\n";
        return;
    }

    delete[] dbFile;
    dbFile = new char[strlen(str.c_str()) + 1];
    strcpy(dbFile, str.c_str());

    int tableCount;
    in >> tableCount;
    std::getline(in, str);

    for(int i = 0; i < tableCount; i++) {
        database->importTable(in);
    }

    out << "\nFile read successfully!\n";

    file.close();
    isSaved = false;
}


/// Save warehouse information in file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::save(std::ostream& out, std::istream& in) {
    std::ofstream file;
    file.open(dbFile);
    if (!file.good()) {
        out << "File count NOT be opened!\n";
        return;
    }

    out << database->countTables() << "\n";

    for (int i = 0; i < database->countTables(); i++) {
        database->exportTable(out, database->getTableName(i));
    }

    out << "\nDatabase saved successfully!\n";

    file.close();
    isSaved = true;
}


/// Close a database file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::close(std::ostream &out, std::istream &in) {
    if (dbFile) {
        delete[] dbFile;
        dbFile = nullptr;
        delete database;
        database = nullptr;
    }
    isSaved = true;
}


/// Save database in different file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::saveas(std::ostream &out, std::istream &in) {
    std::string str;
    std::ofstream file;
    out << "Enter name of the database file:\n";
    in.ignore();
    std::getline(in, str);

    file.open(str.c_str());
    if (!file.good()) {
        out << "File count NOT be opened!\n";
        return;
    }

    out << database->countTables() << "\n";

    for (int i = 0; i < database->countTables(); i++) {
        database->exportTable(out, database->getTableName(i));
    }

    out << "\nDatabase saved successfully!\n";

    file.close();
    isSaved = true;
}


/// Import table from file and save in database
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::import(std::ostream &out, std::istream &in) {
    std::string str;
    std::ofstream file;
    out << "Enter name of the table file:\n";
    in.ignore();
    std::getline(in, str);

    file.open(str.c_str());
    if (!file.good()) {
        out << "File count NOT be opened!\n";
        return;
    }

    database->importTable(in);

    out << "\nTable added successfully!\n";

    file.close();
    isSaved = false;
}


/// Show the names of all tables in database
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::showtables(std::ostream &out, std::istream &in) {
    database->showTables(out);
}


/// Show the types of the columns in a table
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::describe(std::ostream &out, std::istream &in) {
    std::string str;
    out << "Enter name of the table to describe:\n";
    in.ignore();
    std::getline(in, str);

    database->describe(out, str.c_str());
}


/// Print table
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::print(std::ostream &out, std::istream &in) {
    std::string str;
    out << "Enter name of the table to describe:\n";
    in.ignore();
    std::getline(in, str);

    database->printByPages(out, in, str.c_str());
}


/// Export a table to file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::export_(std::ostream &out, std::istream &in) {
    std::string strTable, strFile;
    std::ofstream file;
    out << "Enter name of the table to export:\n";
    in.ignore();
    std::getline(in, strTable);

    out << "Enter name of the file to export to:\n";
    in.ignore();
    std::getline(in, strFile);

    file.open(strFile.c_str());
    if (!file.good()) {
        out << "File count NOT be opened!\n";
        return;
    }

    database->exportTable(file, strTable.c_str());

    file.close();
}


/// Print all rows of table containing a value
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::select(std::ostream &out, std::istream &in) {
    std::string str;
    int column;
    out << "Enter name of the table:\n";
    in.ignore();
    std::getline(in, str);
    out << "Enter the index of the column:\n";
    in.ignore();
    in >> column;
    in.ignore();
    Value* value = readValue(out, in, database->getColumnType(str.c_str(), column));

    database->select(out, in, str.c_str(), column, value);
    delete value;
}


/// Add column to database
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::addcolumn(std::ostream &out, std::istream &in) {
    std::string str;
    out << "Enter name of the table:\n";
    in.ignore();
    std::getline(in, str);

    database->addColumn(in, out, str.c_str());
    isSaved = false;
}


/// Update value in a table
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::update(std::ostream &out, std::istream &in) {
    std::string strTable;
    int searchCol, replCol;
    out << "Enter name of the table:\n";
    in.ignore();
    std::getline(in, strTable);

    out << "Enter the index of the column to search:\n";
    in.ignore();
    in >> searchCol;

    out << "Enter the index of the column to replace in:\n";
    in.ignore();
    in >> replCol;
    in.ignore();

    Value* valueS = readValue(out, in, database->getColumnType(strTable.c_str(), searchCol));
    Value* valueR = readValue(out, in, database->getColumnType(strTable.c_str(), replCol));

    database->update(strTable.c_str(), searchCol, valueS, replCol, valueR);
    isSaved = false;
    delete valueR;
    delete valueS;
}


/// Delete all rows containing a value in a table
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::delete_(std::ostream &out, std::istream &in) {
    std::string str;
    int column;
    out << "Enter name of the table:\n";
    in.ignore();
    std::getline(in, str);
    out << "Enter the index of the column:\n";
    in.ignore();
    in >> column;
    in.ignore();
    Value* value = readValue(out, in, database->getColumnType(str.c_str(), column));

    isSaved = false;
    database->deleteRows(str.c_str(), column, value);
    delete value;
}


/// Insert a new row in a table
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::insert(std::ostream &out, std::istream &in) {
    std::string str;
    int column;
    out << "Enter name of the table:\n";
    in.ignore();
    std::getline(in, str);

    Value** values = new Value*[database->countColumns(str.c_str())];

    for (int i = 0; i < database->countColumns(str.c_str()); i++) {
        values[i] = readValue(out, in, database->getColumnType(str.c_str(), i));
    }

    for (int i = 0; i < database->countColumns(str.c_str()); i++) {
        delete values[i];
    }
    delete[] values;
}


/// Perform innet join on two tables
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::innerjoin(std::ostream &out, std::istream &in) {
    std::string table1, table2;
    int column1, column2;

    out << "Enter name of the first table:\n";
    in.ignore();
    std::getline(in, table1);
    out << "Enter name of the second table:\n";
    in.ignore();
    std::getline(in, table2);
    out << "Enter the indexes of the columns:\n";
    in.ignore();
    in >> column1, column2;

    database->innerJoin(out, table1.c_str(), column1, table2.c_str(), column2);
}


/// Rename table
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::rename(std::ostream &out, std::istream &in) {
    std::string table1, table2;

    out << "Enter the old name of table:\n";
    in.ignore();
    std::getline(in, table1);
    out << "Enter the new name of table:\n";
    in.ignore();
    std::getline(in, table2);

    database->rename(table1.c_str(), table2.c_str());
}


/// Count all rows containing a value
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::count(std::ostream &out, std::istream &in) {
    std::string str;
    int column;
    out << "Enter name of the table:\n";
    in.ignore();
    std::getline(in, str);
    out << "Enter the index of the column:\n";
    in.ignore();
    in >> column;
    in.ignore();
    Value* value = readValue(out, in, database->getColumnType(str.c_str(), column));

    database->countRows(str.c_str(), column, value);
    delete value;
}


/// Perform operation SUM, PROD, MIN or MAX
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::aggregate(std::ostream &out, std::istream &in) {
    std::string str;
    int columnS, columnA, operation;
    out << "Enter name of the table:\n";
    in.ignore();
    std::getline(in, str);
    out << "Enter the index of the column to search in:\n";
    in.ignore();
    in >> columnS;
    out << "Enter the index of the aggregate in:\n";
    in.ignore();
    in >> columnA;
    in.ignore();
    Value* value = readValue(out, in, database->getColumnType(str.c_str(), columnS));

    out << "Enter operation:\n1 - SUM\n2 - PROD\n3 - MAX\n4 - MIN\n";
    in >> operation;

    database->aggregate(out, str.c_str(), columnS, value, columnA,(Operations) operation);
    delete value;
}


/// Exit
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
/// \return if the program should exit
bool Executor::exit(std::ostream &out, std::istream &in) {
    if (!isSaved) {
        out << "You have an open file with unsaved changes, please select close or save first!\n";
        return true;
    }
    return false;
}
