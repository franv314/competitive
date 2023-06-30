#include <bits/stdc++.h>
using namespace std;

const string pi("314159265358979323846264338327#");

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        string n; cin >> n;
        n.push_back('$');
        int correct = 0;
        while (n[correct] == pi[correct]) {
            correct++;
        }

        cout << correct << "\n";
    }
    return 0;
}