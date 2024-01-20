#include <bits/stdc++.h>
using namespace std;

struct DBF {
    vector<vector<int>> dbf;

    int longest_match(int i, int j) {
        int ans = 0;
        for (int h = dbf.size() - 1; h >= 0; h--) {
            if (dbf[h][i] == dbf[h][j]) {
                ans += (1 << h);
                (i += (1 << h)) %= dbf[h].size();
                (j += (1 << h)) %= dbf[h].size();
            }
        }
        return ans;
    }

    DBF(string s) {
        dbf.emplace_back(s.size());
        for (int i = 0; i < s.size(); i++) dbf[0][i] = s[i] - '0';

        vector<int> cs(s.size()), cst(s.size()), order(s.size()), order2(s.size()), new_row(s.size()), inv(s.size());
        for (int w = 1; w <= s.size(); w <<= 1) {
            fill(cs.begin(), cs.end(), 0);
            for (auto x: dbf.back()) cs[x]++;

            cst[0] = 0;
            for (int i = 1; i < s.size(); i++) cst[i] = cst[i - 1] + cs[i - 1];

            for (int i = 0; i < s.size(); i++) order[i] = cst[dbf.back()[(i + w) % s.size()]]++;

            cst[0] = 0;
            for (int i = 1; i < s.size(); i++) cst[i] = cst[i - 1] + cs[i - 1];

            for (int i = 0; i < s.size(); i++) inv[order[i]] = i;

            for (auto i: inv) order2[i] = cst[dbf.back()[i]]++;

            for (int i = 0; i < s.size(); i++) inv[order2[i]] = i;

            pair<int, int> old = {-1, -1};
            int used = -1;

            for (auto i: inv) {
                pair<int, int> n = {dbf.back()[i], dbf.back()[(i + w) % s.size()]};
                used += old != n;
                old = n;
                new_row[i] = used;
            }

            dbf.push_back(new_row);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int N; cin >> N;
    string S, T; cin >> S >> T;

    string concat = S;
    transform(T.begin(), T.end(), back_inserter(concat), [&](char x) { return x ^ 1; });

    DBF dbf(concat);

    int Q; cin >> Q;
    while (Q--) {
        int X, Y, L; cin >> X >> Y >> L;
        int longest = dbf.longest_match(X, Y + N);

        if (longest >= L) {
            cout << "1 ";
        } else if (S[X + longest] == '0') {
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }

    cout << '\n';
}