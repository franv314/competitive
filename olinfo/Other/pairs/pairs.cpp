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

struct Fenwick2D {
    vector<vector<int>> arr;
    
    void add(int x, int y) {
        for (int cy = y; cy < arr.size(); cy += cy & -cy)
            for (int cx = x; cx < arr.size(); cx += cx & -cx)
                arr[cx][cy]++;
    }
    
    int query(int x, int y) {
        int ans = 0;
        for (int cy = y; cy; cy -= cy & -cy)
            for (int cx = x; cx; cx -= cx & -cx)
                ans += arr[cx][cy];
        return ans;
    }
    
    Fenwick2D(int size) : arr(size, vector<int>(size)) { }  
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
    vector<Fenwick2D> fenwicks(M + 1, Fenwick2D(2 * M));
    for (auto &[x, y, z]: animals) {
        int i, j, k; in >> i >> j >> k;
        x = i + j - 1;
        y = j - i + M;
        z = k;
        
        fenwicks[z].add(x, y);
    }
    
    long long ans = 0;
    for (auto [x, y, z]: animals) {
        for (int curr_z = max(1, z - D); curr_z <= min(M, z + D); curr_z++) {
            int off = abs(z - curr_z);
            ans += fenwicks[curr_z].query(min(2 * M - 1, x + D - off), min(2 * M - 1, y + D - off))
                 - fenwicks[curr_z].query(min(2 * M - 1, x + D - off), max(0, y - D + off - 1))
                 - fenwicks[curr_z].query(max(0, x - D + off - 1), min(2 * M - 1, y + D - off))
                 + fenwicks[curr_z].query(max(0, x - D + off - 1), max(0, y - D + off - 1));
        } 
    }
    out << (ans - N) / 2 << '\n';
}

int main() {
    int B, N, D, M; in >> B >> N >> D >> M;
    
    if (B == 1) _1D(N, min(D, B * M), M);
    if (B == 2) _2D(N, min(D, B * M), M);
    if (B == 3) _3D(N, min(D, B * M), M);
}