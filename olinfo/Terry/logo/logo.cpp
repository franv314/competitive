#include <bits/stdc++.h>
using namespace std;

void solve(int t){
    int N, M;
    cin >> N >> M;
    vector<string> logo_iniziale(N), logo_finale(N);
    for(auto &x: logo_iniziale)cin >> x;
    for(auto &x: logo_finale)cin >> x;

    int risposta = 42;

    int min_m = INT_MAX, max_m = INT_MIN, min_n = INT_MAX, max_n = INT_MIN;
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            if (logo_iniziale[n][m] != logo_finale[n][m]) {
                min_m = min(min_m, m);
                max_m = max(max_m, m);
                min_n = min(min_n, n);
                max_n = max(max_n, n);
            }
        }
    }

    risposta = min_n == INT_MAX ? 0 : (max_n - min_n + 1) * (max_m - min_m + 1);

    cout << "Case #" << t << ": " << risposta << "\n";
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
