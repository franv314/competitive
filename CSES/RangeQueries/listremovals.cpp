#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

using ordered_tree = tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    int n; cin >> n;
    ordered_tree list;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        list.insert({i, x});
    }
    
    for (int i = 1; i <= n; i++) {
        int p; cin >> p;
        auto it = list.find_by_order(p - 1);
        cout << it->second << ' ';
        list.erase(it);
    }
}