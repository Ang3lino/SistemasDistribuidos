
#include "../lib/sqlite3.h"
#include "../Trie.cpp"
#include <bits/stdc++.h>


sqlite3 *db_open(char *fname) 
{
    sqlite3 *db = NULL;
    sqlite3_open((fname ?  fname: ":memory:"), &db);
    if (!db) fprintf(stderr, "Couldn't open database\n");
    return db;
}

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    std::unique_ptr<char[]> buf( new char[ size ] ); 
    snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

// std::unique_ptr<char *>
char *db_query(sqlite3 *db, std::string query) 
{
    char *err = NULL;
    sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
    if (err != NULL) {
        printf("%s\n", err);
    }
    return err;    
}

std::string str_from_file(std::string fname) 
{
    std::ifstream in(fname);
    std::stringstream buff;
    buff << in.rdbuf();
    return buff.str();
}

struct ResultSet {
    int cols;
    Trie<int> name2int;

    std::vector<std::vector<std::string > > tuples;

    ResultSet(): cols(0) {
    }

    ResultSet(int argc, char **column): cols(argc) {
        set_column_names(argc, column);
    }

    unsigned row_count() { return tuples.size(); }

    void print() {
        for (unsigned i = 0; i < row_count(); ++i) {
            std::cout << i << ": ";
            for (auto &value: tuples[i]) {
                std::cout << value + ", ";
            }
            std::cout << endl;
        }
        std::cout << endl;
        std::cout << endl;
    }

    int col_index(std::string key) {
        return name2int.get(key);
    }

    void set_column_names(int argc, char **column) {
        if (cols == 0) {
            cols = argc;
            for (int i = 0; i < argc; ++i) {
                std::string key = column[i];
                name2int.put(key, i);
            }
        }
    }

    void put(char **values) {
        std::vector<std::string > tuple(cols);
        for (int i = 0; i < cols; ++i) {
            tuple[i] = values[i];
        }
        tuples.push_back(tuple);
    }
};

int the_callback(void *array_in, int argc, char **argv, char **column) 
{
    ResultSet *rset = (ResultSet *) array_in;
    rset->set_column_names(argc, column); 
    rset->put(argv);
    return 0;
}

ResultSet db_query_values(sqlite3 *db, std::string query) 
{
    char *err = NULL;
    ResultSet rset;
    sqlite3_exec(db, query.c_str(), the_callback, &rset, &err);
    if (err != NULL) {
        printf("%s\n", err);
        free(err);
    }
    return rset;
}

int main(int argc, char const *argv[])
{
    sqlite3 *db = db_open(NULL);
    std::string db_def = str_from_file("db.sql"); // define db arch
    char *err = db_query(db, db_def);

    // insertions
    for (int i = 0; i < 10; ++i) {
        auto query = string_format(
            "INSERT INTO registro VALUES ('%d', 'LOMA980824HDFPNN03', 'PRI', 1.584);", i);
        db_query(db, query);
    }

    // read
    ResultSet rset = db_query_values(db, "SELECT * FROM registro;");
    int idx = rset.col_index("timestamp");
    for (auto &tuple: rset.tuples) {
        cout << tuple[idx] << endl;
    }
    if (err != NULL)
        free(err);
    return 0;
}
