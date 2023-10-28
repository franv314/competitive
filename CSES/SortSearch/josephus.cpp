#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;

    vector<array<int, 3>> elems(n);
    for (int i = 0; i < n; i++) {
        elems[i] = {i + 1, (i + 1) % n, (i - 1 + n) % n};
    }

    int curr = 1 % n;
    for (int i = 0; i < n; i++) {
        cout << elems[curr][0] << ' ';
        
        elems[elems[curr][2]][1] = elems[curr][1];
        elems[elems[curr][1]][2] = elems[curr][2];

        int next = elems[elems[curr][1]][1];

        curr = next;
    }
}