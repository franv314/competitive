#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<string> board(8);
    for (auto &row: board) cin >> row;

    pair<int, int> qpos;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 'q') {
                qpos = {i, j};
            }
        }
    }

    function<pair<int, int>(int, int, int, int)> get_last = [&](int x, int y, int dx, int dy) {
        if (x < 0 || x >= 8 || y < 0 || y >= 8) return make_pair(x, y);
        if (board[x][y] != '.') return make_pair(x, y);
        return get_last(x + dx, y + dy, dx, dy);
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
            case 'R':
                if (get_last(i + 1, j, +1, 0) == qpos) return void(cout << "YES\n");
                if (get_last(i - 1, j, -1, 0) == qpos) return void(cout << "YES\n");
                if (get_last(i, j + 1, 0, +1) == qpos) return void(cout << "YES\n");
                if (get_last(i, j - 1, 0, -1) == qpos) return void(cout << "YES\n");
                break;
            case 'B':
                if (get_last(i + 1, j + 1, +1, +1) == qpos) return void(cout << "YES\n");
                if (get_last(i + 1, j - 1, +1, -1) == qpos) return void(cout << "YES\n");
                if (get_last(i - 1, j + 1, -1, +1) == qpos) return void(cout << "YES\n");
                if (get_last(i - 1, j - 1, -1, -1) == qpos) return void(cout << "YES\n");
                break;
            case 'Q':
                if (get_last(i + 1, j, +1, 0) == qpos) return void(cout << "YES\n");
                if (get_last(i - 1, j, -1, 0) == qpos) return void(cout << "YES\n");
                if (get_last(i, j + 1, 0, +1) == qpos) return void(cout << "YES\n");
                if (get_last(i, j - 1, 0, -1) == qpos) return void(cout << "YES\n");
                if (get_last(i + 1, j + 1, +1, +1) == qpos) return void(cout << "YES\n");
                if (get_last(i + 1, j - 1, +1, -1) == qpos) return void(cout << "YES\n");
                if (get_last(i - 1, j + 1, -1, +1) == qpos) return void(cout << "YES\n");
                if (get_last(i - 1, j - 1, -1, -1) == qpos) return void(cout << "YES\n");
                break;
            case 'N':
                if (make_pair(i + 2, j + 1) == qpos) return void(cout << "YES\n");
                if (make_pair(i + 2, j - 1) == qpos) return void(cout << "YES\n");
                if (make_pair(i - 2, j + 1) == qpos) return void(cout << "YES\n");
                if (make_pair(i - 2, j - 1) == qpos) return void(cout << "YES\n");
                if (make_pair(i + 1, j + 2) == qpos) return void(cout << "YES\n");
                if (make_pair(i + 1, j - 2) == qpos) return void(cout << "YES\n");
                if (make_pair(i - 1, j + 2) == qpos) return void(cout << "YES\n");
                if (make_pair(i - 1, j - 2) == qpos) return void(cout << "YES\n");
                break;
            case 'P':
                if (make_pair(i - 1, j + 1) == qpos) return void(cout << "YES\n");
                if (make_pair(i - 1, j - 1) == qpos) return void(cout << "YES\n");
                break;
            }
        }
    }

    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}