// NOTE: it is recommended to use this even if you don't understand the following code.

#include <bits/stdc++.h>

using namespace std;

// input data
int N;
vector<int> V;
unordered_map<int, int> counts;

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> N;
    V.resize(N);
    for (int i=0; i<N; i++)
        cin >> V[i];

    int bad = 0;
    for (auto x: V) {
        if (++counts[x] == 2) bad++;
    }

    cout << (bad > 1 ? "YES" : "NO") << endl; // print the result
    return 0;
}