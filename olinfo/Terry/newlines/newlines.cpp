#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
    int N;
    cin >> N;

    vector<int> W(N);
    for (int i = 0; i < N; i++) {
        cin >> W[i];
    }
    if (W.back() != -1) W.push_back(-1);

    long long mi = LLONG_MIN, ma = LLONG_MAX;

    long long acc = 0;
    for (int i = 0; i < W.size(); i++) {
        if (W[i] == -1) {
            mi = max(mi, acc - 1);
            if (i != W.size() - 1) ma = min(ma, acc + W[i + 1] - 1);
            acc = 0;
        } else {
            acc += W[i] + 1;
        }
    }

    cout << "Case #" << t << ": " << mi << " " << ma << "\n";
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
