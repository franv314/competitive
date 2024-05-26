#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N, K, L; in >> N >> K >> L;
    vector<int> A(N);
    for (auto &x: A) {
        in >> x;
        x %= K;
    }

    if (N == 0) {
        out << 0 << '\n';
        return 0;
    }

    sort(A.begin(), A.end());
    int best = 1e9;

    for (auto it = A.begin(); it != A.end(); it++) {
        if (next(it) != A.end() && *it == *next(it)) continue;

        int cnt_a = upper_bound(A.begin(), A.end(), L + *it) - it - 1;
        int cnt_b = upper_bound(A.begin(), A.end(), L + *it - K) - A.begin();

        best = min(best, cnt_a + cnt_b);
    }

    out << best << '\n';
}