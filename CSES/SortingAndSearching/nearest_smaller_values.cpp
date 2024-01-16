#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    vector<int> a(n);
    for (auto &x: a) cin >> x;

    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) {
            st.pop();
        }

        cout << (st.empty() ? 0 : st.top() + 1) << ' ';
        st.push(i);
    }
    cout << ' ';
}