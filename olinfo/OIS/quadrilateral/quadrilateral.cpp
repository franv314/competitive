#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<long long> L(N);
    for (auto &x: L) cin >> x;

    sort(L.rbegin(), L.rend());

    for (int i = 0; i < N - 3; i++) {
        if (L[i + 1] + L[i + 2] + L[i + 3] > L[i]) {
            cout << L[i] << " " << L[i + 1] << " " << L[i + 2] << " " << L[i + 3] << '\n';
            return 0;
        }
    }

    cout << "-1\n";
}