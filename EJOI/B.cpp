#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct DSU {
    struct Node {
        int par, sz;
        i64 dst;
        Node() : par(-1), dst(-1), sz(1) { }
    };
    vector<Node> arr;

    pair<int, i64> find(int node) {
        if (arr[node].par == -1)
            return {node, 0};
        
        auto [ans, dst] = find(arr[node].par);
        arr[node].par = ans;
        arr[node].dst = dst + arr[node].dst;
        return {arr[node].par, arr[node].dst};
    }

    void join(int u, int v, int d) {
        auto [pu, du] = find(u);
        auto [pv, dv] = find(v);
        d += du - dv;

        if (arr[pu].sz < arr[pv].sz) {
            swap(pu, pv);
            d *= -1;
        }
        
        arr[pv].par = pu;
        arr[pv].dst = d;
        arr[pu].sz += arr[pv].sz;
    }

    optional<i64> diff(int u, int v) {
        auto [pu, du] = find(u);
        auto [pv, dv] = find(v);

        if (pu != pv)
            return nullopt;
        
        return du - dv;
    }

    void debug() {
        for (auto [par, sz, dst]: arr) {
            cerr << "par " << par << " sz " << sz << " dst " << dst << endl;
        }
        cerr << endl;
    }

    DSU(int n) : arr(n) { }
};

constexpr int MAX = 16;
constexpr int INF = 100;

bool mod_eq(int x, int y, int mod) {
    x %= mod, y %= mod;
    x += mod, y += mod;
    x %= mod, y %= mod;
    return x == y;
}

bool check(optional<i64> status_cor, array<optional<i64>, MAX> status) {
    int val = -1;
    if (status_cor) {
        val = status_cor.value();
    }

    for (int i = MAX - 1; i >= 0; i--) {
        if (status[i]) {
            if (val == -1) {
                val = status[i].value();
            } else if (!mod_eq(val, status[i].value(), 1 << i)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;

    vector<DSU> mod(MAX, DSU(n));
    DSU cor(n);

    while (q--) {
        int x, y, a, b; cin >> x >> y >> a >> b;
        x--, y--;

        int level = b == -1 ? INF : 31 - __builtin_clz(b);
        bool ok = level == INF
            ? cor.diff(y, x).and_then([&](int found) -> optional<bool> { return found == a; }).value_or(true)
            : mod[level].diff(y, x).and_then([&](int found) -> optional<bool> { return mod_eq(found, a, b); }).value_or(true);

        if (!ok) {
            cout << "0\n";
            continue;
        }
        
        array<optional<i64>, MAX> status;
        for (int i = 0; i < MAX; i++)
            status[i] = mod[i].diff(y, x);

        optional<i64> status_cor = cor.diff(y, x);

        if (level == INF)
            status_cor = a;
        else
            status[level] =  a;

        if (!check(status_cor, status)) {
            cout << "0\n";
            continue;
        }

        if (level != INF) {
            for (int l = level; l >= 0; l--)
                if (!mod[l].diff(y, x))
                    mod[l].join(x, y, a);
        } else {
            if (!cor.diff(y, x))
                cor.join(x, y, a);

            for (int l = 0; l < MAX; l++)
                if (!mod[l].diff(y, x))
                    mod[l].join(x, y, a);
        }

        cout << "1\n";
    }
}
