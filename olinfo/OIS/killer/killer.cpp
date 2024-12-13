#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long N, K; cin >> N >> K;
    long long sum = K * (K + 1) / 2;

    if (K == 1 || N == sum || N == sum + 1)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
}