#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;

    if (N == 1 && M % 4) {
        cout << -1;
        return 0;
    } 
    if (M == 1 && N % 4) {
        cout << -1;
        return 0;
    }
    if (N % 2 && M % 2) {
        cout << -1;
        return 0;
    }
    if (N % 2 && M % 4 || M % 2 && N % 4) {
        cout << -1;
        return 0;
    }
    
    if (N == 1) {
        cout << M / 4 << "\n";
        for (int i = 0; i < M; i += 4) {
            for (int j = 0; j < 4; j++) cout << i / 4 << " ";
        }
        return 0;
    }
    if (M == 1) {
        cout << N / 4 << "\n";
        for (int i = 0; i < N; i += 4) {
            for (int j = 0; j < 4; j++) cout << i / 4 << "\n";
        }
        return 0;
    }

    if (N % 2 == 0 && M % 2 == 0) {
        cout << N * M / 4 << "\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << j / 2 + i / 2 * (M / 2) << " ";
            }
            cout << "\n";
        }
        return 0;
    }

    if (N % 2) {
        cout << N * M / 4 << "\n";
        for (int i = 0; i < M; i += 4) {
            cout << i / 4 * 3 << " "  << i / 4 * 3 + 1 << " " << i / 4 * 3 + 1 << " " << i / 4 * 3 + 2 << " "; 
        } cout << "\n";
        for (int i = 0; i < M; i += 4) {
            cout << i / 4 * 3 << " "  << i / 4 * 3 + 1 << " " << i / 4 * 3 + 1 << " " << i / 4 * 3 + 2 << " "; 
        } cout << "\n";
        for (int i = 0; i < M; i += 4) {
            cout << i / 4 * 3 << " "  << i / 4 * 3 << " " << i / 4 * 3 + 2 << " " << i / 4 * 3 + 2 << " "; 
        } cout << "\n";

        int delta = M * 3 / 4;

        for (int i = 0; i < N - 3; i++) {
            for (int j = 0; j < M; j++) {
                cout << delta + j / 2 + i / 2 * (M / 2) << " ";
            }
            cout << "\n";
        }
        return 0;
    }

    if (M % 2) {
        cout << N * M / 4 << "\n";
        for (int h = 0; h < N; h += 4) {
            int delta = h / 4 * M;
            
            cout << delta << " " << delta << " " << delta << " ";
            for (int j = 0; j < M - 3; j++) {
                cout << delta + 3 + j / 2 << " ";
            } cout << "\n";

            cout << delta << " " << delta + 1 << " " << delta + 1 << " ";
            for (int j = 0; j < M - 3; j++) {
                cout << delta + 3 + j / 2 << " ";
            } cout << "\n";

            cout << delta + 2 << " " << delta + 1 << " " << delta + 1 << " ";
            for (int j = 0; j < M - 3; j++) {
                cout << (M - 3) / 2 + delta + 3 + j / 2 << " ";
            } cout << "\n";

            cout << delta + 2 << " " << delta + 2 << " " << delta + 2 << " ";
            for (int j = 0; j < M - 3; j++) {
                cout << (M - 3) / 2 + delta + 3 + j / 2 << " ";
            } cout << "\n";
        }

        return 0;
    }

    exit(1);
}