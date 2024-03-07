#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    long long k; cin >> k;

    deque<int> perm;
    long long inv = 0;

    for (int i = 1; i <= n; i++) {
        if (inv == k) perm.push_back(i);
        else if (inv + i - 1 <= k) perm.push_front(i), inv += i - 1;
        else perm.insert(perm.end() - (k - inv), i), inv = k;
    }

    for (auto x: perm) cout << x << ' '; cout << '\n';
}