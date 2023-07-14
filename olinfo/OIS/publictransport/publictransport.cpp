#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000
#define LOG(x) (31 - __builtin_clz(x))
typedef long long i64;

template<typename T>
class SparseTable {
    vector<vector<T>> table;
 
public:
 
    T query(int l, int r) {
        int d = r - l;
        int h = LOG(d);
        return min(table[h][l], table[h][r - (1 << h)]);
    }
 
    SparseTable() { }
    SparseTable(vector<T> vals) : table(1 + LOG(vals.size()), vector<T>(vals.size())) {
        table[0] = vals;
        for (int h = 1; h <= LOG(vals.size()); h++) {
            for (int i = 0; i < vals.size(); i++) {
                table[h][i] = min(table[h - 1][i], table[h - 1][min((int)vals.size(), i + (1 << (h - 1)))]);
            }
        }
    }
};

struct Line {
    int height;
    i64 m, q;
    
    i64 operator()(int x) {
        return m * x + q;
    }
    
    Line(int height, i64 m, i64 q) : height(height), m(m), q(q) { }
    Line() : Line(-1, 1e12, 1e18) { }
};

class LiChaoTree {
    struct Node {
        Line line;
        int nb, ne;
        Node *lc, *rc;
        
        Node(int nb, int ne, Node *lc, Node *rc) :
            line(), nb(nb), ne(ne), lc(lc), rc(rc) { } 
    } *root;
    
    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return new Node(nb, ne, NULL, NULL);
        return new Node(nb, ne, build(nb, (nb + ne) / 2), build((nb + ne) / 2, ne));
    }
    
    void add(Line line, Node *node) {
        int m = (node->nb + node->ne) / 2;
        if (line(m) < node->line(m)) {
            swap(line, node->line);
        }
        if (node->nb + 1 == node->ne) return;
        
        bool intersect_l = (line(node->nb) < node->line(node->nb)) != (line(m) < node->line(m));
        if (intersect_l) {
            add(line, node->lc);
        } else {
            add(line, node->rc);
        }
    }
    
    Line query(int x, Node *node) {
        if (node->nb + 1 == node->ne) return node->line;
        
        Line rec = x < (node->nb + node->ne) / 2 ? query(x, node->lc) : query(x, node->rc);
        if (rec(x) < node->line(x)) return rec;
        else return node->line;
    }
    
public:

    void add(Line line) { return add(line, root); }
    Line query(int x) { return query(x, root); }
    LiChaoTree(int len) { root = build(0, len); }
};

unordered_map<int, Line> high[MAXN], low[MAXN];

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M, Q; cin >> N >> M >> Q;
    vector<int> S(N), T(N - 1);
    vector<array<int, 3>> queries(Q);
    
    for (auto &s: S) cin >> s;
    for (auto &t: T) cin >> t;
    
    for (auto &[h1, h2, off]: queries) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        off = min(abs(b - d), M - abs(b - d));
        h1 = min(a, c);
        h2 = max(a, c);
        
        high[h2][off], low[h1][off];
    }
    
    vector<i64> pref_T(N);
    for (int i = 1; i < N; i++) {
        pref_T[i] = pref_T[i - 1] + T[i - 1];
    }
    SparseTable sparse_S(S);
    
    {
        i64 acc = 0;
        LiChaoTree lines(M / 2 + 1);
        for (int h = N - 1; h >= 0; h--) {
            for (auto &[off, ans]: high[h]) {
                ans = lines.query(off);
            }
            lines.add(Line(h, S[h], -2 * acc));
            acc += T[h - 1];
        }
    }
    {
        i64 acc = 0;
        LiChaoTree lines(M / 2 + 1);
        for (int h = 0; h < N; h++) {
            for (auto &[off, ans]: low[h]) {
                ans = lines.query(off);
            }
            lines.add(Line(h, S[h], -2 * acc));
            acc += T[h];
        }
    }
    
    for (auto [h1, h2, off]: queries) {
        i64 vert = pref_T[h2] - pref_T[h1];
        i64 min_hor = sparse_S.query(h1, h2 + 1);
        
        i64 best = vert + off * min_hor;
        
        if (high[h2][off].height != -1) {
            int best_height = high[h2][off].height;
            i64 new_vert = 2 * (pref_T[best_height] - pref_T[h2]);
            i64 new_hor = S[best_height];

            best = min(best, vert + new_vert + off * new_hor);
        }
        if (low[h1][off].height != -1) {
            int best_height = low[h1][off].height;
            i64 new_vert = 2 * (pref_T[h1] - pref_T[best_height]);
            i64 new_hor = S[best_height];

            best = min(best, vert + new_vert + off * new_hor);
        }
        
        cout << best << '\n';
    }
}