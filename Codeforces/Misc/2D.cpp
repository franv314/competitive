#include <bits/stdc++.h>
using namespace std;

struct SegmentInfo {
    long long sum, max_pref, max_suff, max_sub;
    
    SegmentInfo() { }
    
    SegmentInfo(int val) {
        sum = val;
        max_pref = max_suff = max_sub = max(0, val);
    }
    
    SegmentInfo(SegmentInfo l, SegmentInfo r) {
        sum = l.sum + r.sum;
        max_pref = max(l.max_pref, l.sum + r.max_pref);
        max_suff = max(r.max_suff, r.sum + l.max_suff);
        max_sub = max({l.max_sub, l.max_suff + r.max_pref, r.max_sub});
    }
};

vector<SegmentInfo> build(int l, int r) {
    if (l + 1 == r) {
        int x; cin >> x;
        return {SegmentInfo(x)};
    }
    int size = r - l;
    vector<SegmentInfo> L = build(l, (l + r) / 2);
    vector<SegmentInfo> R = build((l + r) / 2, r);
    
    vector<SegmentInfo> ans(size);
    
    for (int i = 0; i < size / 2; i++) {
        ans[i] = SegmentInfo(L[i], R[i]);
    }
    for (int i = size / 2; i < size; i++) {
        ans[i] = SegmentInfo(R[i - size / 2], L[i - size / 2]);
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    vector<SegmentInfo> root = build(0, 1 << n);
    int q; cin >> q;
    
    int curr_state = 0;
    while (q--) {
        int k; cin >> k;
        curr_state ^= (1 << k);
        cout << root[curr_state].max_sub << '\n';
    } 
}