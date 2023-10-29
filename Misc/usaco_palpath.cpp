#include <bits/stdc++.h>
using namespace std;

ifstream in("palpath.in");
ofstream out("palpath.out");

const int MOD = 1e9 + 7;

template<typename T>
class Array {
    int f, l;
    vector<T> arr;

public:
    
    T& operator[](const int &idx) {
        return arr[idx - f];
    }
    
    Array(int f, int l) : f(f), l(l), arr(l - f) { }
    Array(int f, int l, T fill) : f(f), l(l), arr(l - f, fill) { }
};

int main() {
    int N; in >> N;
    auto convert = [&](int x, int y) -> pair<int, int> {
        return {x + y, y - x};
    };
    
    vector<string> old_grid(N);
    for (auto &row: old_grid) in >> row;
    
    Array grid(0, 2 * N, Array<char>(-N, +N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            auto [x, y] = convert(i, j);
            grid[x][y] = old_grid[i][j];
        }
    }
    
    Array dp_curr(-N, +N, Array(-N, +N, 0u)), dp_old(-N, +N, Array(-N, +N, 0u));
    for (int i = 1 - N; i < N; i += 2) {
        dp_old[i][i] = 1;
    }
    
    for (int step = 1; step < N; step++) {
        int t = N - 1 - step;
        int b = N - 1 + step;
        
        for (int t_x = -t; t_x <= t; t_x += 2) {
            for (int b_x = -t; b_x <= t; b_x += 2) {
                if (grid[t][t_x] != grid[b][b_x]) dp_curr[t_x][b_x] = 0;
                else dp_curr[t_x][b_x] = (
                    dp_old[t_x + 1][b_x + 1] +
                    dp_old[t_x + 1][b_x - 1] + 
                    dp_old[t_x - 1][b_x + 1] + 
                    dp_old[t_x - 1][b_x - 1] ) % MOD;
            }
        }
        
        swap(dp_old, dp_curr);
    }
    out << dp_old[0][0];
}