#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> arr(n);
    for (auto &[x, _]: arr) cin >> x;
    for (auto &[_, x]: arr) cin >> x;

    int swaps = 0;
    for (auto &[a, b]: arr) {
        if (a > b) {
            swap(a, b);
            swaps++;
        }
    }

    sort(arr.begin(), arr.end());

    if (!is_sorted(arr.begin(), arr.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    })) {
        return void(cout << "NO\n");
    }

    if (swaps % 2 == 1 && n % 2 == 0) {
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i].first < arr[i + 1].second && arr[i].second < arr[i + 1].first) {
                return void(cout << "YES\n");
            }
        }
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
