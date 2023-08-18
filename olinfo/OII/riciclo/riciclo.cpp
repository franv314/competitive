#include <bits/stdc++.h>
using namespace std;

int64_t riciclo(int N, int M, vector<int> T, vector<int> P) {
    int64_t ans = 0;
    int curr = 0;
    for (int i = 0; i <= 30; i++) {
        for (auto t: T) {
            int w = 1 << i;
            if (!(t & w)) continue;
            
            while (w >= (1 << curr)) {
                int can_add = min(w >> curr, P[curr]);
                w -= can_add << curr;
                ans += can_add;
                
                if ((P[curr] -= can_add) == 0 && ++curr >= M) {
                    return ans;
                }
            }
        } 
    }
    return ans;
}