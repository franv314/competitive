#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main() {
    int T, t;
    cin >> T;

    for (t = 1; t <= T; t++) {
        int N, F, C;
        
        // scrivi in queste variabili la risposta
        int nf, nc;

        cin >> N >> F >> C;

        nf = N / F;
        nc = (N - nf * F) / C;

        cout << "Case #" << t << ": " << nf << " " << nc << endl;
    }
}
