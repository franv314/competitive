#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int pow(int val, int exp) {
    long long ans = 1, amounts = val;
    for (; exp; exp >>= 1) {
        if (exp & 1) ans = (ans * amounts) % MOD;
        amounts = (amounts * amounts) % MOD;
    }
    return ans;
}

int acc(multimap<int, int> vals) {
    long long ans = 1;
    for (auto [_, x]: vals)
        ans = (ans * (x + 1)) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    
    map<int, int> am;
    for (int i = 0; i < N; i++) {
        int V; cin >> V;
        am[V]++;
    }
    multimap<int, int> amounts;
    for (auto [_, k]: am) {
        amounts.emplace(k, 1);
    }

    int last = max_element(amounts.begin(), amounts.end())->first;
    int total = 0;
    for (int k = 0; k < last; k++) {
        int c = pow(k + 1, MOD - 2);
        vector<multimap<int, int>::iterator> e;
        
        for (auto it = amounts.begin(); it != amounts.end(); it++) {
            auto &[n, val] = *it;

            val = ((long long)val * (n - k)) % MOD;
            val = ((long long)val * c) % MOD;

            if (val == 0)
                e.push_back(it);
        }
        for (auto x: e) amounts.erase(x);
        cout << acc(amounts) << endl;
        total = (total + acc(amounts)) % MOD;
    }
    
    cout << total - last + 1 << endl;

    return 0;
}