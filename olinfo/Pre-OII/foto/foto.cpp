#include <bits/stdc++.h>
using namespace std;

bool heights(int N, vector<int> Z, vector<int> &H) {
    auto get_Z = [&](int idx) {
        return (idx < 0 || idx >= N - 1) ? INT_MAX : Z[idx];
    };

    fill(H.begin(), H.end(), -1);

    for (int i = 0; i < N - 1; i++) {
        if (get_Z(i - 1) >= get_Z(i) && (H[i] == -1 || H[i] == get_Z(i))) {
            H[i] = get_Z(i);
        } else if (get_Z(i + 1) >= get_Z(i)) {
            H[i + 1] = get_Z(i);
        } else {
            return false;
        }
    }

    for (auto &h: H) {
        if (h == -1) h = 0;
    }

    return true;
}
