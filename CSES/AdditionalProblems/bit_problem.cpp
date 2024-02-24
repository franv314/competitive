#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    vector<int> sos_1(1 << 20), sos_2(1 << 20);
    vector<int> v(n);
    for (auto &x: v) {
        cin >> x;
        sos_1[x]++;
        sos_2[x]++;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < (1 << 20); j++) {
            if (j & (1 << i)) {
                sos_1[j] += sos_1[j ^ (1 << i)];
            } else {
                sos_2[j] += sos_2[j ^ (1 << i)];
            }
        }
    }

    for (auto x: v) {
        cout << sos_1[x] << ' ' << sos_2[x] << ' ' << n - sos_1[x ^ ((1 << 20) - 1)] << '\n';
    }
}