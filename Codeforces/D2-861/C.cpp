#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        string l, r; cin >> l >> r;
        l = string(19 - l.size(), '0') + l;
        r = string(19 - r.size(), '0') + r;
        
        int pos;
        string ans;
        for (pos = 0; pos < 19; pos++) {
            if (l[pos] == r[pos]) {
                ans.push_back(l[pos]);
            } else {
                string ans1 = ans + l[pos], ans2 = ans + r[pos];
                
                vector<string> answers;
                for (int i = l[pos] + 1; i < r[pos]; i++) {
                    answers.push_back(ans + string(19 - ans.size(), i));
                }

                pos++;
                for (int ppos = pos; ppos < 19; ppos++) {
                    for (int i = l[ppos] + 1; i <= '9'; i++) {
                        answers.push_back(ans1 + string(19 - ans1.size(), i));
                    }
                    ans1.push_back(l[ppos]);
                }
                answers.push_back(ans1);

                for (int ppos = pos; ppos < 19; ppos++) {
                    for (int i = r[ppos] - 1; i >= '0'; i--) {
                        answers.push_back(ans2 + string(19 - ans2.size(), i));
                    }
                    ans2.push_back(r[ppos]);
                }
                answers.push_back(ans2);

                for (auto &x: answers) {
                    x = x.substr(x.find_first_not_of('0'));
                }

                ans = *min_element(answers.begin(), answers.end(), [&](string a, string b) {
                    return *max_element(a.begin(), a.end()) - *min_element(a.begin(), a.end()) <
                           *max_element(b.begin(), b.end()) - *min_element(b.begin(), b.end());
                });

                break;
            }
        }
        ans = ans.substr(ans.find_first_not_of('0'));
        cout << ans << endl;
    }
}