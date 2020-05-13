
#include <bits/stdc++.h>
#include <experimental/random>
#include <string.h>

#include "../lib/reg_util.h"
#include "../Trie.cpp"

using namespace std;

bool less_than(const registro &r, const registro &s) {
    return strcmp(r.celular, s.celular) < 0;
}

bool equals(const registro &r, const registro &s) {
    return strcmp(r.celular, s.celular) == 0;
}

void validate_regs(vector<registro > &regs) {
    char c;
    for (auto &reg: regs) {
        int n = strlen(reg.celular);
        for (int i = 0; i < n; ++i) {
            c = reg.celular[i];
            if (!isdigit(c)) {
                cerr << "There's an non digit in reg.celular\n";
            }
        }
    }
}

void search(vector<registro > &regs) {
    int i = std::experimental::randint(0, (int) regs.size() - 1);
    auto r = regs[i];
    // linear
    auto it = find_if(regs.begin(), regs.end(),
            bind(equals, std::placeholders::_1, r));
    if (it == regs.end()) {
        cerr << "Linear search didn't work.\n";
    } else {
        cout << "[OK] Linear search.\t";
    }

    // binary
    if (!binary_search(regs.begin(), regs.end(), r, less_than)) {
        cerr << "Binary search didn't work\n";
    } else {
        cout << "[OK] Binary search\t";
    }

    // trie
    Trie <bool>trie;
    string cel;
    for (auto &reg: regs) {
        cel = string(reg.celular);
        trie.put(cel, true);
    }
    if (!trie.has(string(r.celular))) {
        cerr << "Trie search didn't work\n";
    } else {
        cout << "[OK] Trie search\t";
    }
    cout << endl;
}

int main() {
    int n = 10000;
    vector <struct registro > registros = get_random_registers(n);
    validate_regs(registros);
    sort(registros.begin(), registros.end(), less_than);
    for (int i = 0; i < 100; ++i)
        search(registros);
    return 0;
}

