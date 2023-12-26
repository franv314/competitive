#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, x; cin >> n >> x;
    multiset<int> children;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        children.insert(p);
    }

    int count = 0;
    while (!children.empty()) {
        count++;

        int val = *children.begin();
        children.erase(children.begin());

        if (children.empty()) break;

        auto it = children.upper_bound(x - val);
        if (it == children.begin()) continue;
        children.erase(prev(it));
    }

    cout << count << '\n';
}