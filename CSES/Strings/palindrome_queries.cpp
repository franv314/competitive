#include <bits/stdc++.h>
using namespace std;

typedef uint64_t hash_t;

class SegTree {
    struct Info {
        int size;
        hash_t dir, inv;
    };
    
    vector<Info> arr;
    vector<hash_t> pows;
    int s;
    
    Info merge(Info a, Info b) {
        return {a.size + b.size, a.dir * pows[b.size] + b.dir, b.inv * pows[a.size] + a.inv};
    }

public:

    void update(int p, char x) {
        arr[p += s] = {1, (hash_t)x - 'a', (hash_t)x - 'a'};
        for (p >>= 1; p; p >>= 1)
            arr[p] = merge(arr[2 * p], arr[2 * p + 1]);
    }

    Info query(int l, int r) {
        Info ans_l = {0, 0, 0}, ans_r = {0, 0, 0};
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans_l = merge(ans_l, arr[l++]);
            if (r & 1) ans_r = merge(arr[--r], ans_r);
        }

        return merge(ans_l, ans_r);
    }

    SegTree(string S, hash_t B) {
        pows.resize(S.size() + 1);
        pows[0] = 1;
        for (int i = 1; i <= S.size(); i++) pows[i] = pows[i - 1] * B;
        
        s = 1 << (int)ceil(log2(S.size()));
        arr.assign(2 * s, {1, 0, 0});

        for (int i = 0; i < S.size(); i++) arr[i + s] = {1, (hash_t)S[i] - 'a', (hash_t)S[i] - 'a'};
        for (int i = s - 1; i; i--) arr[i] = merge(arr[2 * i], arr[2 * i + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    string s; cin >> s;

    SegTree segtree(s, 29);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int k; cin >> k;
            char x; cin >> x;
            segtree.update(k - 1, x);
        } else {
            int a, b; cin >> a >> b;
            auto [len, dir, inv] = segtree.query(a - 1, b);

            cout << (dir == inv ? "YES\n" : "NO\n");
        }
    }
}