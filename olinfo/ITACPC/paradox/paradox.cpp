#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    bool adj[26][26] = {};
    bool tak[26] = {};

    for (int i = 0; i < n; i++) {
        string a, op, b; cin >> a >> op >> b;
        if (op == "<") swap(a, b);
        adj[a[0] - 'a'][b[0] - 'a'] = true;
    }

    for (int i = 0, j; i < 26; i++) {
        for (j = 0; j < 26; j++)
            if (!tak[j] && accumulate(adj[j], adj[j] + 26, 0) == 0)
                break;
        if (j == 26)
            return cout << ":(\n", 0;

        tak[j] = true;
        for (int k = 0; k < 26; k++)
            adj[k][j] = 0;
    }

    cout << ":)\n";
}