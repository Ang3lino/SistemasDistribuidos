
#include "dbase.h"


sqlite3 *db_open(char *fname) 
{
    sqlite3 *db = NULL;
    sqlite3_open((fname ?  fname: ":memory:"), &db);
    if (!db) fprintf(stderr, "Couldn't open database\n");
    return db;
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

// ResultSet Member functions
    ResultSet::ResultSet(): cols(0) {
    }

    ResultSet::ResultSet(int argc, char **column): cols(argc) {
        set_column_names(argc, column);
    }

    unsigned ResultSet::row_count() { return tuples.size(); }

    void ResultSet::print() {
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

    int ResultSet::col_index(std::string key) {
        return name2int.get(key);
    }

    void ResultSet::set_column_names(int argc, char **column) {
        if (cols == 0) {
            cols = argc;
            for (int i = 0; i < argc; ++i) {
                std::string key = column[i];
                name2int.put(key, i);
            }
        }
    }

    void ResultSet::put(char **values) {
        std::vector<std::string > tuple(cols);
        for (int i = 0; i < cols; ++i) {
            tuple[i] = values[i];
        }
        tuples.push_back(tuple);
    }

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
