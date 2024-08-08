#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> solve(long long K) {
    if (K == 1) return {{'.'}};

    vector small = solve(K / 2);

    vector doubled(small.size() + 1, vector(small.size() + 1, '.'));
    for (int i = 1; i <= small.size(); i++)
        for (int j = 1; j <= small.size(); j++)
            doubled[i][j] = small[i - 1][j - 1];

    if (small.size() > 1)
        doubled[0][2] = doubled[2][0] = '#';

    if (K % 2 == 0) return doubled;

    vector add_one(doubled.size() + 2, vector(doubled.size() + 2, '.'));
    for (int i = 0; i < doubled.size(); i++)
        for (int j = 2; j <= doubled.size() + 1; j++)
            add_one[i][j] = doubled[i][j - 2];

    for (int i = 1; i <= doubled.size(); i++)
        add_one[i][1] = add_one[doubled.size()][i] = '#';
    
    return add_one;
}
