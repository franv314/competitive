#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n % 2 == 0) {
            cout << "-1\n";
            continue;
        }
        deque<int> sol;

        while (n != 1) {
            if (n % 4 == 3) {
                sol.push_front(2);
                n = (n - 1) / 2;
            } else {
                sol.push_front(1);
                n = (n + 1) / 2;
            }
        }
        cout << sol.size() << "\n";
        for (auto x: sol) cout << x << " "; cout << "\n";
    }
}