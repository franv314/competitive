#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> V(N);
    for (auto &x: V) cin >> x;
    
    vector<int> dst(N);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int len = 1, j = i;
        for (; !dst[j]; j = V[j]) {
            dst[j] = len++;
        }
        ans = max(len - dst[j], ans);
    }
    cout << ans << endl;
}