#include <bits/stdc++.h>
using namespace std;

#define MAXK 100
#define MAXN 5'000

const int country_score = 1e9;

int N, K, S[MAXN];
vector<int> adj[MAXN];

int assigned_to[MAXN];
long long scores[MAXK];

void generate() {
    fill(assigned_to, assigned_to + N, -1);
    for (int i = 0; i < N; i++) {
        set<int> valid;
        for (int j = 0; j < K; j++) valid.insert(j);

        for (auto neighbour: adj[i]) {
            valid.erase(assigned_to[neighbour]);
        }

        auto it = valid.begin();
        int pos = rand() % valid.size();
        while (pos--) it = next(it);
        int player = *it;
        assigned_to[i] = player;
        scores[player] += country_score + S[i];
    }
}

bool valid(int a, int b) {
    for (auto neighbour: adj[a])
        if (assigned_to[neighbour] == assigned_to[a])
            return false;
    for (auto neighbour: adj[b])
        if (assigned_to[neighbour] == assigned_to[b])
            return false;
    return true;
}

void do_swaps() {
    for (int _ = 0; _ < 1'000'000; _++) {
        int a = rand() % N, b = rand() % N;
        
        int a_countries = scores[assigned_to[a]] / country_score;
        int b_countries = scores[assigned_to[b]] / country_score;

        if (a_countries < b_countries) swap(a_countries, b_countries);

        if (a_countries > N / K && b_countries < N / K) {
            swap(assigned_to[a], assigned_to[b]);
            if (!valid(a, b)) swap(assigned_to[a], assigned_to[b]);
        }
    }
}

int main() {
    srand(clock());
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> S[i];
    for (int i = 0; i < N; i++) {
        int L; cin >> L;
        for (int j = 0; j < L; j++) {
            int A; cin >> A;
            adj[i].push_back(A);
        }
    }

    generate();
    do_swaps();
    for (int i = 0; i < N; i++) cout << assigned_to[i] << " ";
}