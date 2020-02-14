#include <bits/stdc++.h>
#include "Cadenota.h"

using namespace std;

// ? 
void a() {
    int n;
    string line;
    cin >> n;
    getline(cin, line);
    cout << line ;
}

// A pesar de haber usado at, sigue arrojando una excepcion
void b() {
    // string cadena1("ESCOM");
    // cout << cadena1[6] << endl;
    string cadena2("ESCOM");
    cout << cadena2.at(6) << endl;
}

char *random_word(const int n) {
    char *ans = (char *) malloc((n + 1) * sizeof(char));
    std::random_device rd;
    std::default_random_engine generator(rd()); // rd() provides a random seed
    std::uniform_int_distribution<int> distribution((int) 'A', (int) 'Z');
    for (int i = 0; i < n; ++i) {
        ans[i] = (char) distribution(generator);
    }
    ans[n] = '\0';  
    return ans;
}

void c(const int n) {
    Cadenota buff_cadenota;
    string buff_string;
    for (int i = 0; i < n; ++i) {
        const Cadenota current = Cadenota(random_word(3)) + Cadenota(" "); 
        buff_cadenota = buff_cadenota + (current);
        buff_string += current.str;
    }
    cout << buff_cadenota << endl;
    cout << buff_string << endl;
}

int main() {
    c(10);
    cout << endl;
    return 0;
}