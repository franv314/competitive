#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    
    if (n == 1) {
        return cout << "01\n", 0;
    }

    vector<int> ans;
    vector<int> status(1 << (n - 1), 3);

    function<void(int)> dfs = [&](int node) {
        if (status[node] & 1) {
            status[node] ^= 1;
            dfs(((node & ~(1 << (n - 2))) << 1));
        }
        if (status[node] & 2) {
            status[node] ^= 2;
            dfs(((node & ~(1 << (n - 2))) << 1) | 1);
        }
        ans.push_back(node);
    };

    dfs(0);
    reverse(ans.begin(), ans.end());

    cout << string(n - 1, '0');
    for (int i = 1; i < (1 << n); i++) {
        cout << (ans[i] & 1);
    }
    cout << "0\n";
}