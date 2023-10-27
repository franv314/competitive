#include <bits/stdc++.h>
using namespace std;

#define MAX_DIGITS 2223
#define MAXN 5982

struct BigInt {
    uint32_t arr[MAX_DIGITS] = {};
};

void mul(const BigInt &A, uint64_t B, BigInt &C) {
    for (int i = 0; i < MAX_DIGITS; i++) {
        uint64_t prod = B * A.arr[i];
        C.arr[i] += prod % 1'000'000'000;
        if (i < MAX_DIGITS - 1) {
            C.arr[i + 1] += prod / 1'000'000'000;
        }
    }
}

BigInt factorials[MAXN + 1];
int pows_10[] = {1, 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000, 100'000'000};

int main() {
    factorials[0].arr[0] = 1;
    for (int i = 0; i < MAXN; i++) {
        mul(factorials[i], i + 1, factorials[i + 1]);
    }

    int best = 1e9;
    int best_digit;
    array<vector<int>, 10> base;

    {
        vector<int> possible(MAXN);
        iota(possible.begin(), possible.end(), 1);

        for (int i = 0; i < MAX_DIGITS; i++) {
            array<vector<int>, 10> maybe_base;
            for (auto p: possible) {
                maybe_base[(factorials[p].arr[i / 9] / pows_10[i % 9]) % 10].push_back(p);
            }

            int ma = 0;
            for (auto &x: maybe_base) ma = max(ma, (int)x.size());
            if (ma < best) {
                best = ma;
                best_digit = i;
                base = maybe_base;
            }
        }
    }

    int best_digit2[10];
    array<vector<int>, 10> base2[10];

    for (int z = 0; z < 10; z++) {
        int best = 1e9;
        int best_digit;
        array<vector<int>, 10> bbase;

        vector<int> possible = base[z];

        for (int i = 0; i < MAX_DIGITS; i++) {
            array<vector<int>, 10> maybe_base;
            for (auto p: possible) {
                maybe_base[(factorials[p].arr[i / 9] / pows_10[i % 9]) % 10].push_back(p);
            }

            int ma = 0;
            for (auto &x: maybe_base) ma = max(ma, (int)x.size());
            if (ma < best) {
                best = ma;
                best_digit = i;
                bbase = maybe_base;
            }
        }

        base2[z] = bbase;
        best_digit2[z] = best_digit;
    }

    int t; cin >> t;
    while (t--) {

        cout << "? " << best_digit << endl;
        int ans1; cin >> ans1;
        
        cout << "? " << best_digit2[ans1] << endl;
        int ans2; cin >> ans2;
        vector<int> possible = base2[ans1][ans2];

        while (possible.size() > 1) {
            int best = 1e9;
            int best_digit;
            array<vector<int>, 10> new_possible;

            for (int i = 0; i < MAX_DIGITS; i++) {
                array<vector<int>, 10> maybe_new_possible;
                for (auto p: possible) {
                    maybe_new_possible[(factorials[p].arr[i / 9] / pows_10[i % 9]) % 10].push_back(p);
                }

                int ma = 0;
                for (auto &x: maybe_new_possible) ma = max(ma, (int)x.size());
                if (ma < best) {
                    best = ma;
                    best_digit = i;
                    new_possible = maybe_new_possible;
                }
            }

            cout << "? " << best_digit << endl;
            int ans; cin >> ans;
            possible = new_possible[ans];
        }

        cout << "! " << possible[0] << endl;
        string ok; cin >> ok;

        if (ok != "YES") break;
    }
}