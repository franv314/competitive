#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int N, D; cin >> N >> D;
    vector<pair<int, int>> gauls(N);

    long long tot = 0;

    for (auto &[h, l]: gauls) {
        cin >> h >> l;
        tot += h;
    }

    sort(gauls.begin(), gauls.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first + a.second < b.first + b.second;
    });

    priority_queue<int> escaped;

    for (auto [h, l]: gauls) {
        if (tot + l >= D) {
            escaped.push(h);
            tot -= h;
        } else if (!escaped.empty() && escaped.top() > h) {
            tot += escaped.top();
            escaped.pop();

            escaped.push(h);
            tot -= h;
        }
    }

    cout << escaped.size() << "\n";
}