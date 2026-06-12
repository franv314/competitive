#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr int MAXZ = 1e5 + 1;

struct Line {
    i64 m, q;
    i64 operator()(i64 x) const { return m * x + q; } 

    Line(i64 m, i64 q) : m(m), q(q) { }
};

class LCT {
    vector<Line> arr;
    int s;

    vector<pair<Line*, Line>> q;

    void add(Line line, int n, int nb, int ne) {
        int m = (nb + ne) / 2;
        if (line(m) >= arr[n](m)) {
            q.emplace_back(&arr[n], arr[n]);
            swap(line, arr[n]);
        }

        if (ne - nb == 1) return;

        if (line(nb) <= arr[n](nb)) {
            add(line, 2 * n + 1, (nb + ne) / 2, ne);
        } else {
            add(line, 2 * n, nb, (nb + ne) / 2);
        }
    }

    i64 qry(i64 x, int n, int nb, int ne) {
        if (ne - nb == 1) return arr[n](x);

        if (x < (nb + ne) / 2)
            return max(arr[n](x), qry(x, 2 * n, nb, (nb + ne) / 2));
        else
            return max(arr[n](x), qry(x, 2 * n + 1, (nb + ne) / 2, ne));
    }

public:

    void rollback(int qst) {
        while (q.size() > qst) {
            auto [p, l] = q.back(); q.pop_back();
            *p = l;
        }
    }

    int qst() { return q.size(); }
    i64 qry(i64 x) { return qry(x, 1, 0, s); }

    void add(const Line &line) {
        add(line, 1, 0, s);
    }

    LCT(int size) {
        s = 1 << (int)ceil(log2(size));
        arr.resize(2 * s, Line(0, -1e18));
    }
};

class Rollback {
    vector<vector<Line>> arr;
    vector<int> query_by_time;
    vector<i64> answers;
    LCT lct;
    int s;

    void traverse(int n, int nb, int ne) {
        int q = lct.qst();
        for (auto line: arr[n]) lct.add(line);

        if (ne - nb == 1) {
            if (nb < query_by_time.size()) {
                answers[nb] = lct.qry(query_by_time[nb]);
            }
        } else {
            traverse(2 * n, nb, (nb + ne) / 2);
            traverse(2 * n + 1, (nb + ne) / 2, ne);
        }

        lct.rollback(q);
    }

public:

    void traverse() {
        traverse(1, 0, s);
    }

    i64 qry(int time) { return answers[time]; }

    void insert(int l, int r, const Line &line) {
        for (l += s, r += s; l < r; r >>= 1, l >>= 1) {
            if (l & 1) arr[l++].push_back(line);
            if (r & 1) arr[--r].push_back(line);
        }
    }

    Rollback(vector<int> qbt) : query_by_time(qbt), answers(qbt.size()), lct(MAXZ) {
        s = 1 << (int)ceil(log2(qbt.size()));
        arr.resize(2 * s);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, k; cin >> n >> k;
    vector<vector<int>> children(n);
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        children[--p[i]].push_back(i);
    }

    vector<i64> z(n), b(n), d(n);
    for (int i = 1; i < n; i++) cin >> z[i];
    for (int i = 1; i < n; i++) cin >> b[i];

    int t = 0;
    vector<int> path;
    vector<int> timer(n);
    vector<vector<int>> existence(n);
    auto dfs = [&](auto &&dfs, int node, i64 dep = 0) -> void {
        d[node] = dep;
        path.push_back(node);
        existence[node].push_back(t);
        timer[node] = t++;

        if (path.size() >= k) {
            existence[path[path.size() - k]].push_back(t);
        }
        for (auto ch: children[node]) {
            dfs(dfs, ch, dep + b[ch]);
        }
        if (path.size() >= k) {
            existence[path[path.size() - k]].push_back(t);
        }
        
        existence[node].push_back(t);
        path.pop_back();
    };

    dfs(dfs, 0);
    
    vector<int> query_by_time(n);
    for (int i = 1; i < n; i++)
        query_by_time[timer[i]] = z[i];

    Rollback rollback(query_by_time);
    for (int first = 1; first < n; first++) {
        Line line = Line(-d[p[first]], z[first] * z[first]);
        for (int i = 0; i < existence[first].size(); i += 2)
            rollback.insert(existence[first][i], existence[first][i + 1], line);
    }

    rollback.traverse();

    i64 ans = 0;
    for (int last = 1; last < n; last++) {
        ans = max(ans, z[last] * z[last] + z[last] * d[last] + rollback.qry(timer[last]));
    }

    cout << ans << '\n';
}
