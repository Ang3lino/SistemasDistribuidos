
#include <bits/stdc++.h>
#include <string.h>

using namespace std;


struct registro {
	char celular[11];
	char CURP[19];
	char partido[4];
	struct timeval timestamp;

	bool operator<(const registro& r) {                           
		for (int i = 0; i < 11; ++i) {
			if (celular[i] < r.celular[i])
				return true;
		}
		return false;
	}

	bool operator==(const registro& r) {                           
		for (int i = 0; i < 11; ++i) {
			if (celular[i] == r.celular[i])
				return false;
		}
		return true;
	}
};


int main() {
    vector <struct registro > registros;
    registro r;

    strcpy(r.celular, "12345678901");
    registros.push_back(r);
    strcpy(r.celular, "22345678901");
    registros.push_back(r);
    strcpy(r.celular, "32345678901");
    registros.push_back(r);

    sort(registros.begin(), registros.end());
    for (auto &r: registros)
        cout << r.celular << endl;
    return 0;
}
