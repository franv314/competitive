#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return __gcd(a, b);
}

int main() {
    int N; cin >> N;
    vector<int> P(N + 1);
    vector<bool> V(N + 1);
    for (int i = 1; i <= N; i++) cin >> P[i];

    int g = 0, s = N;
    for (int i = 1; i <= N; i++) {
        if (V[i]) continue;
        s--;
        for (int curr = i; !V[curr]; curr = P[curr]) {
            g = gcd(g, abs(curr - P[curr]));
            V[curr] = true;
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << (g % i ? -1 : s) << " ";
    }
}