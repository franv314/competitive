#include <bits/stdc++.h>
using namespace std;

map<int, int> factor(int N) {
    map<int, int> ans;
    for (int i = 2; i * i <= N; i++) {
        while (N % i == 0) {
            ans[i]++;
            N /= i;
        }
    }

    if (N != 1)
        ans[N] += 1;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> V(N);
    for (auto &x: V) cin >> x;

    vector<map<int, int>> factors(N);
    for (int i = 0; i < N; i++) factors[i] = factor(V[i]);

    map<vector<pair<int, int>>, int> cnt;
    long long ans = 0;

    for (int i = N - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            map<int, int> merged;
            for (auto [p, f]: factors[i]) merged[p] += f;
            for (auto [p, f]: factors[j]) merged[p] += f;

            vector<pair<int, int>> key;
            for (auto [p, f]: merged) {
                if (f % 4) {
                    key.emplace_back(p, 4 - (f % 4));
                }
            }

            ans += cnt[key];
        }

        for (int j = i + 1; j < N; j++) {
            map<int, int> merged;
            for (auto [p, f]: factors[i]) merged[p] += f;
            for (auto [p, f]: factors[j]) merged[p] += f;

            vector<pair<int, int>> key;
            for (auto [p, f]: merged) {
                if (f % 4) {
                    key.emplace_back(p, f % 4);
                }
            }

            cnt[key]++;
        }
    }

    cout << ans << '\n';
}