#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define _ << " " <<

int N;
int inverses[23];
int total;

void backtrack(string s, int prod, int sum) {
    int last = s.empty() ? 9 : s.back() - '0';
    for (char append = min((9 * N) / prod, last); append > 1; append--) {
        backtrack(s + (char)(append + '0'), prod * append, sum + append);
    }
    if (prod == sum + N - s.size()) {
        int amounts[10] = {};
        long long partial = 1;
        int n = N;
        for (auto c: s) {
            partial = partial * (n--) % MOD * inverses[++amounts[c - 48]] % MOD;
        }
        total = (total + partial) % MOD;
    }
}

int my_pow(int base, int exp) {
    long long res = 1;
    long long curr = base;
    for (; exp; exp >>= 1) {
        if (exp & 1) res = (res * curr) % MOD;
        curr = (curr * curr) % MOD;
    }
    return res;
}

int main() {
    cin >> N;

    for (int i = 1; i < 23; i++) {
        inverses[i] = my_pow(i, MOD - 2);
        cout << inverses[i] << ",\n";
    }

    backtrack("", 1, 0);
    cout << total + 1 << endl;
    return 0;
}