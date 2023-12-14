#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> a(N), b(N);
    for (auto &x: a) {
        cin >> x;
        x--;
    }
    for (auto &x: b) {
        cin >> x;
        x--;
    }

    vector<int> inv_a(N), c(N);
    for (int i = 0; i < N; i++) {
        inv_a[a[i]] = i;
    }

    for (int i = 0; i < N; i++) {
        c[i] = inv_a[b[i]];
    }

    set<int> lis;
    for (auto x: c) {
        auto [it, _] = lis.insert(x);
        if (next(it) != lis.end()) lis.erase(next(it));
    }

    cout << lis.size() << '\n';
}