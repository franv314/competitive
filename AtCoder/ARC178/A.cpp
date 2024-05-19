#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, M; cin >> N >> M;
    vector<int> A(M);
    for (auto &x: A) cin >> x;

    sort(A.begin(), A.end());

    if (A.front() == 1 || A.back() == N) {
        return void(cout << "-1\n");
    }

    vector<int> P(N);
    P[0] = 1;

    set<int> missing;
    for (int i = 2; i <= N; i++)
        missing.insert(i);
    
    for (int i = 1; i < N - 1; i++) {
        if (*next(missing.begin()) == i + 2 && binary_search(A.begin(), A.end(), i + 1)) {
            P[i] = *next(missing.begin());
            missing.erase(next(missing.begin()));
        } else {
            P[i] = *missing.begin();
            missing.erase(missing.begin());
        }
    }
    P[N - 1] = *missing.begin();

    for (auto x: P)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    while (t--) solve();
}