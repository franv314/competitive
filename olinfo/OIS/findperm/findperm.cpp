#include <bits/stdc++.h>
using namespace std;

int query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int ans; cin >> ans;
    return ans;
}

int main() {
    int N; cin >> N;

    vector<vector<int>> by_lead(32 - __builtin_clz(N));
    for (int i = 1; i <= N; i++)
        by_lead[query(i, i)].push_back(i);
    
    vector<int> bits(32 - __builtin_ctz(N));
    vector<int> ans(N + 1);

    ans[bits[0] = by_lead[0][0]] = 1;

    for (int i = 1; i < by_lead.size(); i++) {
        for (auto x: by_lead[i]) {
            int val = 1 << i;
            for (int j = 0; j < i; j++)
                if (query(x, bits[j]) != -1)
                    val |= 1 << j;
            
            if ((ans[x] = val) == (1 << i))
                bits[i] = x;
        }
    }

    ans.erase(ans.begin());
    cout << "! ";
    for (auto x: ans)
        cout << x << " ";
    cout << "\n";
}
