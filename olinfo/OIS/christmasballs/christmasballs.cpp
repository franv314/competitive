#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define MAXN 100'000

// input data
int N;
vector<int> C;
vector<int> adj[MAXN];

int ma = INT_MIN;

struct EnrichedMap {
    unordered_map<int, int> freq;
    int mode_am, mode_no;

    void merge(EnrichedMap other) {
        for (auto [val, am]: other.freq) {
            freq[val] += am;
            if (freq[val] == mode_am) mode_no++;
            if (freq[val] > mode_am) {
                mode_am = freq[val];
                mode_no = 1;
            }
        }
    }

    EnrichedMap(int val) {
        freq[val] = 1;
        mode_no = 1;
        mode_am = 1;
    }
};

EnrichedMap dfs(int node) {
    EnrichedMap map_1(C[node]);
    for (auto child: adj[node]) {
        EnrichedMap map_2 = dfs(child);
        if (map_1.freq.size() < map_2.freq.size()) swap(map_1, map_2);
        map_1.merge(map_2);
    }
    ma = max(ma, map_1.mode_no);
    return map_1;
}

int main() {
    cin >> N;
    C.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    for (int i = 1; i < N; i++) {
        int temp;
        cin >> temp;
        adj[temp].push_back(i);
    }

    dfs(0);

    cout << ma << endl; // print the result
    return 0;
}