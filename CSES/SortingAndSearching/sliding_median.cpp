#include <iostream>
#include <bits/extc++.h>
 
using namespace std;
using namespace __gnu_pbds;
 
int n, k, i, v[8<<15];

#define a V.insert(v[i] + i++ / 3e5);
#define b cout << (int)*V.find_by_order((k - 1) / 2) << " ";

main() {
    cin >> n >> k;
    for (int &x: v) cin >> x;
 
    tree<double, null_type, less<double>, rb_tree_tag, tree_order_statistics_node_update> V;
    while (i < k) a
 
    b
    while (i < n) {
        V.erase(v[i - k] + (i - k) / 3e5);
        a b
    }
}