#include <bits/stdc++.h>
using namespace std;

string solve(string N) {
    int rem = accumulate(N.begin(), N.end(), 0) % 3;
    if (rem == 0) return N;
    
    string opt1;
    if (count_if(N.begin(), N.end(), [&](char c){ return c % 3 == rem; }) >= 1) {
        opt1 = N;
        int to_remove = 1;
        for (int i = 0; i < opt1.size() - 1; i++) {
            if (opt1[i] % 3 == rem && opt1[i] < opt1[i + 1]) {
                opt1.erase(i, 1);
                to_remove--;
                break;
            }
        }
        for (int i = opt1.size() - 1; to_remove; i--) {
            if (opt1[i] % 3 == rem) {
                opt1.erase(i, 1);
                to_remove--;
            }
        }

        int start_from = opt1.find_first_not_of("0");
        if (start_from == string::npos) opt1 = "";
        else opt1 = opt1.substr(start_from);
    }

    string opt2;
    if (count_if(N.begin(), N.end(), [&](char c){ return c % 3 == 3 - rem; }) >= 2) {
        opt2 = N;
        int to_remove = 2;
        for (int _ = 0; _ < 2; _++) {
            for (int i = 0; i < opt2.size() - 1; i++) {
                if (opt2[i] % 3 == 3 - rem && opt2[i] < opt2[i + 1]) {
                    opt2.erase(i, 1);
                    to_remove--;
                    break;
                }
            }
        }
        
        for (int i = opt2.size() - 1; to_remove; i--) {
            if (opt2[i] % 3 == 3 - rem) {
                opt2.erase(i, 1);
                to_remove--;
            }
        }

        int start_from = opt2.find_first_not_of("0");
        if (start_from == string::npos) opt2 = "";
        else opt2 = opt2.substr(start_from);
    }
    if (opt1.size() > opt2.size()) return opt1;
    if (opt1.size() < opt2.size()) return opt2;
    return max(opt1, opt2);
}

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        string sol = solve(s);
        cout << (sol.empty() ? "-1" : sol) << "\n";
    }
}