#include <bits/stdc++.h>
using namespace std;

void dedup(vector<int> &arr) {
    set<int> seen;
    for (int i = 0; i < arr.size(); i++) {
        if (seen.count(arr[i]))
            return arr.resize(i);

        seen.insert(arr[i]);
    }
}

int conta(int N, vector<int> &A, vector<int> &B, vector<int> &C) {
    dedup(A);
    dedup(B);
    dedup(C);

    int b = 0, c = 0;
    set<int> in_a(A.begin(), A.end());
    map<int, int> in_b, in_c;
    set<pair<int, int>> chain = {{-1, 0}};
    multiset<int> best = {0};

    auto value = [&](set<pair<int, int>>::iterator it) -> int {
        int nxt = next(it) == chain.end() ? b : next(it)->first;
        return nxt + it->second;
    };

    auto extend_c = [&]() -> bool {
        if (c == C.size() || in_a.count(C[c]))
            return false;
        
        in_c[C[c]] = c;
        
        best.erase(best.find(value(chain.begin())));
        chain.erase({-1, c});
        chain.emplace(-1, c + 1);
        best.insert(value(chain.begin()));

        if (!in_b.count(C[c])) {
            c++;
            return true;
        }

        auto pv = prev(chain.lower_bound({in_b[C[c]], c}));
        if (pv->second < c) {
            c++;
            return true;
        }

        best.erase(best.find(value(pv)));
        auto [it, _] = chain.emplace(in_b[C[c]], c);
        best.insert(value(pv));

        while (next(it) != chain.end() && next(it)->second > c) {
            best.erase(best.find(value(next(it))));
            chain.erase(next(it));
        }

        best.insert(value(it));

        c++;
        return true;
    };

    auto extend_b = [&]() -> bool {
        if (b == B.size() || in_a.count(B[b]))
            return false;
        
        in_b[B[b]] = b;

        if (!in_c.count(B[b])) {
            best.erase(best.find(value(prev(chain.end()))));
            b++;
            best.insert(value(prev(chain.end())));
            return true;
        }

        auto pv = prev(chain.end());
        if (pv->second < in_c[B[b]]) {
            best.erase(best.find(value(prev(chain.end()))));
            b++;
            best.insert(value(prev(chain.end())));
            return true;
        }

        best.erase(best.find(value(pv)));
        auto [it, _] = chain.emplace(b, in_c[B[b]]);
        best.insert(value(pv));

        best.insert(value(it));

        best.erase(best.find(value(prev(chain.end()))));
        b++;
        best.insert(value(prev(chain.end())));
        return true;
    };

    int ans = 0;

    for (int a = A.size(); a >= 0; a--) {
        while (extend_c()) ;
        while (extend_b()) ;

        ans = max(ans, a + *best.rbegin());
    
        if (a != 0)
            in_a.erase(A[a - 1]);
    }

    return ans;
}
