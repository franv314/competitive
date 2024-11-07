#include <bits/stdc++.h>
using namespace std;

vector<int> solve_even(int n) {
    deque<int> ans;

    ans.push_back(5);
    ans.push_back(1);

    int curr = 2;
    while (curr <= n) {
        ans.push_back(curr);
        ans.push_back(2 * curr - 1);
        curr = 2 * curr;
    }

    while (ans.back() > n)
        ans.pop_back();
    
    set<int> used(ans.begin(), ans.end());
    for (int i = 1; i <= n; i++)
        if (!used.count(i))
            ans.push_front(i);

    return {ans.begin(), ans.end()};
}

void solve() {
    int n; cin >> n;
    
    vector<int> ans;

    if (n == 5) {
        ans = {2, 1, 3, 4, 5};
    } else if (n % 2 == 0) {
        ans = solve_even(n);
    } else {
        ans = solve_even(n - 1);
        ans.push_back(n);
    }
    
    int acc = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2) acc |= ans[i];
        else acc &= ans[i];
    }

    cout << acc << '\n';
    for (auto x: ans) cout << x << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}