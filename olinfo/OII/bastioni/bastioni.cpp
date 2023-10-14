#include <bits/stdc++.h>
using namespace std;

int fun(int N, string &S) {
    vector<char> dp(N + 1);
    dp[N] = '.';
    for (int i = N - 1; i >= 0; i--) {
        if (S[i] == '?') dp[i] = dp[i + 1];
        else dp[i] = S[i];
    }

    int cnt = 1;
    char dir = '.';
    for (int i = 0; i < N; i++) {
        if (S[i] == '>') {
            if (dir == '<') {
                cnt++;
                dir = '.';
            } else {
                dir = '>';
            }
        } else if (S[i] == '<') {
            if (dir == '>') {
                cnt++;
                dir = '.';
            } else {
                dir = '<';
            }
        } else {
            if (dir == '>') S[i] = '<';
            else if (dir == '<') S[i] = '>';
            else if (dp[i] == '<') S[i] = '>';
            else S[i] = '<';
            i--;
        }
    }

    return cnt;
}

int arrampicate(int N, string S){
    string s = "";
    int ans = 0;
    for (auto c: S) {
        if (c == '#') {
            ans += fun(s.size(), s);
            s = "";
        } else if (c != '=') {
            s.push_back(c);
        }
    }
    ans += fun(s.size(), s);

    return ans;
}
