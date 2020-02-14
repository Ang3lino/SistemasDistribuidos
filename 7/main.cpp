#include <bits/stdc++.h>

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

void c() {
    
}

int main() {
    a();
    return 0;
}