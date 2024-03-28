#include <bits/stdc++.h>
using namespace std;

struct Info {
    int cnt_yes, last_yes;
    int cnt_no, last_no;

    int size, fst;

    Info(int cnt_yes, int last_yes, int cnt_no, int last_no, int size, int fst) :
        cnt_yes(cnt_yes), last_yes(last_yes), cnt_no(cnt_no), last_no(last_no), size(size), fst(fst) { }
    Info(int val) :
        Info(1, val, 0, 1e9, 1, val) { }
};

Info merge(Info a, Info b) {
    int size = a.size + b.size;
    int fst = a.fst;

    int cnt_yes, last_yes;
    int cnt_no, last_no;

    if (a.last_yes < b.fst) {
        cnt_yes = a.cnt_yes + b.cnt_no;
        last_yes = b.last_no;
    } else {
        cnt_yes = a.cnt_yes + b.cnt_yes;
        last_yes = b.last_yes;
    }

    if (a.last_no < b.fst) {
        cnt_no = a.cnt_no + b.cnt_no;
        last_no = b.last_no;
    } else {
        cnt_no = a.cnt_no + b.cnt_yes;
        last_no = b.last_yes;
    }

    return {cnt_yes, last_yes, cnt_no, last_no, size, fst};
}

struct Treap {
    Info val, acc;
    int pri;
    Treap *lc, *rc;

    void update() {
        if (lc) acc = merge(lc->acc, val);
        else acc = val;

        if (rc) acc = merge(acc, rc->acc);
    }

    Treap(int val) : val(val), acc(val), lc(NULL), rc(NULL) { pri = rand(); }
};

void split(Treap *treap, Treap *&left, Treap *&right, int k) {
    if (treap == NULL) return void(left = right = NULL);

    int size_l = treap->lc ? treap->lc->acc.size : 0;

    if (size_l >= k) {
        right = treap;
        split(treap->lc, left, right->lc, k);
    } else {
        left = treap;
        split(treap->rc, left->rc, right, k - size_l - 1);
    }

    treap->update();
}

void merge(Treap *&treap, Treap *left, Treap *right) {
    if (left == NULL) return void(treap = right);
    if (right == NULL) return void(treap = left);

    if (left->pri < right->pri) {
        treap = left;
        merge(treap->rc, treap->rc, right);
    } else {
        treap = right;
        merge(treap->lc, left, treap->lc);
    }

    treap->update();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, Q; cin >> N >> Q;

    Treap *treap = NULL;
    vector<int> T(N);
    set<pair<int, int>> elements;

    for (int i = 0; i < N; i++) {
        cin >> T[i];
        merge(treap, treap, new Treap(T[i]));
        elements.emplace(T[i], i);
    }

    auto query = [&]() {
        int min_pos = elements.begin()->second;
        
        Treap *left = NULL, *right = NULL;

        split(treap, left, right, min_pos);
        merge(treap, right, left);

        int ans = treap->acc.cnt_yes;

        split(treap, right, left, N - min_pos);
        merge(treap, left, right);
    
        return N - ans;
    };

    auto update = [&](int pos, int val) {
        Treap *l = NULL, *c = NULL, *r = NULL;

        split(treap, l, c, pos);
        split(c, c, r, 1);

        *c = Treap(val);

        merge(treap, l, c);
        merge(treap, treap, r);

        elements.erase({T[pos], pos});
        elements.emplace(T[pos] = val, pos);
    };

    cout << query() << ' ';

    while (Q--) {
        int pos, val; cin >> pos >> val;
        update(pos, val);
        cout << query() << ' ';
    }

    cout << '\n';
}