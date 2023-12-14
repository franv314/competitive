#include <bits/stdc++.h>
using namespace std;

#define SIZE 7

int d, ans;
string s;
bool grid[SIZE][SIZE];

void recur(int i, int j) {
    //cout << path << '\n';
    if (i == 0 && j == SIZE - 1) {
        if (d == SIZE * SIZE - 1) ans++;
        return;
    }

    bool can_l = i > 0 && grid[i - 1][j] == false;
    bool can_u = j > 0 && grid[i][j - 1] == false;
    bool can_r = i + 1 < SIZE && grid[i + 1][j] == false;
    bool can_d = j + 1 < SIZE && grid[i][j + 1] == false;

    if (!can_l && !can_r && can_u && can_d) return;
    if (!can_u && !can_d && can_l && can_r) return;

    if (can_l && (s[d] == '?' || s[d] == 'L')) {
        d++;
        grid[i - 1][j] = true;
        
        recur(i - 1, j);
        
        d--;
        grid[i - 1][j] = false;
    }
    if (can_u && (s[d] == '?' || s[d] == 'U')) {
        d++;
        grid[i][j - 1] = true;

        recur(i, j - 1);

        d--;
        grid[i][j - 1] = false;
    }
    if (can_r && (s[d] == '?' || s[d] == 'R')) {
        d++;
        grid[i + 1][j] = true;
        
        recur(i + 1, j);
        
        d--;
        grid[i + 1][j] = false;
    }
    if (can_d && (s[d] == '?' || s[d] == 'D')) {
        d++;
        grid[i][j + 1] = true;

        recur(i, j + 1);

        d--;
        grid[i][j + 1] = false;
    }
}

int main() {
    grid[0][0] = true;
    cin >> s;
    recur(0, 0);
    cout << ans;
}