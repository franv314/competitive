#include <bits/stdc++.h>
using namespace std;

void solve(int N, char output[]) {
    ofstream out(output);
    
    for (int dx = 0; dx < N; dx++) {
        for (int xs = 0; xs < N; xs++) {
            for (int x = xs, y = 0; y < N; x = (x + dx) % N, y++) {
                out << y * N + x << " ";
            }
            out << N * N + dx << "\n";
        }
    }
    for (int x = 0; x < N * N; x += N) {
        for (int y = 0; y < N; y++) {
            out << x + y << " "; 
        }
        out << N * (N + 1) << "\n";
    }
    for (int i = N * N; i <= N * (N + 1); i++) {
        out << i << " ";
    }
    out << endl;
}

int main(int argn, char* argv[]) {
    if (argn < 3) {
        return 1;
    }
    solve(stoi(argv[1]), argv[2]);
    return 0;
}