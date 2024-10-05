#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, K; cin >> N >> K;
    vector<int> A(N);
    for (auto &x: A) cin >> x;

    vector<bool> can(N);
    set<int> h;

    can[0] = true;
    h.insert(A[0]);

    for (int i = 1; i < N; i++) {
        auto it = h.lower_bound(A[i]);

        if (it != h.end() && abs(*it - A[i]) <= K) {
            can[i] = true;
            h.insert(A[i]);
        }

        if (it != h.begin() && abs(*prev(it) - A[i]) <= K) {
            can[i] = true;
            h.insert(A[i]);
        }
    }

    for (auto x: can) cout << x << ' ';
    cout << '\n';
}