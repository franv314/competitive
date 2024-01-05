#include <bits/stdc++.h>
using namespace std;

int area(int a, int b, int c) {
    if (a + b <= c || a + c <= b || b + c <= a) return 0; 
    return (a + b + c) * (a + b - c) * (a + c - b) * (b + c - a);
}

int query(int i, int j, int k) {
    if (i > j) swap(i, j);
    if (j > k) swap(j, k);
    if (i > j) swap(i, j);

    cout << "? " << i << " " << j << " " << k << endl;
    int ans; cin >> ans;
    return ans;
}

void answer(vector<int> ans) {
    if (ans.empty()) return void(cout << "! -1" << endl);
    cout << "!";
    ans.erase(ans.begin());
    for (auto x: ans) cout << " " << x;
    cout << endl;
}

void solve_brute(int n) {
    vector q(n + 1, vector(n + 1, vector(n + 1, 0)));
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                q[i][j][k] = query(i, j, k);
            }
        }
    }

    vector<int> ans;

    for (int i = 0; i < (1 << (2 * n)); i++) {
        vector<int> arr(n + 1);
        for (int j = 0; j < n; j++) arr[j + 1] = 1 + ((i >> (2 * j)) & 3);

        bool ok = true;

        for (int x = 1; x <= n; x++) {
            for (int y = x + 1; y <= n; y++) {
                for (int z = y + 1; z <= n; z++) {
                    if (q[x][y][z] != area(arr[x], arr[y], arr[z])) {
                        ok = false;
                        break;
                    }
                }
            }
        }

        if (ok) {
            if (!ans.empty()) return answer({});
            ans = arr;
        }
    }

    answer(ans);
}

void solve_smart(int n) {
    mt19937 rng(69420);
    uniform_int_distribution<int> dis(1, n);

    int tx, ty, tz, val;
    for (;;) {
        int x = dis(rng);
        int y = dis(rng);
        int z = dis(rng);
        if (x == y || x == z || y == z) continue;

        int q = query(x, y, z);
        switch (q) {
            case   3: tx = x, ty = y, tz = z, val = 1; goto out1;
            case  48: tx = x, ty = y, tz = z, val = 2; goto out1;
            case 243: tx = x, ty = y, tz = z, val = 3; goto out1;
            case 768: tx = x, ty = y, tz = z, val = 4; goto out1;
        }
    }
    out1:

    vector<int> ans(n + 1);
    ans[tx] = ans[ty] = ans[tz] = val;

    if (val != 1) {
        for (int i = 1; i <= n; i++) {
            if (i == tx || i == ty || i == tz) continue;
            int q = query(i, tx, ty);

            for (int l = 1; l <= 4; l++) {
                if (area(l, val, val) == q) {
                    ans[i] = l;
                    break;
                }
            } 
        }

        return answer(ans);
    }

    int last = 1;
    vector<int> not_ones;
    for (; last <= n && not_ones.size() < 4; last++) {
        if (last == tx || last == ty || last == tz) continue;
        int q = query(last, tx, ty);

        if (q != 0) {
            ans[last] = 1;
        } else {
            not_ones.push_back(last);
        }
    }

    if (not_ones.empty()) {
        return answer(ans);
    }

    int cx = -1, cy = -1, val2;
    for (int i = 0; i < not_ones.size(); i++) {
        for (int j = i + 1; j < not_ones.size(); j++) {
            int q = query(tx, not_ones[i], not_ones[j]);
            
            switch (q) {
                case 15: cx = not_ones[i], cy = not_ones[j], val2 = 2; goto out2;
                case 35: cx = not_ones[i], cy = not_ones[j], val2 = 3; goto out2;
                case 63: cx = not_ones[i], cy = not_ones[j], val2 = 4; goto out2;
            }
        }
    }
    out2:

    if (cx == -1) {
        return answer({});
    }

    ans[cx] = ans[cy] = val2;

    for (auto x: not_ones) {
        if (x == tx || x == ty || x == tz || x == cx || x == cy) continue;
        
        int q = query(x, cx, cy);

        for (int l = 1; l <= 4; l++) {
            if (area(l, val2, val2) == q) {
                ans[x] = l;
                break;
            }
        } 
    }

    for (; last <= n; last++) {
        if (last == tx || last == ty || last == tz || last == cx || last == cy) continue;
        
        int q = query(last, cx, cy);

        for (int l = 1; l <= 4; l++) {
            if (area(l, val2, val2) == q) {
                ans[last] = l;
                break;
            }
        } 
    }

    answer(ans);
}

int main() {
    int n; cin >> n;

    if (n < 9) {
        solve_brute(n);
    } else {
        solve_smart(n);
    }
}