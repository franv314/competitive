#include <bits/stdc++.h>
using namespace std;

int N;
string s;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    cin >> N;
    cin >> s;

    vector<int> to_check(N);
    iota(to_check.begin(), to_check.end(), 0);

    for (int j = 0; to_check.size() > 1; j++) {
        char curr_max = '\0';
        vector<int> max_idxs = {};

        for (auto i: to_check) {
            if (s[i + j] == curr_max) max_idxs.push_back(i);
            else if (s[i + j] > curr_max) {
                curr_max = s[i + j];
                max_idxs = {i};
            }
        }
        to_check = max_idxs;
    }
    cout << to_check[0] << endl;
    return 0;
}