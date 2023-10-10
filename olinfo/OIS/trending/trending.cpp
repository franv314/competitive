#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, T; cin >> N >> T;
    map<string, int> freq;
    set<pair<int, string>> tags;

    list<string> s;

    for (int i = 0; i < T; i++) {
        string S; cin >> S;
        s.push_back(S);
        if (tags.count({-freq[S], S})) tags.erase({-freq[S], S});
        freq[S]++;
        tags.emplace(-freq[S], S);
    }

    cout << tags.begin()->second << '\n';

    for (int i = T; i < N; i++) {
        string S; cin >> S;
        tags.erase({-freq[s.front()], s.front()});
        freq[s.front()]--;
        tags.emplace(-freq[s.front()], s.front());
        s.pop_front();
        s.push_back(S);

        if (tags.count({-freq[S], S})) tags.erase({-freq[S], S});
        freq[S]++;
        tags.emplace(-freq[S], S);

        cout << tags.begin()->second << '\n';
    }
}