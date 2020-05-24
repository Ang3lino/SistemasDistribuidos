
#ifndef __DBASE__
#define __DBASE__

#include "sqlite3.h"
#include "../Trie.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


// template<typename ... Args>
// std::string string_format( const std::string& format, Args ... args );

std::string str_from_file(std::string fname) ;

struct ResultSet {
    int cols;
    Trie<int> name2int;

    std::vector<std::vector<std::string > > tuples;

    ResultSet();
    ResultSet(int argc, char **column);

    unsigned row_count() ;
    int col_index(std::string key) ;

    void print() ;
    void set_column_names(int argc, char **column) ;
    void put(char **values) ;
};

sqlite3 *db_open(char *fname) ;
char *db_query(sqlite3 *db, std::string query) ;
ResultSet db_query_values(sqlite3 *db, std::string query) ;
int the_callback(void *array_in, int argc, char **argv, char **column) ;


#endif

// Author: Angel Manriquez

