#include <bits/stdc++.h>
using namespace std;

#define MAXN 10'000'000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    vector<int> sieve(MAXN + 1, -1);
    for (int i = 2; i <= MAXN; i++) {
        if (sieve[i] == -1) {
            for (int j = i; j <= MAXN; j += i) {
                sieve[j] = i;
            }
        }
    }

    int n; cin >> n;
    vector<int> A(n, -1), B(n, -1);

    for (int i = 0; i < n; i++) {
        int x; cin >> x;

        A[i] = sieve[x];
        B[i] = x;

        while (B[i] % sieve[x] == 0) {
            B[i] /= sieve[x];
        }

        if (B[i] == 1) A[i] = B[i] = -1;
    }

    for (auto x: A) cout << x << " "; cout << "\n";
    for (auto x: B) cout << x << " "; cout << "\n";
}