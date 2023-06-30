#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define MAXN 1'000'000
#define MAXS 10'000
#define MAXL 14

typedef unsigned long long hash_t;

#define b 131
#define extend(hash, c) ((hash) * (b) + (c))
#define pop(hash, length, c) ((hash) - (c) * pot[(length) - 1])

gp_hash_table<hash_t, null_type> found;
//unordered_set<hash_t> found;
hash_t pref_hash[MAXN + 1];
int max_match[MAXN];

vector<hash_t> pot(MAXS);

int main() {
    pot[0] = 1;
    for (int i = 1; i < MAXS; i++)
        pot[i] = pot[i - 1] * b;
    
    //found.reserve(16384);
    //found.max_load_factor(0.25);
    
    ios::sync_with_stdio(false); cin.tie(NULL);
    string N, S;
    getline(cin, N);
    getline(cin, S);
    
    for (int i = 1; i <= N.size(); i++) {
        pref_hash[i] = extend(pref_hash[i - 1], N[i - 1]);
    }
    
    vector<tuple<int, int, vector<int>>> ranges;
    
    ranges.push_back({0, S.size() + 1, {}});
    for (int i = 0; i < N.size(); i++) {
        get<2>(ranges[0]).push_back(i);
    }
    
    while (!ranges.empty()) {
        auto [l, r, pos] = ranges.back();
        ranges.pop_back();
        
        if (l + 1 == r) {
            for (auto p: pos) {
                max_match[p] = l;
            }
            continue;
        }
        
        int m = (l + r) / 2;
        
        found.clear();
          
        hash_t hs = 0;
        for (int k = 0; k < S.size(); k++) {
            if (k >= m) hs = pop(hs, m, S[k - m]);
            hs = extend(hs, S[k]);
            if (k >= m - 1) {
                found.insert(hs);
            }
        }
        
        vector<int> L, R;
        
        for (auto p: pos) {
            if (p + m > N.size()) {
                L.push_back(p);
                continue;
            }
            
            hash_t test_hashes = pop(pref_hash[p + m], m + 1, pref_hash[p]);
            
            if (found.find(test_hashes) != found.end()) R.push_back(p);
            else L.push_back(p);
        }
        
        ranges.push_back({l, m, L});
        ranges.push_back({m, r, R});
    }
    
    int curr = 0;
    int jumps = 0;
    while (curr < N.size()) {
        curr += max_match[curr];
        jumps++;
    }
    cout << jumps << '\n';
}