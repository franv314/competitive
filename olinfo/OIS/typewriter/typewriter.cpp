#include <bits/stdc++.h>
using namespace std;

int main() {
    string S1, S2, S3; cin >> S1 >> S2 >> S3;

    vector<char> C1, C2, C3;
    vector<int> I1, I2, I3;

    {
        int l = 0;
        for (int r = 1; r <= S1.size(); r++) {
            if (r == S1.size() || S1[r] != S1[r - 1]) {
                C1.push_back(S1[l]);
                I1.push_back(r - l);
                l = r;
            }
        }
    }
    {
        int l = 0;
        for (int r = 1; r <= S2.size(); r++) {
            if (r == S2.size() || S2[r] != S2[r - 1]) {
                C2.push_back(S2[l]);
                I2.push_back(r - l);
                l = r;
            }
        }
    }
    {
        int l = 0;
        for (int r = 1; r <= S3.size(); r++) {
            if (r == S3.size() || S3[r] != S3[r - 1]) {
                C3.push_back(S3[l]);
                I3.push_back(r - l);
                l = r;
            }
        }
    }

    if (C1 != C2 || C2 != C3 || C3 != C1) return cout << "IMPOSSIBLE\n", 0;

    for (int i = 0; i < C1.size(); i++) {
        array<int, 3> x = {I1[i], I2[i], I3[i]};
        sort(x.begin(), x.end());
        cout << string(x[1], C1[i]);
    }
}