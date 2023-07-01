#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define MAXK 100
#define MAXN 5000
#define COUNTRY_SCORE 1000000000

long long players[MAXK];
int strength[MAXN];
mt19937 rd;

struct Compare {
    bool operator()(int a, int b) const {
        if (players[a] != players[b]) {
            return players[a] < players[b];
        }
        return a < b;
    }
};

struct Compare2 {
    bool operator()(int a, int b) const {
        if (strength[a] != strength[b]) {
            return strength[a] < strength[b];
        }
        return a < b;
    }
};

using ord_set = tree<int, null_type, Compare2, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    int start = clock();

    ios::sync_with_stdio(false); cin.tie(NULL);
    
    int N, K; cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> strength[i];

    vector<vector<int>> adj(N);
    for (auto &a: adj) {
        int L; cin >> L;
        a.resize(L);
        for (auto &x: a) {
            cin >> x;
        }
    }

    vector<ord_set> countries_of(K);
    vector<int> countries(N, -1);
    for (int n = 0; n < N; n++) {
        set<int, Compare> available_players;
        for (int i = 0; i < K; i++) {
            available_players.insert(i);
        }
        for (auto x: adj[n]) {
            if (countries[x] >= 0) {
                available_players.erase(countries[x]);
            }
        }
        countries[n] = *available_players.begin();
        countries_of[*available_players.begin()].insert(n);
        players[*available_players.begin()] += COUNTRY_SCORE + strength[n];
    }

    set<pair<int, int>> players_by_countries;
    
    for (int i = 0; i < K; i++) {
        players_by_countries.insert({countries_of[i].size(), i});
    }

    for (;;) {
        auto [cs, strongest] = *players_by_countries.rbegin();
        auto [cw, weakest] = *players_by_countries.begin();

        if (cs == cw + (N % K != 0)) break;
      
        int rd_from_strong = rd() % countries_of[strongest].size();
       
        rd_from_strong = *countries_of[strongest].find_by_order(rd_from_strong);

        bool can = true;
        for (auto x: adj[rd_from_strong]) {
            if (countries[x] == weakest) {
                can = false;
                break;
            }
        }
        if (!can) continue;

        players[strongest] -= COUNTRY_SCORE + strength[rd_from_strong];
        players[weakest] += COUNTRY_SCORE + strength[rd_from_strong];
                
        pair<int, int> s = *players_by_countries.rbegin(); players_by_countries.erase(prev(players_by_countries.end()));
        pair<int, int> w = *players_by_countries.begin(); players_by_countries.erase(players_by_countries.begin());

        s.first--;
        w.first++;
        players_by_countries.insert(s);
        players_by_countries.insert(w);

        countries_of[strongest].erase(rd_from_strong);
        countries_of[weakest].insert(rd_from_strong);

        countries[rd_from_strong] = weakest;
    }

    set<pair<long long, int>> players_by_score;
    for (int i = 0; i < K; i++) {
        players_by_score.insert({players[i], i});
    }

    while (clock() - start < .5 * CLOCKS_PER_SEC) {
        int player_of_1 = players_by_score.rbegin()->second;
        int player_of_2 = players_by_score.begin()->second;

        int rd1 = *countries_of[player_of_1].find_by_order(rd() % countries_of[player_of_1].size());
        int rd2 = *countries_of[player_of_2].find_by_order(rd() % countries_of[player_of_2].size());

        if (strength[rd1] <= strength[rd2]) continue;
        
        bool can = true;
        for (auto x: adj[rd1]) {
            if (countries[x] == player_of_2) {
                can = false;
                break;
            }
        }
        if (!can) continue;
        for (auto x: adj[rd2]) {
            if (countries[x] == player_of_1) {
                can = false;
                break;
            }
        }
        if (!can) continue;

        players[player_of_1] += strength[rd2] - strength[rd1];
        players[player_of_2] += strength[rd1] - strength[rd2];

        pair<long long, int> s = *players_by_score.rbegin(); players_by_score.erase(prev(players_by_score.end()));
        pair<long long, int> w = *players_by_score.begin(); players_by_score.erase(players_by_score.begin());

        s.first = players[player_of_1];
        w.first = players[player_of_2];

        players_by_score.insert(s);
        players_by_score.insert(w);

        countries_of[player_of_1].erase(rd1);
        countries_of[player_of_2].erase(rd2);
        countries_of[player_of_1].insert(rd2);
        countries_of[player_of_2].insert(rd1);
        
        swap(countries[rd1], countries[rd2]);
    }

    for (auto country: countries) {
        cout << country << ' ';
    }
}

