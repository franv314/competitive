#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    int n, q; cin >> n >> q;
    ordered_tree<long long> salaries;
    vector<int> salary(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> salary[i];
        salaries.insert(salary[i] * (long long)2e9 + i);
    }
    
    while (q--) {
        char t; cin >> t;
        int a, b; cin >> a >> b;
        if (t == '!') {
            salaries.erase(salary[a] * (long long)2e9 + a);
            salary[a] = b;
            salaries.insert(salary[a] * (long long)2e9 + a);
        } else {
            cout << salaries.order_of_key((long long)2e9 * (b + 1)) - salaries.order_of_key((long long)2e9 * a) << '\n';
        }
    }
}