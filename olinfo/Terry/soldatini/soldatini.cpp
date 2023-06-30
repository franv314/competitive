#include <bits/stdc++.h>

using namespace std;

void solve(int t) {
    int N;
    cin >> N;
    string S;
    cin >> S;

    vector<int> sizes;
    int curr = 0;

    for (auto c: S) {
        int t = c == '1' ? 1 : -1;
        if (curr * t < 0) {
            sizes.push_back(curr);
            curr = 0;
        }
        curr += t;
    }
    sizes.push_back(curr);

    int risposta = max(1, *max_element(sizes.begin(), sizes.end()) + 1);
    for (int i = 0; i < sizes.size(); i++) {
        if (sizes[i] < 0) continue;
        if (i == sizes.size() - 1 || i == sizes.size() - 2 || sizes[i + 1] != -1) {
            risposta = max(risposta, sizes[i] + 1);
        } else {
            risposta = max(risposta, sizes[i] + sizes[i + 2] + 1);
        }
    }

    cout << "Case #" << t << ": " << min(risposta, N) << "\n";
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
