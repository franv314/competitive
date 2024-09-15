#include <bits/stdc++.h>
#include <bits/extc++.h>
#include "treasure.h"

using namespace std;
using namespace __gnu_pbds;

vector<int> encode(vector<pair<int, int>> P) {
    vector<pair<int, int>> X, Y;
    
    for (int i = 0; i < P.size(); i++) {
        auto [x, y] = P[i];
        X.emplace_back(x, i);
        Y.emplace_back(y, i);
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    vector<int> pos_of(P.size());
    for (int i = 0; i < P.size(); i++)
        pos_of[Y[i].second] = i;

    vector<int> match(P.size());
    for (int i = 0; i < P.size(); i++)
        match[i] = pos_of[X[i].second];

    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> free;
    for (int i = 0; i < P.size(); i++)
        free.insert(i);

    vector<int> perm(P.size());
    int acc = 0;
    for (int i = 0; i < P.size(); i++) {
        perm[i] = free.order_of_key(match[i]) + acc;
        free.erase(match[i]);
        acc += P.size() - i;
    }
    
    vector<int> ans;
    copy(perm.begin(), perm.end(), back_inserter(ans));
    transform(X.begin(), X.end(), back_inserter(ans), [](auto x) { return x.first + 10e8; });
    transform(Y.begin(), Y.end(), back_inserter(ans), [](auto y) { return y.first + 15e8; });

    return ans;
}

vector<pair<int, int>> decode(vector<int> S) {
    int N = S.size() / 3;
    vector<int> X, P;
    tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> Y;
    for (auto s: S) {
        if (s < 10e8) P.push_back(s);
        else if (s < 15e8) X.push_back(s - 10e8);
        else Y.insert(s - 15e8);
    }

    sort(P.begin(), P.end());
    sort(X.begin(), X.end());

    vector<pair<int, int>> pairs;
    int acc = 0;

    for (int i = 0; i < N; i++) {
        pairs.emplace_back(X[i], *Y.find_by_order(P[i] - acc));
        Y.erase(Y.find_by_order(P[i] - acc));
        acc += N - i;
    }

    return pairs;
}
