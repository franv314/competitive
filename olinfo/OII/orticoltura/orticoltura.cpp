#include <bits/stdc++.h>
using namespace std;

void posiziona(int D, int T);
void budget(int B);

void irriga(int C, int N, vector<int>& X, vector<int>& P) {
    vector<int> seeds1(N);
    iota(seeds1.begin(), seeds1.end(), 0);
    sort(seeds1.begin(), seeds1.end(), [&](int a, int b) { return tie(X[a], P[a]) < tie(X[b], P[b]); });
    vector<int> seeds;
    
    for (auto seed: seeds1) {
        if (seeds.empty()) {
            seeds.push_back(seed);
            continue;
        }
        int t = seeds.back();
        if (P[seed] < P[t] && abs(X[seed] - X[t]) <= P[t] - P[seed]) {
            continue;
        }

        while (!seeds.empty()) {
            int t = seeds.back();
            if (!(P[t] < P[seed] && abs(X[t] - X[seed]) <= P[seed] - P[t])) {
                break;
            } else {
                seeds.pop_back();
            }
        }
        seeds.push_back(seed);
    }

    sort(seeds.begin(), seeds.end(), [&](int a, int b) { return X[a] + P[a] < X[b] + P[b]; });

    vector<pair<int, long long>> cost(seeds.size() + 1);
    cost[seeds.size()] = {-1, 0};
    pair<long long, int> best = {LLONG_MAX, -1};

    for (int i = seeds.size() - 1; i >= 0; i--) {
        best = min(best, {(X[seeds[i]] + P[seeds[i]]) / 2 + cost[i + 1].second, i});

        int h = ((X[seeds[best.second]] + P[seeds[best.second]]) - (X[seeds[i]] - P[seeds[i]])) / 2;
        long long this_cost = cost[best.second + 1].second + C + h;
        cost[i] = {best.second, this_cost};
    }

    for (int i = 0; i != seeds.size(); i = cost[i].first + 1) {
        int next = cost[i].first;
        int h = ((X[seeds[next]] + P[seeds[next]]) - (X[seeds[i]] - P[seeds[i]])) / 2;
        int d = ((X[seeds[next]] + P[seeds[next]]) + (X[seeds[i]] - P[seeds[i]])) / 2;
        posiziona(d, h);
    }

    budget(cost[0].second);
}
