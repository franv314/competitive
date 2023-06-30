#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e7 + 19;

int curr[MOD], old[MOD];
bitset<MOD> found;
vector<int> values;

int main() {
    int N, K; cin >> N >> K;

    found.set(1);
    values.push_back(1);
    old[1] = 1;
    for (int n = 1; n <= N; n++) {
        vector<int> temp;
        for (auto i: values) {
            curr[i] = 0;
        };

        for (auto i: values) {
            for (int k = 1; k <= 9; k++) {
                int nw = i * k % MOD;
                if (!found[nw]) {
                    found.set(nw);
                    temp.push_back(nw);
                }
                curr[nw] += old[i];
            }
        }

        for (auto i: temp) {
            values.push_back(i);
        }

        for (auto i: values) {
            curr[i] %= MOD;
        }

        swap(curr, old);
    }

    cout << old[K];
}