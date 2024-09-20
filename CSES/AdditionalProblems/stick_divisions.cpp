#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n >> n;
    
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        q.push(x);
    }

    long long ans = 0;
    while (q.size() > 1) {
        int x = q.top(); q.pop();
        int y = q.top(); q.pop();
        q.push(x + y);
        ans += x + y;
    }
    
    cout << ans << '\n';
}