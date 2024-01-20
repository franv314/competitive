#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;

    vector<int> A(N), B(M);
    for (auto &x: A) cin >> x;
    for (auto &x: B) cin >> x;

    A.insert(A.begin(), INT_MIN);
    A.push_back(INT_MIN);
    B.insert(B.begin(), INT_MIN);
    B.push_back(INT_MIN);

    int peaks_a = 0, peaks_b = 0;
    for (int i = 1; i <= N; i++) peaks_a += A[i] > A[i - 1] && A[i] > A[i + 1];
    for (int i = 1; i <= M; i++) peaks_b += B[i] > B[i - 1] && B[i] > B[i + 1];

    cout << (long long)peaks_a * peaks_b << '\n';
}