
#include "../lib/sqlite3.h"
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

bool db_query(sqlite3 *db, std::string &query) {
    char *err = NULL;
    sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
    if (err != NULL) {
        printf("%s\n", err);
        return false;
    }
    free(err);
    return true;
}

int main(int argc, char const *argv[])
{
    sqlite3 *db = db_open(NULL);
    std::string query = "CREATE TABLE t (id INT AUTOINCREMENT PRIMARY KEY);";
    db_query(db, query);
    return 0;
}
