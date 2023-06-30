#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        vector<pair<int, vector<int>>> seqs(n, {0, vector<int>(n - 1)});

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                cin >> seqs[i].second[j];
            }
        }

        for (int i = 0; i < n; i++) {
            map<int, pair<int, int>> am;
            for (int j = 0; j < n; j++) {
                auto &[i, seq] = seqs[j];
                am[seq[i]].first++;
                am[seq[i]].second = j;
                i++;
            }

            auto [a, f_a] = *am.begin();
            auto [b, f_b] = *prev(am.end());

            if (f_a.first == 1) {
                cout << b << " ";
                seqs[f_a.second].first--;
            } else {
                cout << a << " ";
                seqs[f_b.second].first--;
            }
        }
        cout << "\n";
    }
}