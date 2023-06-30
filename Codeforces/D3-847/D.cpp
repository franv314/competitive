#include <bits/stdc++.h>
using namespace std;

int solve_tc() {
    int n; cin >> n;

    map<int, int> freq;
    while (n--) {
        int a; cin >> a;
        freq[a]++;
    }

    int runs = 0;
    while (!freq.empty()) {
        int val = freq.begin()->first;

        for (;;) {
            if (freq.find(val) == freq.end()) break;
            if (--freq[val] == 0) freq.erase(val);
            val++;
        }
        runs++;
    }
    return runs;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        cout << solve_tc() << "\n";
    }
}