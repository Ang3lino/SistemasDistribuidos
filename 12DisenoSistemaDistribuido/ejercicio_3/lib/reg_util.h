
#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include <iterator> 

#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <cstdlib>      // std::rand, std::srand
#include <memory>		// std::smart
#include <array>


using namespace std; 

struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
};

//Partidos disponibles 2018
char const partidos[9][4] = {"PRI", "PAN", "PRD", "P_T", "VDE", "MVC", "MOR", "PES", "PNL"};

//Entidades federativas
char const entidad[32][3] =  {"AS", "BC", "BS", "CC", "CS", "CH", "CL", "CM", "DF", "DG", "GT", "GR", "HG", "JC", "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TL", "TS", "VZ", "YN", "ZS"};

void print_structure(void *ptr, int size);

inline unique_ptr<FILE, int(*)(FILE*) > 
fopen_smart(const char *fname, const char *mode) ;

inline int file_descriptor(FILE *fp) ;

void save_registers(const char *fname, vector<struct registro > &registers) ;

registro read_first_register(const char *fname) ;

template<int n> array<registro, n> read_registers(const char *fname);
vector<struct registro > get_random_registers(int n);

#endif