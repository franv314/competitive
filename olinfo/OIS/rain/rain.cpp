#include <bits/stdc++.h>
using namespace std;

class SegTree {
    vector<int> arr;
    int s;

    void update(int p, int d) {
        p += s;
        arr[p] += d;

        for (p >>= 1; p; p >>= 1)
            arr[p] += d;
    }

    int query(int l, int r) {
        int ans = 0;
        for (l += s, r += s; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += arr[l++];
            if (r & 1) ans += arr[--r];
        }
        return ans;
    }

public:

    void add(int l, int r, int d) {
        update(l, +d);
        update(r, -d);
    }

    int query(int x) {
        return query(0, x + 1);
    }

    SegTree(int N) {
        s = 1 << (int)ceil(log2(N + 1));
        arr.resize(2 * s);
    }
};

struct Event {
    int time, l, r;
    bool type;

    bool operator<(const Event &o) const {
        return tie(time, type, l, r) < tie(o.time, o.type, o.l, o.r);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    vector<Event> events;

    int N, K, M; cin >> N >> K >> M;
    for (int i = 0; i < M; i++) {
        int l, r, s, e; cin >> l >> r >> s >> e;
        events.push_back({s, l, r + 1, true});
        events.push_back({e + 1, l, r + 1, false});
    }

    sort(events.begin(), events.begin());
    
    SegTree segtree(N);

    map<int, array<long long, 2>> lines;
    if (K != 0) {
        lines[0] = {K, -1};
    }
    if (K != N - 1) {
        lines[K] = {0, +1};
    }

    for (auto [time, l, r, type]: events) {
        if (type) {
            segtree.add(l, r, 1);
            auto it1 = lines.lower_bound(l);
            auto it2 = lines.lower_bound(r);
            
        } else {

        }
    }
}