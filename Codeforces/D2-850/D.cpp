#include <bits/stdc++.h>
using namespace std;

const char eq[] = {'w', 'i', 'n'};

void solve_tc() {
    int n; cin >> n;
    vector<array<int, 3>> has(n);
    vector<int> ex[3][3];

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
    
        has[i][0] = count(s.begin(), s.end(), 'w');
        has[i][1] = count(s.begin(), s.end(), 'i');
        has[i][2] = count(s.begin(), s.end(), 'n');

        for (int gives = 0; gives < 3; gives++) {
            for (int takes = 0; takes < 3; takes++) {
                if (has[i][gives] > 1 && has[i][takes] == 0) {
                    ex[gives][takes].push_back(i);
                } 
            }
        }
    }

    vector<tuple<int, int, int, int>> exchanges;
    for (int gives = 0; gives < 3; gives++) {
        for (int takes = 0; takes < 3; takes++) {
            while (!ex[gives][takes].empty() && !ex[takes][gives].empty()) {
                int a = ex[gives][takes].back(); ex[gives][takes].pop_back();
                int b = ex[takes][gives].back(); ex[takes][gives].pop_back();
                
                exchanges.push_back({a + 1, gives, b + 1, takes});
                has[a][gives]--; has[b][gives]++;
                has[a][takes]++; has[b][takes]--;
            }
        }
    }

    vector<int> needs(n);

    for (int i = 0; i < n; i++) {
        for (int test = 0; test < 3; test++) {
            assert(has[i][test] != 3);
            if (has[i][test] == 0) needs[i] = test;
        }
    }

    vector<int> givers[3];
    for (int gives = 0; gives < 3; gives++) {
        for (int takes = 0; takes < 3; takes++) {
            for (auto i: ex[gives][takes]) {
                givers[gives].push_back(i);
            }
        }
    }

    while (!givers[0].empty()) {
        int a = givers[0].back(); givers[0].pop_back();
        int b = givers[1].back(); givers[1].pop_back();
        int c = givers[2].back(); givers[2].pop_back();

        if (needs[a] == 1) {
            exchanges.push_back({a + 1, 0, b + 1, 1});
            exchanges.push_back({b + 1, 0, c + 1, 2});
        } else {
            exchanges.push_back({a + 1, 0, c + 1, 2});
            exchanges.push_back({b + 1, 1, c + 1, 0});
        }
    }

    cout << exchanges.size() << "\n";
    for (auto [a, b, c, d]: exchanges) {
        cout << a << " " << eq[b] << " " << c << " " << eq[d] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve_tc();
    }
}