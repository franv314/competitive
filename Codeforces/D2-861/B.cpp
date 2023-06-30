#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        
        vector<vector<int>> cards(m, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> cards[j][i];
            }
        }

        long long sum = 0;
        for (int j = 0; j < m; j++) {
            sort(cards[j].begin(), cards[j].end());
            for (int i = 0; i < n; i++) {
                sum += cards[j][i] * (long long)(i - n + i + 1);
            }
        }
        cout << sum << "\n";
    }
}