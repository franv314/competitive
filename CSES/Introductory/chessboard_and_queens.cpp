#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> can(8);
    for (auto &row: can) cin >> row;

    vector<int> queens = {0, 1, 2, 3, 4, 5, 6, 7};
    int cnt = 0;
    do {
        bool ok = true;
        for (int i = 0; i < 8; i++)
            if (can[i][queens[i]] == '*')
                ok = false;

        for (int i = 0; i < 8; i++)
            for (int j = i + 1; j < 8; j++)
                if (abs(i - j) == abs(queens[i] - queens[j]))
                    ok = false;
        cnt += ok;
    } while(next_permutation(queens.begin(), queens.end()));
    cout << cnt;
}