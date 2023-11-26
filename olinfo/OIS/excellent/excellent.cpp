#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    if (N == 1) cout << "-1\n";
    else if (N % 3 == 0) cout << string(N, '1') + "\n";
    else if (N % 3 == 1) cout << string(N - 2, '1') + "55\n";
    else cout << string(N - 1, '1') + "5\n";
}