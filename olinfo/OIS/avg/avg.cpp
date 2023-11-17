#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    vector<int> A(N);
    for (auto &x: A) cin >> x;

    long long wsum = (long long)N * K;
    long long sum = accumulate(A.begin(), A.end(), 0LL);

    if (sum < wsum) return cout << "1\n", 0;
    if (sum == wsum) return cout << "0\n", 0;

    sort(A.begin(), A.end());
    int r = 0;
    while (sum > wsum) {
        r++;
        sum -= A.back() - 1;
        A.pop_back();
    }

    cout << r << '\n';
}