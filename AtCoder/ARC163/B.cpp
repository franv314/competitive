#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;
    int A1, A2; cin >> A1 >> A2;
    vector<int> others(N - 2);
    for (auto &o: others) cin >> o;
    
    sort(others.begin(), others.end());
    
    int best = INT_MAX;
    
    for (int l = 0; l <= N - 2 - M; l++) {
        int r = l + M;
        int mi = others[l], ma = others[r - 1];
        
        int mmi = mi < A1 ? (A1 - mi) : 0;
        int mma = ma > A2 ? (ma - A2) : 0;
        
        best = min(best, mmi + mma);
    }
    cout << best;
}