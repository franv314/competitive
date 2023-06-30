#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s1; cin >> s1;
    string s2; cin >> s2;
    int t, q; cin >> t >> q;
    
    int diff = 0;
    for (int i = 0; i < s1.size(); i++) diff += s1[i] != s2[i];
    
    queue<pair<int, int>> blocks;
    for (int time = 0; time < q; time++) {
        while (!blocks.empty() && blocks.front().second <= time - t) {
            auto [pos, _] = blocks.front(); blocks.pop();
            if (s1[pos] != s2[pos]) diff++;
            
            //cout << "\t" << s1 << " " << s2 << " " << diff << endl;
        }
        
        int type; cin >> type;
        if (type == 1) {
            int pos; cin >> pos;
            pos--;
            
            blocks.push({pos, time});
            if (s1[pos] != s2[pos]) diff--;
            
            //cout << s1 << " " << s2 << " " << diff << endl;
        } else if (type == 3) {
            cout << (diff ? "NO\n" : "YES\n");
        } else {
            int i1, j1, i2, j2; cin >> i1 >> j1 >> i2 >> j2;
            j1--; j2--;
            if (j1 == j2) {
                if (i1 == i2) ;
                else swap(s1[j1], s2[j2]);
            } else {
                if (s1[j1] != s2[j1]) diff--;
                if (s1[j2] != s2[j2]) diff--;
                
                if (i1 == 1 && i2 == 1) swap(s1[j1], s1[j2]);
                if (i1 == 1 && i2 == 2) swap(s1[j1], s2[j2]);
                if (i1 == 2 && i2 == 1) swap(s2[j1], s1[j2]);
                if (i1 == 2 && i2 == 2) swap(s2[j1], s2[j2]);
                
                if (s1[j1] != s2[j1]) diff++;
                if (s1[j2] != s2[j2]) diff++;
            }
        }
    }
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}