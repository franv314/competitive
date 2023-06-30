#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ord_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>; 

long long solve() {
    ord_set<int> vals;
    int N; cin >> N;
    
    long long ans = 0;
    for (int _ = 0; _ < N; _++) {
        int a; cin >> a;
        vals.insert(a);

        if (vals.size() & 1) {
            ans += *vals.find_by_order(vals.size() / 2);
        } else {
            ans += (*vals.find_by_order(vals.size() / 2 - 1) + *vals.find_by_order(vals.size() / 2)) / 2;
        }
    }
    return ans;
}

int main() {
    int T; cin >> T;
    while (T--)
        cout << solve() << "\n";
}