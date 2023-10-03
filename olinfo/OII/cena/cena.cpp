#include <bits/stdc++.h>
using namespace std;

#define MAXS 100'000
#define MAXP 100
#define MAXF 1000

int amounts[MAXP];
pair<int, int> next_dish[MAXP][MAXF];
int curr_jumps[MAXP];
int ends_at[MAXS][MAXF];

long long conta(int S, int s[], int P, int p[]) {
    for (int i = 0; i < P; i++) {
        if (i != P - 1) {
            if (p[i + 1] != p[i]) next_dish[p[i]][amounts[p[i]]] = {p[i + 1], amounts[p[i + 1]]};
            else next_dish[p[i]][amounts[p[i]]] = {p[i + 1], amounts[p[i + 1]] + 1};
        } else {
            next_dish[p[i]][amounts[p[i]]] = {-1, -1};
        }
        amounts[p[i]]++;
    }

    fill(curr_jumps, curr_jumps + MAXP, -1);

    for (int i = S - 1; i >= 0; i--) {
        for (int j = 0; j < amounts[s[i]]; j++) {
            auto [dish, am] = next_dish[s[i]][j];
            if (dish == -1) ends_at[i][j] = i;
            else if (curr_jumps[dish] == -1) ends_at[i][j] = -1;
            else ends_at[i][j] = ends_at[curr_jumps[dish]][am];
        }
        curr_jumps[s[i]] = i;
    }

    long long ans = 0;
    int l = -1;
    for (int i = 0; i < S; i++) {
        if (p[0] == s[i] && ends_at[i][0] != -1) {
            ans += (long long)(S - ends_at[i][0]) * (i - l);
            l = i;
        }
    }
    return ans;
}
