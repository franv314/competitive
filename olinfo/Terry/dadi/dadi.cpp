#include <iostream>
#include <string>

using namespace std;

void solve(int t) {
    int K;
    cin >> K;
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    if (K) {
        int x = min(A, K);
        D += x;
        K -= x;
        A -= x;
    }
    if (K) {
        int x = min(B, K);
        D += x;
        K -= x;
        B -= x;
    }
    if (K) {
        int x = min(C, K);
        D += x;
        K -= x;
        C -= x;
    }
    int risposta = A + 2 * B + 3 * C + 4 * D;

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
