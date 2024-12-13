#include <bits/stdc++.h>
using namespace std;

char conv[3] = {'R', 'G', 'B'};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M, L, K; cin >> N >> M >> L >> K;

    if (K == 0) {
        cout << "YES\n";
        for (int i = 0; i < N; i++)
            cout << string(M, 'R') << '\n';
        return 0;
    }

    int total = (N - L + 1) * (M - L + 1);
    if (L % 3 || total < K)
        return cout << "NO\n", 0;
    
    vector<string> grid(N);

    for (int i = 0; i < N; i++)
        grid[i] = string(M, conv[i % 3]);

    int split = K % (N - L + 1);
    int last_col = (K + (N - L)) / (N - L + 1);

    for (int i = last_col + L - 1; i < M; i++)
        for (int j = 0; j < N; j++)
            grid[j][i] = conv[0];
    
    if (split)
        for (int j = split + L - 1; j < N; j++)
            grid[j][last_col + L - 2] = grid[j - 1][last_col + L - 2];

    cout << "YES\n";
    for (auto row: grid)
        cout << row << '\n';
}