#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    int head_a = 1e9, head_b = 1e9;
    int score = 0;

    for (auto x: a) {
        if ((x > head_a && x > head_b) || (x <= head_a && x <= head_b)) {
            score += (x > head_a && x > head_b);

            if (head_a < head_b) head_a = x;
            else head_b = x;
        } else if (x <= head_a) {
            head_a = x;
        } else {
            head_b = x;
        }
    }

    cout << score << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}