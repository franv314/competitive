#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    string s; cin >> s;

    vector<int> pos_of(1 << n);
    vector<int> xorations(1 << n);
    iota(xorations.begin(), xorations.end(), 0);
    sort(xorations.begin(), xorations.end(), [&](int a, int b) {
        return s[a] < s[b]; 
    });
    
    char old = '$';
    int curr = -1;
    for (auto x: xorations) {
        if (s[x] != old) curr++;
        old = s[x];
        pos_of[x] = curr;
    }
    
    for (int len = 1; len < (1 << n); len <<= 1) {
        vector<pair<int, int>> pairs(1 << n);
        for (int i = 0; i < (1 << n); i++) {
            pairs[i] = {pos_of[i], pos_of[i ^ len]};
        }
        
        iota(xorations.begin(), xorations.end(), 0);
        sort(xorations.begin(), xorations.end(), [&](int a, int b) {
            return pairs[a] < pairs[b];
        });
        
        pair<int, int> old(-1, -1);
        int curr = -1;
        for (auto x: xorations) {
            if (pairs[x] != old) curr++;
            old = pairs[x];
            pos_of[x] = curr;
        }
    }
    for (int i = 0; i < (1 << n); i++) {
        cout << s[i ^ xorations.front()];
    }
}