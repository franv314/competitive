#include <bits/stdc++.h>
using namespace std;

void visita(int N, int *PRE, int *POST, int *SIMM) {
    int pos_in_post[N];
    for (int i = 0; i < N; i++) 
        pos_in_post[POST[i]] = i;
    
    int reached_post = 0;
    int s = 0;
    vector<pair<int, int>> parents = {{-1, -1}};
    for (int i = 0; i < N; i++) {
        if (pos_in_post[PRE[i]] > reached_post) {
            parents.push_back({PRE[i], 0});
        } else if (parents.back().second == 0) {
            SIMM[s++] = PRE[i];
            SIMM[s++] = parents.back().first;
            reached_post = pos_in_post[PRE[i]] + 1;
            parents.back().second++;
        } else {
            SIMM[s++] = PRE[i];
            while (parents.back().second == 1) {
                reached_post = pos_in_post[parents.back().first] + 1;
                parents.pop_back();
            }
            SIMM[s++] = parents.back().first;
            parents.back().second++;
        }
    }
}