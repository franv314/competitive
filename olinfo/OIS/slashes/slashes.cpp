#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

//  0
// 1 2
//  3
char grid[1000][1000];
bool visited[1000][1000][4];
int cnt;
int N, M;

void dfs(int n, int m, int t) {
    visited[n][m][t] = true;
    
    if (n > 0 && t == 0 && !visited[n - 1][m][3]) dfs(n - 1, m , 3);
    if (n < N - 1 && t == 3 && !visited[n + 1][m][0]) dfs(n + 1, m, 0);
    if (m > 0 && t == 1 && !visited[n][m - 1][2]) dfs(n, m - 1, 2);
    if (m < M - 1 && t == 2 && !visited[n][m + 1][1]) dfs(n, m + 1, 1);

    if (t == 0) {
        if (grid[n][m] == '/' && !visited[n][m][1]) dfs(n, m, 1);
        if (grid[n][m] == '\\' && !visited[n][m][2]) dfs(n, m, 2);
    }
    if (t == 1) {
        if (grid[n][m] == '/' && !visited[n][m][0]) dfs(n, m, 0);
        if (grid[n][m] == '\\' && !visited[n][m][3]) dfs(n, m, 3);
    }
    if (t == 2) {
        if (grid[n][m] == '/' && !visited[n][m][3]) dfs(n, m, 3);
        if (grid[n][m] == '\\' && !visited[n][m][0]) dfs(n, m, 0);
    }
    if (t == 3) {
        if (grid[n][m] == '/' && !visited[n][m][2]) dfs(n, m, 2);
        if (grid[n][m] == '\\' && !visited[n][m][1]) dfs(n, m, 1);
    }
}

int main() {
    cin >> N >> M;
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            cin >> grid[n][m];
        }
    }

    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            for (int i = 0; i < 4; i++) {
                if (!visited[n][m][i]) {
                    cnt++;
                    dfs(n, m, i);
                }
            }
        }
    }

    cout << cnt << endl;
}