#include <bits/stdc++.h>
using namespace std;

string query(string str) {
    cout << "? " << str << endl;
    string ans; cin >> ans;
    return ans;
}

void answer(string str) {
    cout << "! " << str << endl;
}

void solve() {
    string fst = query("abcde")
               + query("fghij")
               + query("klmno")
               + query("pqrst")
               + query("uvwxy")
               ;

    char occ[5];
    int curr = 0;
    occ[4] = 'z';

    for (int i = 0; i < 25; i++)
        if (fst[i] != 'W')
            occ[curr++] = i + 'a';
    
    string ans(5, occ[4]);
    for (int i = 0; i < min(4, curr); i++) {
        string qry = query(string(5, occ[i]));

        for (int j = 0; j < 5; j++)
            if (qry[j] == 'G')
                ans[j] = occ[i];
    }

    answer(ans);
}

int main() {
    int T; cin >> T;
    while (T--) solve();
}