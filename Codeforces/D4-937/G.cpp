#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;

    map<string, int> genres, artists;
    vector<int> genre(n), artist(n);
    vector<vector<int>> by_genre, by_artist;

    for (int i = 0; i < n; i++) {
        string g, w; cin >> g >> w;
        
        if (!genres.count(g)) genres[g] = genres.size();
        genre[i] = genres[g];

        if (!artists.count(w)) artists[w] = artists.size();
        artist[i] = artists[w];
    }

    by_genre.resize(genres.size());
    by_artist.resize(artists.size());

    for (int i = 0; i < n; i++) {
        by_genre[genre[i]].push_back(i);
        by_artist[artist[i]].push_back(i);
    }

    vector dp(1 << n, vector(n, 0));
    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
    int ans = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) < 2) continue;

        for (int last = 0; last < n; last++) {
            if (!((mask >> last) & 1)) continue;

            for (auto x: by_genre[genre[last]]) {
                if (x == last) continue;
                dp[mask][last] |= dp[mask ^ (1 << last)][x];
            }
            for (auto x: by_artist[artist[last]]) {
                if (x == last) continue;
                dp[mask][last] |= dp[mask ^ (1 << last)][x];
            }

            if (dp[mask][last]) ans = max(ans, __builtin_popcount(mask));
        }
    }

    cout << n - ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}