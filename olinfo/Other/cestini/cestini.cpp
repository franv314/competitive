#include <vector>
using namespace std;

vector<vector<int>> cestini;

void inizia(int N, int M) {
    vector<int> zero = {};
    for (int i = 0; i < N; i++) zero.push_back(i);
    cestini.push_back(zero);
    for (int i = 1; i < M; i++) {
        vector<int> empty;
        cestini.push_back(empty);
    }
}

void sposta(int a, int b) {
    cestini[b].push_back(cestini[a].back());
    cestini[a].pop_back();
}

int controlla(int a, int i) {
    if (i >= cestini[a].size()) return -1;
    else return cestini[a][i];
}