#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto &row: grid) cin >> row;

    int ma = 0;

    vector<int> block(m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') {
                block[j] = i;
            }
        }

        stack<pair<int, int>> st;
        st.emplace(-1, i);
        for (int j = 0; j < m; j++) {
            while (!st.empty() && st.top().second <= block[j]) {
                auto [t1, h] = st.top(); st.pop();
                
                if (st.empty()) break;
                auto [x, t2] = st.top();
                ma = max(ma, (i - h) * (j - x - 1));
            }
            st.emplace(j, block[j]);
        }
        
        while (st.size() > 1) {
            auto [t1, h] = st.top(); st.pop();
                
            auto [x, t2] = st.top();
            ma = max(ma, (i - h) * (m - x - 1));
        }
    }

    cout << ma << '\n';
}