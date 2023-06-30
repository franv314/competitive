#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, Q; cin >> N >> Q;
    
    vector<int> C(N), pos_of(N + 1), overtaken(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> C[i];
        pos_of[C[i]] = i;
    }

    int ma = INT_MIN, idx;
    while (Q--) {
        int supera; cin >> supera;
        int pos_supera = pos_of[supera];
        int pos_superato = pos_supera - 1;
        int superato = C[pos_superato];

        overtaken[superato]++;
        if ((overtaken[superato] == ma && superato < idx) || overtaken[superato] > ma) {
            ma = overtaken[superato];
            idx = superato;
        }

        swap(C[pos_supera], C[pos_superato]);
        swap(pos_of[supera], pos_of[superato]);

        cout << idx << "\n";
    }
}