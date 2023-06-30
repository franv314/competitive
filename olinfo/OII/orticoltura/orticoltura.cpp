#include <bits/stdc++.h>
using namespace std;

void posiziona(int D, int T);
void budget(int B);

deque<pair<int, int>> irrigatori;

struct Compare1 {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.first - a.second < b.first - b.second || a.first < b.first;
    }
};

struct Compare2 {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.first + a.second < b.first + b.second || a.first < b.first;
    }
};

void irriga(int C, int N, vector<int>& X, vector<int>& P) {
    irrigatori.resize(N);
    for (int i = 0; i < N; i++)
        irrigatori[i] = {X[i], P[i]};


    set<pair<int, int>, Compare1> starts(irrigatori.begin(), irrigatori.end());
    set<pair<int, int>, Compare2>   ends(irrigatori.begin(), irrigatori.end());

    int total_cost = 0;
    while (!starts.empty()) {
        auto [x, p] = *starts.begin();
        starts.erase(starts.begin());
        ends.erase({x, p});

        int left = x - p;
        int curr = x + p;
        int cost = p;
        
        while (!ends.empty()) {
            auto [xn, pn] = *ends.begin();
            int next = xn + pn;
            
            int new_cost = (next - left + 1) / 2;
            if (new_cost - cost > C + pn) break;

            starts.erase({xn, pn});
            ends.erase(ends.begin());
            curr = next;
            cost = new_cost; 
        }
        total_cost += cost + C;
        posiziona((left + curr + 1) / 2, cost);
    }
    budget(total_cost);
}