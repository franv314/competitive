#include <bits/stdc++.h>

using namespace std;

void solve(int t) {
    int N, M, Q;
    cin >> N >> M >> Q;

    string asdoiunasd; cin >> asdoiunasd;

    vector<char> risposta;

    vector<string> cestini(M);
    cestini[0] = asdoiunasd;

    for (int i = 0; i < Q; i++) {
        char type;
        int a, b;
        cin >> type >> a >> b;

        if (type == 's') {
            cestini[b].push_back(cestini[a].back());
            cestini[a].pop_back();

        } else {
            if (b >= cestini[a].size()) risposta.push_back(-1);
            else risposta.push_back(cestini[a][b]); 
        }
    }


    cout << "Case #" << t << ":";
    for (auto r : risposta) {
        cout << r;
    }
    cout << endl;
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
