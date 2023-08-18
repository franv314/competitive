#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, X; cin >> N >> X;

    vector<int> L(N);
    for (int i = 0; i < N; i++) {
        cin >> L[i];
    }

    sort(L.begin(), L.end());
    int days = 0;
    for (int i = 0; i < L.size();) {
        if (i != L.size() - 1 && L[i] + L[i + 1] <= X) {
            i += 2;
        } else {
            i++;
        }
        days++;
    }

    cout << days << endl; // print the result
    return 0;
}