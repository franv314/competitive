#include <bits/stdc++.h>
using namespace std;

int main() {
    string S; cin >> S;
    sort(S.begin(), S.end());
    vector<string> unique;

    do {
        unique.push_back(S);
    } while (next_permutation(S.begin(), S.end()));

    cout << unique.size() << "\n";
    for (auto x: unique) cout << x << "\n";
}