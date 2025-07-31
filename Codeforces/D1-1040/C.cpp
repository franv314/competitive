#include <bits/stdc++.h>
using namespace std;

int query(vector<int> i) {
    cout << "? " << i.size();
    for (auto x: i) cout << " " << x + 1;
    cout << endl;
    int ans; cin >> ans;
    return ans;
}
void answer(string s) {
    cout << "! " << s << endl;
}

vector<pair<int, int>> magic = {
    {1, 1},
    {2, 3},
    {3, 6},
    {5, 15},
    {8, 36},
    {13, 91},
    {19, 190},
    {28, 406},
    {41, 861},
    {59, 1770},
    {84, 3570},
    {120, 7260},
};

#define BLOCK 12

void solve() {
    int n; cin >> n;

    int l = 0, r = n + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        
        vector<int> q;
        for (int i = 0; i < m; i++) q.push_back(i);

        if (query(q) != 0) r = m;
        else l = m; 
    }
    int sg = l - 1;
    int gs = l == n ? 0 : l;

    string ans;

    for (int i = 0; i < n; i += BLOCK) {
        vector<int> q;
        for (int x = 0; x < BLOCK; x++) {
            q.push_back(sg);
            for (int cnt = 0; cnt < magic[x].first; cnt++) {
                q.push_back(sg);
                q.push_back(min(i + x, n - 1));
            }
            q.push_back(gs);
        }

        int a = query(q) - BLOCK;
        string add;
        int consec = 0;
        for (int x = BLOCK - 1; x >= 0; x--) {
            a -= consec;
            if (a >= magic[x].second) {
                a -= magic[x].second;
                add += ')';
                consec++;
            } else {
                consec = 0;
                add += '(';
            }
        }

        reverse(add.begin(), add.end());
        ans += add;
    }

    ans.resize(n);
    answer(ans);
}

int main() {
    int t; cin >> t;
    while (t--) solve();
}