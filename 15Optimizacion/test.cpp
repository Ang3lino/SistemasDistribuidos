
#include <bits/stdc++.h>
#include <string.h>

#include "./lib/reg_util.h"

using namespace std;

bool cmp(const registro &r, const registro &s) {
    cout << r.celular << endl;
    cout << s.celular << endl;
    return strcmp(r.celular, s.celular) < 0;
}

void validate_regs(vector<registro > &regs) {
    int j = 0;
    char c;
    for (auto &reg: regs) {
        cout << reg.celular << endl;
        int n = strlen(reg.celular);
        for (int i = 0; i < n; ++i) {
            c = reg.celular[i];
            if (!isdigit(c)) {
                cout << c << endl;
                cout << j << endl;
                throw "Aqui hay una inconsistencia";
            }
        }
        ++j;
    }
}

int main() {
    int n = 10000;
    vector <struct registro > registros = get_random_registers(n);
    validate_regs(registros);
    sort(registros.begin(), registros.end(), cmp);
    for (auto &r: registros)
        cout << r.celular << endl;
    return 0;
}

