#include <bits/stdc++.h>
using namespace std;
 
struct Treap;
int size(Treap*);
 
struct Treap {
    char val;
    int pri, size;
    bool reverse;
 
    Treap *L, *R;
 
    void update() {
        if (reverse) {
            reverse = false;
            swap(L, R);
            if (L != NULL) L->reverse ^= true;
            if (R != NULL) R->reverse ^= true;
        }
    }
};

Treap t[20'000'000];
vector<Treap*> arr;

void init() {
    arr.resize(20'000'000);
    iota(arr.begin(), arr.end(), t);
}

Treap* get(char val, int pri, Treap *L, Treap *R) {
    Treap* top = arr.back(); arr.pop_back();
    top->val = val, top->pri = pri, top->L = L, top->R = R;
    top->size = 1 + ::size(L) + ::size(R);
    return top;
}

Treap* get(char val) {
    return get(val, rand(), NULL, NULL);
}

void ret(Treap* treap) {
    arr.push_back(treap);
}

int size(Treap *treap) { return treap ? treap->size : 0; }
 
pair<Treap*, Treap*> split(Treap *treap, int k) {
    if (treap == NULL) return {NULL, NULL};
 
    treap->update();
    
    if (size(treap->L) >= k) {
        auto [LL, LR] = split(treap->L, k);
        
        Treap *NR = get(treap->val, treap->pri, LR, treap->R);
        ret(treap);
        return {LL, NR};
    } else {
        auto [RL, RR] = split(treap->R, k - size(treap->L) - 1);
 
        Treap *NL = get(treap->val, treap->pri, treap->L, RL);
        ret(treap);
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
        Treap *N = get(L->val, L->pri, L->L, NR);
        ret(L);
        return N;
    } else {
        Treap *NL = merge(L, R->L);
        Treap *N = get(R->val, R->pri, NL, R->R);
        ret(R);
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
 
ostream& operator<<(ostream &os, Treap *treap) {
    if (treap == NULL) return os;
    treap->update();
    cout << treap->L << treap->val << treap->R;
    return os;
}
 
int main() {
    init();
    int n, m; cin >> n >> m;
 
    Treap *treap = NULL;
    string s; cin >> s;
    for (auto x: s) {
        treap = merge(treap, get(x));
    }
    
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--;
        treap = reverse(treap, a, b);
    }
 
    cout << treap;
}