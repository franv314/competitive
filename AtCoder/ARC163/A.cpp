#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    string S; cin >> S;
    
    for (int len = 1; len < N; len++) {
        string s1 = S.substr(0, len);
        string s2 = S.substr(len);
    
        if (s1 < s2) {
            cout << "Yes\n";
            return;
        }
    }
    
    cout << "No\n";
}

int main() {
    int T; cin >> T;
    while (T--) solve();
}