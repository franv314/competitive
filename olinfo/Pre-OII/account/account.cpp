#include <bits/stdc++.h>
using namespace std;

int chiedi(int K);
void rispondi(string S);

void indovina(int N) {
    int curr = N * (N + 1) / 2;
    string ans(N, 'a');
    
    for (char c = 'a' + N - 1; c != 'a'; c--) {
        int pos = chiedi(curr);
        ans[N - pos] = c;

        curr -= pos;
    }
    rispondi(ans);
}