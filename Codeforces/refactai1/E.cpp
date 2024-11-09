#include <bits/stdc++.h>
using namespace std;

constexpr int MAXV = 400'000;
constexpr int PRIMES = 33860;

vector<vector<int>> divisors(MAXV + 1);
vector<int> pos_of(MAXV + 1, -1);

unordered_set<bitset<PRIMES>> generators;
vector<unordered_set<bitset<PRIMES>>::iterator> gen_by_i(MAXV + 1);

void precalc() {
    generators.reserve(60000); //updated !
    generators.max_load_factor(0.25); //updated !
    int pos = 0;

    for (int i = 2; i <= MAXV; i++) {
        if (divisors[i].empty()) {
            pos_of[i] = pos++;
            
            bitset<PRIMES> gen;
            gen.set(pos_of[i]);
            gen_by_i[i] = generators.insert(gen).first;

            for (int j = i + i; j <= MAXV; j += i)
                divisors[j].push_back(i);
        }
    }

    for (int i = 2; i <= MAXV; i++) {
        if (divisors[i].empty())
            continue;
        
        bitset<PRIMES> gen;
        for (auto x: divisors[i]) {
            gen |= *gen_by_i[i - x];
        }

        auto [it, ok] = generators.insert(gen);
        gen_by_i[i] = it;
    }
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int prime = -1;

    for (auto x: a) {
        if (divisors[x].empty()) {
            if (prime == -1)
                prime = x;
            else
                return void(cout << "-1\n");
        }
    }

    if (prime == -1)
        return void(cout << "2\n");

    for (auto x: a) {
        if (!(*gen_by_i[x])[pos_of[prime]]) {
            return void(cout << "-1\n");
        }
    }

    cout << prime << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    precalc();
    int t; cin >> t;
    while (t--) solve();
}