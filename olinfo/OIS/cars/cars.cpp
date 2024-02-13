#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> P(N);
    for (auto &x: P) cin >> x;

    if (is_sorted(P.begin(), P.end())) {
        cout << "0\n";
        return 0;
    }

    int wrong;
    for (int i = 0; i < N - 1; i++) {
        if (P[i] > P[i + 1]) {
            wrong = i;
            break;
        }
    }

    rotate(P.begin(), P.begin() + wrong + 1, P.end());

    if (is_sorted(P.begin(), P.end())) {
        cout << N - 1 - wrong << '\n';
    } else {
        cout << "-1\n";
    }
}