#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N, M; cin >> N >> M;

    if (N > M)
        return cout << "-1\n", 0;
    
    cout << string(M, '.') << '\n';
    for (int i = 1; i < N; i++) {
        cout << string(i, '#') << string(M - i, '.') << '\n';
    }
}