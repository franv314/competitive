#include <bits/stdc++.h>
using namespace std;

int dis[] = {1, 0, 1, 2, 9};

int main() {
    long long n, k; cin >> n >> k;
    long long ans[5];
    ans[0] = 1 * dis[0];
    ans[1] = n * dis[1];
    ans[2] = n * (n - 1) / 2 * dis[2];
    ans[3] = n * (n - 1) * (n - 2) / 6 * dis[3];
    ans[4] = n * (n - 1) * (n - 2) * (n - 3) / 24 * dis[4];
    
    cout << accumulate(ans, ans + k + 1, 0ll);
}