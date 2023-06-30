#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
    int N1, N2, N3, N4;
    cin >> N1 >> N2 >> N3 >> N4;

    int M;
    cin >> M;

    string F1, F2, F3, F4;
    cin >> F1 >> F2 >> F3 >> F4;

    // scrivi in queste variabili la risposta
    int p1, p2, p3, p4;

    const char *f1 = F1.c_str(), *f2 = F2.c_str(), *f3 = F3.c_str(), *f4 = F4.c_str();
    for (p1 = 0; p1 <= N1 - M; p1++) {
        for (p2 = 0; p2 <= N2 - M; p2++) {
            for (p3 = 0; p3 <= N3 - M; p3++) {
                for (p4 = 0; p4 <= N4 - M; p4++) {
                    if (
                        !strncmp(f1 + p1, f2 + p2, M) &&
                        !strncmp(f3 + p3, f4 + p4, M) &&
                        !strncmp(f2 + p2, f3 + p3, M)
                    ) {
                        cout << "Case #" << t << ": " << p1 << " " << p2 << " " << p3 << " " << p4 << endl;
                        return;
                    }
                }
            }
        }
    }
    
}

int main() {
    // le seguenti due righe possono essere utili per leggere e scrivere da file

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }
}
