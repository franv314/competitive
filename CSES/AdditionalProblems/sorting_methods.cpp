#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> arr;

    void add(int x) {
        for (; x < arr.size(); x += x & -x)
            arr[x]++;
    }

    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }

    Fenwick(int n) : arr(n + 1) { }
};

long long method_1(int n, const vector<int> &arr) {
    Fenwick fenwick(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += i - fenwick.query(arr[i]);
        fenwick.add(arr[i]);
    }
    return ans;
}

int method_2(int n, const vector<int> &arr) {
    int ans = n;
    vector<bool> visited(n);

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        ans--;

        for (int curr = i; !visited[curr]; curr = arr[curr] - 1) {
            visited[curr] = true;
        }
    }

    return ans;
}

int method_3(int n, const vector<int> &arr) {
    set<int> lis;
    for (auto x: arr) {
        auto [it, ok] = lis.insert(x);
        if (ok && next(it) != lis.end()) lis.erase(next(it));
    }
    return n - lis.size();
}

int method_4(int n, const vector<int> &arr) {
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[arr[i] - 1] = i;
    
    for (int i = n - 2; i >= 0; i--) {
        if (pos[i] > pos[i + 1]) return i + 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    cout << method_1(n, a) << ' ' << method_2(n, a) << ' ' << method_3(n, a) << ' ' << method_4(n, a) << '\n';
}
