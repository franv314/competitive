#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k; cin >> n >> k;

    vector<int> paper = {n};
    while (k--) {
        int x, l; cin >> x >> l;
        x--;
        paper.insert(paper.begin() + x + 1, paper[x] - l);
        paper[x] = l;
    }

    cout << set<int>(paper.begin(), paper.end()).size() << '\n';
}