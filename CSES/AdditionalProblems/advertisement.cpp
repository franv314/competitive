#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> l(n), r(n);

    {
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] >= a[i]) {
                st.pop();
            }
            l[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
    }

    {
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()] >= a[i]) {
                st.pop();
            }
            r[i] = st.empty() ? n : st.top();
            st.push(i);
        }
    }

    long long best = 0;
    for (int i = 0; i < n; i++) best = max(best, (long long)a[i] * (r[i] - l[i] - 1));

    cout << best << '\n';
}