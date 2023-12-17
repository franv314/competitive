#include <bits/stdc++.h>
using namespace std;

#define MAXN 100
#define MAXX 1000

bitset<MAXN * MAXX + 1> knapsack;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    knapsack.set(0);
    for (auto x: a) {
        knapsack |= (knapsack << x);
    }

    cout << knapsack.count() - 1 << '\n';
    for (int i = 1; i <= MAXN * MAXX; i++) {
        if (knapsack.test(i)) {
            cout << i << ' ';
        }
    }
    cout << '\n';
}