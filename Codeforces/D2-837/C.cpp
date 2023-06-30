#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    vector<int> primes;
    vector<bool> factor(32000);
    for (int i = 2; i < 32000; i++) {
        if (!factor[i]) {
            primes.push_back(i);
            for (int j = i; j < 32000; j += i) {
                factor[j] = true;
            }
        }
    }

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        set<int> factors;
        bool found = false;
        while (n--) {
            int a; cin >> a;
            for (auto x: primes) {
                if (a % x) continue;
                if (factors.find(x) != factors.end()) found = true;
                factors.insert(x);
                while (!(a % x)) a /= x;
            }
            if (a != 1) {
                if (factors.find(a) != factors.end()) found = true;
                factors.insert(a);
            }
        }
        cout << (found ? "YES\n" : "NO\n");
    }
}