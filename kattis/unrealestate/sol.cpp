#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    struct Node {
        int val;
        double score, ans;
        int nb, ne;
        Node *lc, *rc;

        Node(int b, int e, double score, Node *l, Node *r) :
            val(0), nb(b), ne(e), score(score), ans(0.), lc(l), rc(r) { }
    } *root;

    Node* build(int nb, int ne, double scores[]) {
        if (nb + 1 == ne) return new Node(nb, ne, scores[nb], NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2, scores);
        Node *rc = build((nb + ne) / 2, ne, scores);
        return new Node(nb, ne, lc->score + rc->score, lc, rc);
    }

    void add_range(int l, int r, int d, Node *node) {
        if (node->ne <= l || node->nb >= r) return;
        if (l <= node->nb && node->ne <= r) {
            node->val += d;
        } else {
            add_range(l, r, d, node->lc);
            add_range(l, r, d, node->rc);
        }

        node->ans = node->val ? node->score : (node->lc ? node->lc->ans : 0) + (node->rc ? node->rc->ans : 0);
    }

public:

    void add_range(int l, int r, int d) { add_range(l, r, d, root); }
    double query() { return root->ans; }

    SegTree(vector<double> scores) {
        root = build(0, scores.size(), scores.data());
    }
};

int main() {
    int n; scanf("%d", &n);
    vector<tuple<double, int, double, double>> things;
    map<double, int> compress;

    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2; scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);

        things.push_back({x1, -1, y1, y2});
        things.push_back({x2, +1, y1, y2});
        compress[y1], compress[y2];
    }

    vector<double> scores;
    int w = 0;
    compress.begin()->second = w++;
    double old = compress.begin()->first;
    for (auto it = next(compress.begin()); it != compress.end(); it = next(it)) {
        it->second = w++;
        scores.push_back(it->first - old);
        old = it->first;
    }

    SegTree segtree(scores);
    sort(things.begin(), things.end());

    double ans = 0;
    old = -2000.;
    for (auto [pos, d, y_l, y_h]: things) {
        //cout << (pos - old) << " " << segtree.query() << endl;
        ans += (pos - old) * segtree.query();
        segtree.add_range(compress[y_l], compress[y_h], -d);
        old = pos;
    }

    ans = round(ans * 100) / 100;
    printf("%.2lf\n", ans);
}