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


void cpp(const long n) {
    string buff_string;
    for (long i = 0; i < n; ++i) {
        buff_string += string(random_word(3)) + " ";
    }
    // cout << buff_string << endl;
    cout << "Cadena lista" << endl;
    const int pos = buff_string.find("IPN");
    if (pos > 0) cout << "Se encontro ipn\n";
    else cout << "No se encontro ipn\n";
}

void c(const long n) {
    Cadenota buff_cadenota(n);
    for (long i = 0; i < n; ++i) {
        const Cadenota current = Cadenota(random_word(3)) + Cadenota(" "); 
        if (i % 1000 == 0) cout << i << " / " << n << endl;
        buff_cadenota = buff_cadenota + (current);
    }
    // cout << buff_cadenota << endl;
    cout << "Cadena lista" << endl;
    bool found = strstr(buff_cadenota.str, "IPN") != NULL;
    if (found) cout << "Se encontro ipn\n";
    else cout << "No se encontro ipn\n";
}
int main() {
    const long n = 100000;
    cpp(n);
    cout << endl;
    return 0;
}