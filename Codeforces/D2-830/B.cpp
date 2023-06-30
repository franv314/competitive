#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n;
        cin >> s;

        char last = ' ';
        int blocks = 0;
        for (auto x: s) {
            if (x != last) blocks++;
            last = x;
        }
        cout << max(blocks - 2 + (s[0] == '1'), 0) << endl;
    }
}