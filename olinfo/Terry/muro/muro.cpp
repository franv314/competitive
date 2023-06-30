#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
    int N, Q;
    cin >> N >> Q;

    vector<int> L(Q);
    for (int i = 0; i < Q; i++) {
        cin >> L[i];
    }
    reverse(L.begin(), L.end());

    int covered = 0, i;
    for (i = 0; i < Q && covered < N; i++) {
        int pos_at = max(0, covered - L[i] + 1);
        covered = pos_at + L[i];
    }

    cout << "Case #" << t << ": " << i << endl;
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
