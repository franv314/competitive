#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
    int N, K;
    cin >> N >> K;

    vector<int> C(N);
    for (int i = 0; i < N; i++) cin >> C[i];
    sort(C.begin(), C.end());

    vector<int> D;

    for (int i = 1; i < N; i++)
        D.push_back(C[i] - C[i - 1]);
    sort(D.rbegin(), D.rend());

    int l = C.back() - C.front();
    for (int i = 0; i < K - 1; i++) {
        l -= D[i];
    }

    cout << "Case #" << t << ": " << l << "\n";
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
