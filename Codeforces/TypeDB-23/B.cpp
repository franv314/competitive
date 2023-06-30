#include <bits/stdc++.h>
using namespace std;

int factor[1'000'001];
vector<int> primes;

void sieve() {
    for (int i = 2; i <= 1'000'000; i++) {
        if (factor[i] == 0) {
            primes.push_back(i);
            for (int j = 2 * i; j <= 1'000'000; j += i) {
                factor[j] = i;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    sieve();

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int orig = n;
        map<int, int> freqs;

        for (int i = 0; primes[i] * primes[i] * primes[i] <= orig; i++) {
            while (n % primes[i] == 0) {
                freqs[primes[i]]++;
                n /= primes[i];
            }
        }
        if (n == 1) {
        } else if (n > 1'000'000 || factor[n] == 0) {
            freqs[n]++;
        } else {
            freqs[factor[n]]++;
            freqs[n / factor[n]]++;
        }

        long long total = 0;
        while (!freqs.empty()) {
            int mi = INT_MAX;
            for (auto [p, a]: freqs) {
                mi = min(mi, a);
            }
            long long partial = mi;
            vector<map<int, int>::iterator> e;
            for (auto &[p, a]: freqs) {
                partial *= p;
                a -= mi;
                if (a == 0) {
                    e.push_back(freqs.find(p));
                }
            }
            for (auto x: e) freqs.erase(x);

            total += partial;
        }
        cout << total << "\n";
    }
}