#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

int main() {
    int n, k; cin >> n >> k;
    
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;
    for (int i = 1; i <= n; i++) {
        t.insert(i);
    }

    int cur = 0;
    for (int i = 0; i < n; i++) {
        cur = (cur + k) % t.size();
        cout << *t.find_by_order(cur) << ' ';
        t.erase(t.find_by_order(cur)); 
    }
}