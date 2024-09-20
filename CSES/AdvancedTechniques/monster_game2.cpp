#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Line {
    i64 m, q;

    i64 operator()(i64 x) const { return m * x + q; }
};

class LiChaoTree {
    vector<Line> arr;
    vector<int> compress;
    int s;

    void add_line(Line line, int n, int nb, int ne) {
        if (nb + 1 == ne) {
            if (line(compress[n]) < arr[n](compress[n])) {
                arr[n] = line;
            }
            return;
        }

        if (line(compress[2 * n + 1]) <= arr[n](compress[2 * n + 1])) {
            swap(line, arr[n]);
        }

        bool at_start = line(compress[2 * n]) < arr[n](compress[2 * n]);
        bool at_mid = line(compress[2 * n + 1]) < arr[n](compress[2 * n + 1]);

        if (at_start != at_mid) {
            add_line(line, 2 * n, nb, (nb + ne) / 2);
        } else {
            add_line(line, 2 * n + 1, (nb + ne) / 2, ne);
        }
    }

    i64 get_min(int x, int n, int nb, int ne) {
        if (nb + 1 == ne)
            return arr[n](x);
        
        if (compress[2 * n + 1] > x)
            return min(arr[n](x), get_min(x, 2 * n, nb, (nb + ne) / 2));
        else
            return min(arr[n](x), get_min(x, 2 * n + 1, (nb + ne) / 2, ne));
    }

public:
    void add_line(Line line) { add_line(line, 1, 0, s); }
    i64 get_min(int x) { return get_min(x, 1, 0, s); }

    LiChaoTree(const vector<int> vals) {
        s = 1 << (int)ceil(log2(vals.size()));

        arr.assign(2 * s, {0, (i64)1e15});
        compress.resize(2 * s);

        for (int i = 0; i < vals.size(); i++)
            compress[i + s] = vals[i];
        for (int i = vals.size(); i < s; i++)
            compress[i + s] = compress[i + s - 1] + 1;
        for (int i = s - 1; i > 0; i--)
            compress[i] = min(compress[2 * i], compress[2 * i + 1]);
    };
};

int main() {
    int n, x; cin >> n >> x;
    vector<int> s(n), f(n);
    for (auto &x: s) cin >> x;
    for (auto &x: f) cin >> x;

    vector<int> c = s;
    sort(c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    LiChaoTree lichao(c);

    lichao.add_line({x, 0});
    for (int i = 0; i < n - 1; i++) {
        i64 t = lichao.get_min(s[i]);
        lichao.add_line({f[i], t});
    }

    cout << lichao.get_min(s.back()) << '\n';
}
