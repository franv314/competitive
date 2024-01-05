#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int N; cin >> N;
    long long S; cin >> S;

    vector<int> A(N);
    for (auto &x: A) cin >> x;

    vector<int> p(N);

    long long curr = 0;
    int r = 0;
    for (int l = 0; l < N; l++) {
        while (r != N && curr + A[r] <= S) {
            curr += A[r];
            r++;
        }

        p[l] = r;

        curr -= A[l];
    }

    vector<long long> ans(N + 1);
    ans[N] = 0;

    for (int i = N - 1; i >= 0; i--) {
        ans[i] = ans[p[i]] + N - i;
    }

    cout << accumulate(ans.begin(), ans.end(), 0LL) << '\n';
}