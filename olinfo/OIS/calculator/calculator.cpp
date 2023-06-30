#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

enum {ADD = '+', SUB = '-', MUL = '*', DIV = '/', MOD = '%',
      AND = '&',  OR = '|', XOR = '^', LSH = '<', RSH = '>'};

struct Construction {
    char op;
    int n_1, n_2;
};

bool operator<(Construction a, Construction b) { return false; }

struct MySet {
    map<int, pair<int, Construction>> vals;

    MySet() {
        for (int i = 1; i < 10000; i++) vals[i] = {INT_MAX, {0, -1, -1}};
    }

    void push_back(pair<int, pair<int, Construction>> val) {
        vals[val.first] = min(vals[val.first], val.second);
    }
};

map<int, pair<int, Construction>> knowns;

void reconstruct(int n) {
    if (n == 1) {
        cout << "(1)";
        return;
    }
    auto k = knowns[n];

    cout << '(';
    reconstruct(k.second.n_1);
    
    if (k.second.op == '>' || k.second.op == '<') cout << k.second.op;
    cout << k.second.op;

    reconstruct(k.second.n_2);
    cout << ')';
}

int main() {

    knowns[1] = {1, {-1, 0, 0}};

    int res;
    for (int it = 0; it < 8; it++) {
        cerr << "Iteration:" _ it _ "Size:" _ knowns.size()  << endl;
        MySet new_numbers;
        for (auto [n_1, w_1]: knowns) {
            cerr << "It" _ it _ "n" _ n_1 << endl;
            for (auto [n_2, w_2]: knowns) {
                auto [p_1, s_1] = w_1;
                auto [p_2, s_2] = w_2;

                // Addition
                res = n_1 + n_2;
                new_numbers.push_back({res, {p_1 + p_2, {ADD, n_1, n_2}}});
                
                // Multiplication
                res = n_1 * n_2;
                new_numbers.push_back({res, {p_1 + p_2, {MUL, n_1, n_2}}});

                // And
                res = n_1 & n_2;
                new_numbers.push_back({res, {p_1 + p_2, {AND, n_1, n_2}}});

                // Or
                res = n_1 | n_2;
                new_numbers.push_back({res, {p_1 + p_2, {OR, n_1, n_2}}});

                // Xor
                res = n_1 ^ n_2;
                new_numbers.push_back({res, {p_1 + p_2, {XOR, n_1, n_2}}});

                // Subtraction
                res = n_1 - n_2;
                new_numbers.push_back({res, {p_1 + p_2, {SUB, n_1, n_2}}});
                res = n_2 - n_1;
                new_numbers.push_back({res, {p_1 + p_2, {SUB, n_2, n_1}}});

                // Division
                res = n_1 / n_2;
                new_numbers.push_back({res, {p_1 + p_2, {DIV, n_1, n_2}}});
                res = n_2 / n_1;
                new_numbers.push_back({res, {p_1 + p_2, {DIV, n_2, n_1}}});

                // Modulo
                res = n_1 % n_2;
                new_numbers.push_back({res, {p_1 + p_2, {MOD, n_1, n_2}}});
                res = n_2 % n_1;
                new_numbers.push_back({res, {p_1 + p_2, {MOD, n_2, n_1}}});

                // Left shift
                res = n_1 << n_2;
                new_numbers.push_back({res, {p_1 + p_2, {LSH, n_1, n_2}}});
                res = n_2 << n_1;
                new_numbers.push_back({res, {p_1 + p_2, {LSH, n_2, n_1}}});

                // Right shift
                res = n_1 >> n_2;
                new_numbers.push_back({res, {p_1 + p_2, {RSH, n_1, n_2}}});
                res = n_2 >> n_1;
                new_numbers.push_back({res, {p_1 + p_2, {RSH, n_2, n_1}}});
            }
        }
        for (auto [n, how]: new_numbers.vals) {
            if (n > 0 && n <= 3000 && how.first != INT_MAX) {
                if (knowns.find(n) == knowns.end())  knowns[n] = how;
                else knowns[n] = min(knowns[n], how);
            }
        }
    }

    cout << "#include<bits/stdc++.h>\n"
            "using namespace std;"
            "int main() {"
            "int N; scanf(\"%d\", &N);"
            "switch(N) {";


    for (int M = 2; M <= 3000; M++) {
        if (knowns.find(M) != knowns.end()) {
            cout << "case " << M << ": puts(\"";
            reconstruct(M);
            cout << "\"); break;";
        }
    }

    cout << "} }";

    return 0;
}