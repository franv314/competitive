#include <bits/stdc++.h>
using namespace std;

int N, M;

vector<int> sort_cyclic_shifts(string s) {
    vector<int> C(M), P(M);
    vector<int> cnt(max(M, 26));
    for (int i = 0; i < M; i++) cnt[s[i] - 'a']++;
    for (int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < M; i++) P[--cnt[s[i] - 'a']] = i;
    int classes = 0;
    for (int i = 1; i < M; i++) {
        if (s[P[i]] != s[P[i - 1]]) classes++;
        C[P[i]] = classes;
    }
    for (int size = 1; size < M; size *= 2) {
        vector<int> PN(M), CN(M);
        for (int i = 0; i < M; i++) {
            PN[i] = P[i] - size;
            if (PN[i] < 0) PN[i] += M;
        }
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < M; i++) cnt[C[PN[i]]]++;
        for (int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = M - 1; i >= 0; i--) P[--cnt[C[PN[i]]]] = PN[i];
        classes = 0;
        CN[P[0]] = 0;
        for (int i = 1; i < M; i++) {
            pair<int, int> curr = {C[P[i]], C[(P[i] + size) % M]};
            pair<int, int> prev = {C[P[i - 1]], C[(P[i - 1] + size) % M]};
            if (curr != prev) classes++;
            CN[P[i]] = classes;
        }
        C = CN;
    }
    return P;
}

string r(string s) {
    int a = sort_cyclic_shifts(s)[0];
    return s.substr(a) + s.substr(0, a);
}

int main(){
    cin >> N >> M;

    map<string, int> repr;
    while(N--){
        string S; cin >> S;
        repr[r(S)]++;
    }

    long long tot = 0;
    for (auto [_, am]: repr) tot += am * (am - 1) / 2;
    cout << tot << endl;
}