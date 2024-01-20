#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string S; cin >> S;
    int N; cin >> N;

    set<string> U;
    for (int i = 0; i < N; i++) {
        string u; cin >> u;
        U.insert(u);
    }

    if (!U.count(S)) return cout << S << '\n', 0;

    for (int i = 1; ; i++) {
        if (!U.count(S + to_string(i))) return cout << S + to_string(i) << '\n', 0;
    }
}