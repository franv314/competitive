#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N; cin >> N;
    
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    long long ans = 1;
    int pos_b = 0;
    for (int pos_a = 0; pos_a < N; pos_a++) {
        while (pos_b < N && B[pos_b] <= A[pos_a]) pos_b++;
        ans = (ans * (pos_b - pos_a)) % MOD;
    }

    cout << ans << endl; // print the result
    return 0;
}