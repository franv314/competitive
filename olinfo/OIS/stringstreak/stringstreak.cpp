#include <bits/stdc++.h>
using namespace std;

int main() {
    string S; cin >> S;
    int N = S.size();
    int B; cin >> B;
    
    vector<bool> is_ok(N);
    int ma = 0;
    
    for (char c = 'a'; c <= 'z'; c++) {
        for (int i = 0; i < N; i++) {
            is_ok[i] = S[i] == c;
        }
        
        int r = 0;
        int cost = 0;
        deque<pair<int, int>> windows;
        for (int l = 0; l < N; l++) {
            for (;;) {
                if (r == N) break;
                if (is_ok[r]) {
                    r++;
                    continue;
                }
                if (r == 0 || is_ok[r - 1]) {
                    int add = 2;
                    if (cost + add <= B) {
                        cost += add;
                        windows.push_back({r, r + 1});
                        r++;
                    } else {
                        break;
                    }
                } else {
                    int add = 1 << (windows.back().second - windows.back().first);
                    if (cost + add <= B) {
                        cost += add;
                        windows.back().second = r + 1;
                        r++;
                    } else {
                        break;
                    }
                }
            }
            
            ma = max(ma, r - l);
            
            if (is_ok[l]) {
            } else if (l == N || is_ok[l + 1]) {
                cost -= 2;
                windows.pop_front();
            } else {
                windows.front().first = l + 1;
                cost -= 1 << (windows.front().second - windows.front().first);
            }
        }
    }
    
    cout << ma << '\n';
}