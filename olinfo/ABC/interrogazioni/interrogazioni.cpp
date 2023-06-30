#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'000

int arr[MAXN], temp[MAXN];

long long count_inv(int l, int r) {
    if (r - l < 2) return 0;
    
    long long total = 0;
    total += count_inv(l, (l + r) / 2);
    total += count_inv((l + r) / 2, r);

    int u = l, v = (l + r) / 2;
    for (int i = l; i < r; i++) {
        if (v == r || (u != (l + r) / 2 && arr[u] <= arr[v])) {
            temp[i] = arr[u++];
        } else {
            temp[i] = arr[v++];
            total += (l + r) / 2 - u;
        }
    }
    
    copy(temp + l, temp + r, arr + l);

    return total;
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int N; cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];

    cout << count_inv(0, N);
}