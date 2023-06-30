#include <bits/stdc++.h>
using namespace std;

map<int, int> gcd(map<int, int> a, map<int, int> b) {
    for (auto &[p, q]: a) {
        q = min(b[p], q);
    }
    return a;
}

map<int, int> lcm(map<int, int> a, map<int, int> b) {
    for (auto [p, q]: b) {
        a[p] = max(a[p], q);
    }
    return a;
}

map<int, int> mul(map<int, int> a, map<int, int> b) {
    for (auto [p, q]: b) {
        a[p] += q;
    }
    return a;
}

bool div(map<int, int> a, map<int, int> b) {
    for (auto [p, q]: a) {
        if (q > b[p]) return false;
    }
    return true;
}

#define MAXP 1'000'001

vector<int> primes;
vector<int> smallest_prime(MAXP);

void sieve() {
    for (int i = 2; i < MAXP; i++) {
        if (!smallest_prime[i]) {
            primes.push_back(i);
            for (int j = i; j < MAXP; j += i) {
                smallest_prime[j] = i;
            }
        }
    }
}

int main() {
    sieve();
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        
        map<int, int> g_ab;
        map<int, int> l_b;
        int pricetags = 1;
        
        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;

            map<int, int> A, B;
            for (auto p: primes) {
                if (p * p * p > 1e9) break;
                while (a % p == 0) a /= p, A[p]++;
                while (b % p == 0) b /= p, B[p]++;
            }

            if (a <= 1e6) {
                while (a != 1) {
                    A[smallest_prime[a]]++;
                    a /= smallest_prime[a];
                }
            } else A[a]++;
            if (b <= 1e6) {
                while (b != 1) {
                    B[smallest_prime[b]]++;
                    b /= smallest_prime[b];
                }
            } else B[b]++;

            if (i == 0) g_ab = mul(A, B); else g_ab = gcd(g_ab, mul(A, B));
            l_b = lcm(l_b, B);

            if (div(l_b, g_ab)) continue;

            pricetags++;
            l_b = B; g_ab = mul(A, B);
        }
        cout << pricetags << "\n";
    }
}