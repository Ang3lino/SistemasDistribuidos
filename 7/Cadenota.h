#ifndef CADENOTA_H
#define CADENOTA_H

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Cadenota {
    char *str;
    int capacity, size;

    Cadenota() {
        capacity = 2;
        size = 0;
        str = (char *) malloc(capacity * sizeof(char));
    }

    Cadenota(const char *source) {
        size = strlen(source);
        capacity = 2 * size;
        str = (char *) malloc(capacity * sizeof(char));
        strcpy(str, source);
    }

    Cadenota operator+ (const Cadenota &other) {
        size += other.size;
        if (size > capacity) {
            capacity <<= 1;
            str = (char *) realloc(str, capacity);
        }
        strcat(str, other.str);
        return *this;
    }

    friend ostream & operator << (ostream &, const Cadenota &);
};


ostream& operator << (ostream &out, const Cadenota &self) {
    char *str;
    int capacity, size;
    out << "Capacity: " << self.capacity << endl;
    out << "Size: " << self.size << endl;
    out << "C string: " << self.str << endl;
    return out;
}

#endif