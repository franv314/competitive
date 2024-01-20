#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> S(N);

    for (auto &x: S) cin >> x;

    sort(S.rbegin(), S.rend());
    int p = -1;
    map<int, int> freq;

    for (auto x: S) {
        if (++freq[x] == 2) {
            freq[x] = 0;
            if (p == -1) {
                p = x;
            } else {
                cout << (long long)p * x << '\n';
                return 0;
            }
        }
    }

    cout << 0 << '\n';
}