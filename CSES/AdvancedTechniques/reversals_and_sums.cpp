#include <bits/stdc++.h>
using namespace std;

struct Treap;
int size(Treap*);
long long sum(Treap*);

struct Treap {
    int val, pri, size;
    bool reverse;
    long long sum;

    Treap *L, *R;

    void update() {
        if (reverse) {
            reverse = false;
            swap(L, R);
            if (L != NULL) L->reverse ^= true;
            if (R != NULL) R->reverse ^= true;
        }
    }

    Treap(int val) : Treap(val, rand(), NULL, NULL) { }

    Treap(int val, int pri, Treap *L, Treap *R) : val(val), pri(pri), L(L), R(R) {
        size = 1 + ::size(L) + ::size(R);
        sum = val + ::sum(L) + ::sum(R);
    }
};

int size(Treap *treap) { return treap ? treap->size : 0; }
long long sum(Treap *treap) { return treap ? treap->sum : 0; }

pair<Treap*, Treap*> split(Treap *treap, int k) {
    if (treap == NULL) return {NULL, NULL};

    treap->update();
    
    if (size(treap->L) >= k) {
        auto [LL, LR] = split(treap->L, k);
        
        Treap *NR = new Treap(treap->val, treap->pri, LR, treap->R);
        delete treap;
        return {LL, NR};
    } else {
        auto [RL, RR] = split(treap->R, k - size(treap->L) - 1);

        Treap *NL = new Treap(treap->val, treap->pri, treap->L, RL);
        delete treap;
        return {NL, RR};
    }
}

Treap* merge(Treap *L, Treap *R) {
    if (L == NULL) return R;
    if (R == NULL) return L;
    
    L->update();
    R->update();

    if (L->pri >= R->pri) {
        Treap *NR = merge(L->R, R);
        Treap *N = new Treap(L->val, L->pri, L->L, NR);
        delete L;
        return N;
    } else {
        Treap *NL = merge(L, R->L);
        Treap *N = new Treap(R->val, R->pri, NL, R->R);
        delete R;
        return N;
    }
}

Treap* reverse(Treap *treap, int l, int r) {
    auto [L, T] = split(treap, l);
    auto [M, R] = split(T, r - l);

    M->reverse ^= true;

    treap = merge(L, M);
    treap = merge(treap, R);
    return treap;
}

pair<Treap* ,long long> sum(Treap *treap, int l, int r) {
    auto [L, T] = split(treap, l);
    auto [M, R] = split(T, r - l);

    long long ans = sum(M);

    treap = merge(L, M);
    treap = merge(treap, R);

    return {treap, ans};
}

int main() {
    int n, m; cin >> n >> m;

    Treap *treap = NULL;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        treap = merge(treap, new Treap(x));
    }
    
    for (int i = 0; i < m; i++) {
        int t, a, b; cin >> t >> a >> b;
        a--;
        if (t == 1) {
            treap = reverse(treap, a, b);
        } else {
            auto [t, ans] = sum(treap, a, b);
            cout << ans << "\n";
            treap = t;
        }
    }
}