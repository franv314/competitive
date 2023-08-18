#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int N; cin >> N;
    set<int, greater<int>> s;
    for (int i = 0; i < N; i++) {
        int t; cin >> t;
        s.insert(20000 * t + i);
        auto it = s.upper_bound(20000 * t + i);
        if (it != s.end()) s.erase(it);
    }
    cout << s.size();
}