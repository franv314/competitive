#include <bits/stdc++.h>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct Fenwick {
    vector<int> arr;
    
    void add(int x, int d) {
        for (; x < arr.size(); x += x & -x)
            arr[x] += d;
    }
    
    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }
    
    Fenwick(int size) : arr(size) { }  
};

void _1D(int N, int D, int M) {
    vector<int> animals(N);
    for (auto &x: animals) in >> x;
    sort(animals.begin(), animals.end());
    
    long long ans = 0;
    queue<int> in_range;
    for (auto x: animals) {
        while (!in_range.empty() && x - in_range.front() > D) {
            in_range.pop();
        }
        ans += in_range.size();
        in_range.push(x);
    }
    out << ans << '\n';
}

void _2D(int N, int D, int M) {
    vector<pair<int, int>> animals(N);
    for (auto &[x, y]: animals) {
        int i, j; in >> i >> j;
        x = i + j - 1;
        y = j - i + M;
    }
    
    sort(animals.begin(), animals.end());
    Fenwick fenwick(2 * M);
    
    long long ans = 0;
    queue<pair<int, int>> in_range;
    for (auto [x, y]: animals) {
        while (!in_range.empty() && x - in_range.front().first > D) {
            fenwick.add(in_range.front().second, -1);
            in_range.pop();
        }
        ans += fenwick.query(min(2 * M - 1, y + D)) - fenwick.query(max(0, y - D - 1));
        in_range.push({x, y});
        fenwick.add(y, 1);
    }
    out << ans << '\n';
}

void _3D(int N, int D, int M) {
    vector<tuple<int, int, int>> animals(N);
    vector prefix_sums(M + 1, vector(2 * M, vector(2 * M, 0)));
    for (auto &[x, y, z]: animals) {
        int i, j, k; in >> i >> j >> k;
        x = i + j - 1;
        y = j - i + M;
        z = k;
        
        prefix_sums[z][x][y]++;
    }
    
    for (int k = 1; k <= M; k++) {
        for (int i = 1; i < 2 * M; i++) {
            for (int j = 1; j < 2 * M; j++) {
                prefix_sums[k][i][j] += prefix_sums[k][i - 1][j] + prefix_sums[k][i][j - 1] - prefix_sums[k][i - 1][j - 1];
            }
        }
    }
    
    long long ans = 0;
    for (auto [x, y, z]: animals) {
        for (int curr_z = max(1, z - D); curr_z <= min(M, z + D); curr_z++) {
            int off = abs(z - curr_z);
            ans += prefix_sums[curr_z][min(2 * M - 1, x + D - off)][min(2 * M - 1, y + D - off)]
                 - prefix_sums[curr_z][min(2 * M - 1, x + D - off)][max(0, y - D + off - 1)]
                 - prefix_sums[curr_z][max(0, x - D + off - 1)][min(2 * M - 1, y + D - off)]
                 + prefix_sums[curr_z][max(0, x - D + off - 1)][max(0, y - D + off - 1)];
        } 
    }
    out << (ans - N) / 2 << endl;
}

int main() {
    int B, N, D, M; in >> B >> N >> D >> M;
    
    if (B == 1) _1D(N, min(D, B * M), M);
    if (B == 2) _2D(N, min(D, B * M), M);
    if (B == 3) _3D(N, min(D, B * M), M);
}