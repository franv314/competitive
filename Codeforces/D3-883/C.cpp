#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, h; cin >> n >> m >> h;
    vector<tuple<int, long long, int>> scores;
    for (int i = 1; i <= n; i++) {
        vector<int> times(m);
        for (auto &t: times) cin >> t;
        sort(times.begin(), times.end());
        long long so_far = 0;
        long long penalty = 0;
        int probs = 0;
        for (auto t: times) {
            so_far += t;
            if (so_far <= h) {
                probs++;
                penalty += so_far;
            } else {
                break;
            }
        }
        scores.push_back({-probs, penalty, i});
    }   
    sort(scores.begin(), scores.end());
    for (int i = 0; i < n; i++) {
        if (get<2>(scores[i]) == 1) {
            cout << i + 1 << '\n';
            return;
        }
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}