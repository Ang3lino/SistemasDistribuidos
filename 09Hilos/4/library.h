
#ifndef LIBRARY_H
#define LIBRARY_H

#include <bits/stdc++.h>

#include <cmath>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void cpu() ;

// -------------------------------------------------------------------------------------------------
string random_sequence(const int &word_count, const int &word_length, const string &separator=" "); 

// |source| mod substr_length must be 0
void create_random_file(const char *source, const char* &filename, const int &substr_length); 
void dd(const char *filename); 

// ---------------------------------------------------------------------
#define numeroElementos 100000000
#define RAM_COUNT 14500000

void ram();


#endif