#include <bits/stdc++.h>
using namespace std;

#define PRI 100

vector<int> primes;

void sieve() {
    bitset<PRI> is_not_prime;
    for (int i = 2; i < PRI; i++) {
        primes.push_back(i);
        if (!is_not_prime[i]) {
            for (int j = 2 * i; j < PRI; j += i) {
                is_not_prime[j] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;

    sieve();
    while (t--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        bool imp = false;
        vector<set<int>> prime_classes(PRI);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long long x = a[i], y = a[j];
                if (x == y) {
                    imp = true;
                    goto out;
                }
                for (auto p: primes) {
                    if (x % p == y % p) {
                        prime_classes[p].insert(x % p);
                    }
                    if (prime_classes[p].size() == p) {
                        imp = true;
                        goto out;
                    }
                }
            }
        }

        out:
        cout << (imp ? "NO" : "YES") << endl;
    }
}