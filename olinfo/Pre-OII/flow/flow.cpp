#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000
#define MAXM 1000
#define MAXK 1000
#define _ << " " <<

struct Point {
    int n, m;
};

int N, M, K, grid[MAXN][MAXM];
Point heads[MAXK + 1], dest[MAXK + 1];

ifstream in("input_001.txt");
ofstream out("output_001.txt");

struct Backtrack {
    int grid[MAXN][MAXN];
    int connected;
    Point heads[MAXK + 1];

    pair<int, int> guessed_move;

    Backtrack(int g[MAXN][MAXM], int c, Point h[MAXK + 1]) {
        for (int n = 0; n < N; n++)
            for (int m = 0; m < M; m++)
                grid[n][m] = g[n][m];
        connected = c;
        for (int k = 0; k <= K; k++)
            heads[k] = h[k];
        guessed_move = {0, 0};
    }
};

bool operator==(Point a, Point b) { return a.n == b.n && a.m == b.m; }
bool operator!=(Point a, Point b) { return a.n != b.n || a.m != b.m; }

void read_input() {
    in >> N >> M >> K;
    for (int k = 0; k <= K; k++)
        dest[k] = {-1, -1};
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            in >> grid[n][m];
            if (dest[grid[n][m]] == (Point){-1, -1}) {
                dest[grid[n][m]] = {n, m};
            } else {
                heads[grid[n][m]] = {n, m};
            }
        }
    }
    heads[0] = {-1, -1};
}

void stdout_output() {
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            printf("%01d ", grid[n][m]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void print_output() {
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            out << grid[n][m] << " ";
        }
        out << "\n";
    }
    out << "\n";
}

int can_move(int n, int m) {
    return (n > 0 && !grid[n - 1][m])
    | ((n < N - 1 && !grid[n + 1][m]) << 1)
    |     ((m > 0 && !grid[n][m - 1]) << 2)
    | ((m < M - 1 && !grid[n][m + 1]) << 3);
}

bool has_reached(int n, int m, int k) {
    return dest[k] == (Point){n + 1, m}
        || dest[k] == (Point){n - 1, m}
        || dest[k] == (Point){n, m - 1}
        || dest[k] == (Point){n, m + 1};
}

void solve() {
    int connected = 0;
    vector<Backtrack> tries;

    while (connected < K) {
        bool added = false;
        bool impossible = false;
        for (int k = 0; k <= K; k++) {
            Point &head = heads[k];

            int n = head.n, m = head.m;
            if (has_reached(n, m, grid[n][m])) {
                head = {-1, -1};
                connected++;
            }
            if (!grid[n][m] || head == (Point){-1, -1})
                continue;
            

            int can = can_move(n, m);
            if (!can) {
                added = true;
                impossible = true;
                break;
            }

            switch (can) {
            case 1:
                grid[n - 1][m] = grid[n][m];
                head.n--;
                added = true;
                break;
            case 2:
                grid[n + 1][m] = grid[n][m];
                head.n++;
                added = true;
                break;
            case 4:
                grid[n][m - 1] = grid[n][m];
                head.m--;
                added = true;
                break;
            case 8:
                grid[n][m + 1] = grid[n][m];
                head.m++;
                added = true;
                break;
            }
        }
        if (!added) {
            tries.push_back({grid, connected, heads});
            for (int k = 1; k <= K; k++) {
                if (heads[k] != (Point){-1, -1}) {
                    Point &head = heads[k];
                    int n = head.n, m = head.m;
                    int can = can_move(head.n, head.m);
                    
                    tries.back().guessed_move = {k, can & -can};
                    switch (can & -can) {
                    case 1:
                        grid[n - 1][m] = grid[n][m];
                        head.n--;
                        break;
                    case 2:
                        grid[n + 1][m] = grid[n][m];
                        head.n++;
                        break;
                    case 4:
                        grid[n][m - 1] = grid[n][m];
                        head.m--;
                        break;
                    case 8:
                        grid[n][m + 1] = grid[n][m];
                        head.m++;
                        break;
                    }
                    break;
                }
            }
        }
        if (impossible) {
            stdout_output();
            for (;;) {
                Backtrack &top = tries.back();
                for (int n = 0; n < N; n++)
                    for (int m = 0; m < M; m++)
                        grid[n][m] = top.grid[n][m];
                connected = top.connected;
                for (int k = 0; k <= K; k++)
                    heads[k] = top.heads[k];

                Point &head = heads[top.guessed_move.first];
                
                int n = head.n, m = head.m;
                int can = can_move(n, m);
                for (int attempt = top.guessed_move.second * 2; attempt <= 8; attempt *= 2) {
                    if (attempt & can) {
                        top.guessed_move.second = attempt;

                        switch (attempt) {
                        case 1:
                            grid[n - 1][m] = grid[n][m];
                            head.n--;
                            break;
                        case 2:
                            grid[n + 1][m] = grid[n][m];
                            head.n++;
                            break;
                        case 4:
                            grid[n][m - 1] = grid[n][m];
                            head.m--;
                            break;
                        case 8:
                            grid[n][m + 1] = grid[n][m];
                            head.m++;
                            break;
                        }
                        goto exitloop;
                    }
                }

                tries.pop_back();
            }
        }
        exitloop:;
    }
}

int main() {
    read_input();
    solve();
    print_output();
    return 0;
}