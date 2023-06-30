#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int a = s[0], b = s[1], c = s[2], d = s[3];
        map<int, int> freq;
        
        freq[a]++, freq[b]++, freq[c]++, freq[d]++;
        multiset<int> f;
        for (auto [_, q]: freq) f.insert(q);

        if (f == multiset<int>({4})) {
            cout << "-1\n";
        } else if (f == multiset<int>({1, 3})) {
            cout << "6\n";
        } else if (f == multiset<int>({2, 2})) {
            cout << "4\n";
        } else if (f == multiset<int>({1, 1, 2})) {
            cout << "4\n";
        } else if (f == multiset<int>({1, 1, 1, 1})) {
            cout << "4\n";
        } else {
            throw;
        }
    }
}