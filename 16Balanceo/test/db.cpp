
#include "../lib/sqlite3.h"
#include <bits/stdc++.h>
#include <varargs.h>

void db_query(...) 
{
    char *query;
    asprintf(query, __VA_ARGS__);
}

sqlite3 *db_open(char *fname) 
{
    sqlite3 *db = NULL;
    sqlite3_open((fname ?  fname: ":memory:"), &db);
    if (!db) fprintf(stderr, "Couldn't open database\n");
    return db;
}

int main(int argc, char const *argv[])
{
    sqlite3 *db = db_open(NULL);
    
    return 0;
}
