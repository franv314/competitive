#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> arr;

    void add(int p) {
        for (; p < arr.size(); p += p & -p)
            arr[p]++;
    }

    int query(int p) {
        int ans = 0;
        for (; p; p -= p & -p)
            ans += arr[p];
        return ans;
    }

    Fenwick(int size) : arr(size + 1) { }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> A(N), B(N);
    for (auto &a: A) cin >> a;
    for (auto &b: B) cin >> b;

    if (A[0] != B[0]) {
        cout << "-1\n";
        return 0;
    }

    for (int i = 0; i < N - 1; i++) {
        A[i] += A[i + 1];
        B[i] += B[i + 1];

        if (i & 1) {
            A[i] *= -1;
            B[i] *= -1;
        }
    }
    A.pop_back();
    B.pop_back();

    map<int, queue<int>> pos;
    for (int i = 0; i < N - 1; i++) pos[A[i]].push(i);

    vector<int> perm(N - 1);
    for (int i = 0; i < N - 1; i++) {
        if (pos[B[i]].empty()) {
            cout << "-1\n";
            return 0;
        }

        perm[i] = pos[B[i]].front();
        pos[B[i]].pop();
    }

    long long ans = 0;
    Fenwick fenwick(N - 1);
    for (int i = 0; i < N - 1; i++) {
        ans += i - fenwick.query(perm[i]);
        fenwick.add(perm[i] + 1);
    }

    cout << ans << '\n';
}