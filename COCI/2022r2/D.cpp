#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

class SegTree {
    struct Node {
        bool val;
        int nb, ne;
        Node *lc, *rc;
    } *nodes, *root;
    int node;

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) {
            nodes[node] = {false, nb, ne, NULL, NULL};
            return &nodes[node++];
        }
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        nodes[node] = {lc->val || rc->val, nb, ne, lc, rc};
        return &nodes[node++];
    }

    void set(int x, bool v, Node* node) {
        if (node->nb > x || node->ne <= x) return;
        if (node->nb + 1 == node->ne) {
            node->val = v;
            return;
        }

        set(x, v, node->lc);
        set(x, v, node->rc);
        node->val = node->lc->val || node->rc->val;
    }

    bool query(int l, int r, Node* node) {
        if (node->nb >= r || node->ne <= l) return false;
        if (l <= node->nb && node->ne <= r) return node->val;
        return query(l, r, node->lc) || query(l, r, node->rc);
    }

public:

    void set(int x, bool v) {
        set(x, v, root);
    }

    bool query(int l, int r) {
        return query(l, r, root);
    }

    SegTree (int n) {
        node = 0;
        nodes = (Node*)malloc(300'000 * sizeof(Node));
        root = build(0, n);
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<string> leona(n), zoe(m);
    vector<tuple<string, bool, int>> words(n + m);
    for (int i = 0; i < n; i++) {
        cin >> leona[i];
        words[i] = {leona[i], false, i};
    }
    for (int i = 0; i < m; i++) {
        cin >> zoe[i];
        words[i + n] = {zoe[i], true, i};
    }
    
    vector<int> first_l(n), first_z(m);
    vector<int> fwith_l(28, n), fwith_z(26, m);

    char looking_for = 'a';
    for (int i = 0; i < n; i++) {
        if (leona[i][0] >= looking_for) {
            for (char c = looking_for; c <= leona[i][0]; c++) {
                fwith_l[c - 'a'] = i;
            }
            looking_for = leona[i][0] + 1;
        }
    }
    looking_for = 'a';
    for (int i = 0; i < m; i++) {
        if (zoe[i][0] >= looking_for) {
            for (char c = looking_for; c <= zoe[i][0]; c++) {
                fwith_z[c - 'a'] = i;
            }
            looking_for = zoe[i][0] + 1;
        }
    }

    int idx_l = 0, idx_z = 0;
    int l = 0, z = 0;
    while (idx_l < n || idx_z < m) {
        if (idx_l != n && (idx_z == m || leona[idx_l] <= zoe[idx_z])) {
            words[idx_l + idx_z] = {leona[idx_l], false, idx_l};

            for (; z < idx_z; z++) first_z[z] = idx_l;
            idx_l++;
        } else {
            words[idx_l + idx_z] = {zoe[idx_z], true, idx_z};

            for (; l < idx_l; l++) first_l[l] = idx_z;
            idx_z++;
        }
    }
    for (; z < m; z++) first_z[z] = n;
    for (; l < n; l++) first_l[l] = m;

    reverse(words.begin(), words.end());

    SegTree win_l(n), win_z(m);
    
    for (auto [word, player, pos]: words) {
        if (!player) {
            bool val = !win_z.query(first_l[pos], fwith_z[word[0] + 2 - 'a']);
            win_l.set(pos, val);
        } else {
            bool val = !win_l.query(first_z[pos], fwith_l[word[0] + 2 - 'a']);
            win_z.set(pos, val);
        }
    }

    cout << (win_l.query(0, 1) ? "Leona\n" : "Zoe\n");
    return 0;
}