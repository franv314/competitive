#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    vector<pair<int, int>> wins(N);
    for (int i = 0; i < N; i++) {
        wins[i].second = i + 1;
        string res; cin >> res;
        for (int j = 0; j < N; j++) {
            if (j == i) continue;
            if (res[j] == 'o') wins[i].first--;
            else wins[j].first--;
        }
    }

    sort(wins.begin(), wins.end());
    for (auto [w, p]: wins) cout << p << " ";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}