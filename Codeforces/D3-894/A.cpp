#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<string> carpet(n);
    for (auto &line: carpet) {
        cin >> line;
    }
    int pos = 0;
    char need[] = {'v', 'i', 'k', 'a'};
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (carpet[j][i] == need[pos]) {
                pos++;
                break;
            }
        }
        if (pos == 4) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}