#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

struct Fenwick {
    vector<unordered_map<int, int>> amounts;

    void insert(int val, int pos) {
        for (; pos < amounts.size(); pos += (pos & -pos))
            amounts[pos][val]++;
    }

    int query(int val, int pos) {
        int ans = 0;
        for (; pos; pos -= (pos & -pos)) {
            ans += amounts[pos][val];
        }
        return ans;
    }

    Fenwick(int n) : amounts(n + 1) { }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    Fenwick fenwick_even(n), fenwick_odd(n);
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i & 1) fenwick_odd.insert(a[i], (i + 1) / 2);
        else fenwick_even.insert(a[i], i / 2);
    }

    long long ans = 0;
    
    for (int i = 1; i <= n - k / 2; i++) {
        int min_pivot = (k + 1) / 2;
        int max_pivot = n - k / 2;

        int first = max(i, 2 * min_pivot - i);
        int last = min(i + k - 1, 2 * max_pivot - i);

        first = (first + 1) / 2;
        last = (last + 1) / 2;

        int s = last - first + 1;

        int eq;
        if (i & 1) eq = fenwick_odd.query(a[i], last) - fenwick_odd.query(a[i], first - 1);
        else eq = fenwick_even.query(a[i], last) - fenwick_even.query(a[i], first - 1);

        ans += s - eq;
    }
    cout << ans << "\n";
}