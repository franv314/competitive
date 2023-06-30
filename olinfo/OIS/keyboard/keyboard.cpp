#include <bits/stdc++.h>
using namespace std;

int jumps[10][10][100'001];

int solve_testcase(string S) {
    for (int j = 0; j < 10; j++) {
        for (int k = j + 1; k < 10; k++) {
            jumps[j][k][0] = 0;
        }
    }
    
    char old = '0';
    
    for (int i = 0; i < S.length(); i++) {
        char next = S[i];
        int start = min(old, next) - 48;
        int end = max(old, next) - 48;

        for (int j = 0; j < 10; j++) {
            for (int k = j + 1; k < 10; k++) {
                jumps[j][k][i + 1] = jumps[j][k][i];
                if (start == j && end == k) {
                    jumps[j][k][i + 1]++;
                }
            }
        }

        old = next;
    }

    int pos[10];
    iota(pos, pos + 10, 0);
    
    int cost = 0;
    for (int j = 0; j < 10; j++) {
        for (int k = j + 1; k < 10; k++) {
            cost += jumps[j][k][S.length()] * abs(pos[j] - pos[k]);
        }
    }

    for (int i = 0; i < S.length(); i++) {
        for (int a = 0; a < 10; a++) {
            for (int b = a + 1; b < 10; b++) {
                int count = 0;
                for (int j = 0; j < 10; j++) {
                    for (int k = j + 1; k < 10; k++) {
                        count += jumps[j][k][i] * abs(pos[j] - pos[k]);
                    }
                }

                int currPos = i > 0 ? S[i - 1] - 48 : 0;

                pos[a] = b; pos[b] = a;

                int nextPos = pos[S[i] - 48];
                count += abs(nextPos - currPos);

                for (int j = 0; j < 10; j++) {
                    for (int k = j + 1; k < 10; k++) {
                        count += (jumps[j][k][S.length()] - jumps[j][k][i + 1]) * abs(pos[j] - pos[k]);
                    }
                }

                pos[a] = a; pos[b] = b;
                cost = min(cost, count);
            }
        }
    }

    return cost;
}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        string S; cin >> S;

        cout << solve_testcase(S) << "\n";
    }

    return 0;
}