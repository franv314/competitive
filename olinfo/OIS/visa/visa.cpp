#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define MAXN 1000
#define INF 5e8

typedef bitset<2 * MAXN> visas_t;

gp_hash_table<visas_t, pair<int, int>, hash<visas_t>> knowns[MAXN];

int N;
int cost[MAXN];
vector<int> embassies[MAXN];
vector<pair<int, int>> flights[MAXN];

vector<int> output;

void read_input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int K, L;
        cin >> cost[i] >> K >> L;
        embassies[i].resize(K);
        flights[i].resize(L);

        for (auto &E: embassies[i]) cin >> E;
        for (auto &[C, _]: flights[i]) cin >> C;
        for (auto &[_, T]: flights[i]) cin >> T;
    }
}

int recursive(int country, visas_t visas) {
    if (country == N - 1) return 0;

    visas_t new_visas = visas;
    for (auto e: embassies[country]) new_visas.set(e);

    pair<int, int>& best = knowns[country][visas];
    best = {INF, -1};
    for (auto [c, t]: flights[country]) {
        if (new_visas[MAXN + c]) {
            pair<int, int> best_if =
                knowns[c].find(new_visas) != knowns[c].end() ?
                knowns[c][new_visas] :
                make_pair(t + recursive(c, new_visas), c);

            best = min(best, best_if);
        } else if (new_visas[c]) {
            visas_t new_new_visas = new_visas;
            new_new_visas.set(MAXN + c);

            pair<int, int> best_if =
                knowns[c].find(new_new_visas) != knowns[c].end() ?
                knowns[c][new_new_visas] :
                make_pair(cost[c] + t + recursive(c, new_new_visas), c);

            best = min(best, best_if);
        }
    }
    return best.first;
}

void build_output(int country, visas_t visas) {
    output.push_back(country);
    if (country == N - 1) return;
    if (knowns[country].find(visas) == knowns[country].end()) exit(1);

    visas_t new_visas = visas;
    for (auto e: embassies[country]) new_visas.set(e);

    new_visas.set(knowns[country][visas].second + MAXN);
    build_output(knowns[country][visas].second, new_visas);
}

void print_output() {
    cout << output.size() << "\n";
    for (auto country: output) cout << country << " ";
}

int main() {
    read_input();

    visas_t starting_visas;
    starting_visas.set(0);
    starting_visas.set(MAXN);

    recursive(0, starting_visas);
    build_output(0, starting_visas);
    print_output();
}