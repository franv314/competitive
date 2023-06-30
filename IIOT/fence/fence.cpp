#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;

    vector<pair<int, int>> s;
    s.push_back({-1, 0});

    for (int i = 0; i < N; i++) {
        int H; cin >> H;
        while (s.size() > 1 && s[s.size() - 2].second >= s[s.size() - 1].second && H >= s[s.size() - 1].second) {
            s.pop_back();
        }
        s.push_back({i, H});
    }
    long long tot = 0;
    for (int i = 0; i < s.size() - 1; i++) {
        tot += (s[i + 1].first - s[i].first) * (long long)min(s[i + 1].second, s[i].second);
    }
    cout << tot;
}