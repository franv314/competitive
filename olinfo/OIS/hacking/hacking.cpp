#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> V;

int main() {
    cin >> N;
    V.resize(N);
    for (int i=0; i<N; i++)
        cin >> V[i];

    map<int, multiset<int>> seqs;
    int tot = 0;
    for (auto n: V) {
        int seq = n;
        if (seqs[n - 2].empty()) {
            tot++;
        } else {
            seq = *seqs[n - 2].begin();
            seqs[n - 2].erase(seqs[n - 2].begin());
        }
        if (n != -seq) {
            seqs[n].insert(seq);
        }
    }
    for (auto [_, y]: seqs) {
        if (!y.empty()) {
            cout << "0\n";
            return 0;
        }
    }
    cout << tot << endl;
    return 0;
}