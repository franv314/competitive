#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string temp; cin >> temp;
        deque<bool> s;
        for (auto c: temp) {
            s.push_back(c == '1');
        }
        
        vector<int> inversions;
        int i = 0;
        
        while (s.size() > 1) {
            if (s.front() != s.back()) {
                inversions.push_back(i);
            }
            s.pop_back(); s.pop_front();
            i++;
        }
        bool ok = true;
        for (int j = 0; j < (int)inversions.size() - 1; j++) {
            if (inversions[j + 1] != inversions[j] + 1) {
                ok = false;
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
}