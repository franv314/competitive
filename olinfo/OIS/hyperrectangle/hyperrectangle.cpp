#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> V(2 * N);
    for (int i = 0; i < 2 * N; i++)
        cin >> V[i];

    sort(V.begin(), V.end());
    for (int i = 0; i < N; i++)
        cout << V[i] << " ";
    cout << endl;
    for (int i = N; i < 2 * N; i++)
        cout << V[i] << " ";
    cout << endl;

    return 0;
}