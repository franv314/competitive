#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Line {
    i64 m, q;

    i64 first_leq(const Line &o) const {
        i64 num = o.q - q;
        i64 den = m - o.m;

        return (num + den - 1) / den;
    }

    i64 operator()(i64 x) const { return m * x + q; }
};

int main() {
    int n, x; cin >> n >> x;
    vector<int> s(n), f(n);
    for (auto &x: s) cin >> x;
    for (auto &x: f) cin >> x;

    vector<pair<Line, int>> ch;
    ch.push_back({{x, 0}, 0});

    for (int i = 0; i < n - 1; i++) {
        if (i != 0 && f[i - 1] == f[i])
            continue;
        if (i == 0 && f[i] == x)
            continue;

        Line best = prev(upper_bound(ch.begin(), ch.end(), make_pair(Line{0, 0}, s[i]), [](const auto &a, const auto &b) {
            return a.second < b.second;
        }))->first;
        
        i64 t = best(s[i]);
        Line new_line = {f[i], t};

        while (new_line.first_leq(ch.back().first) < ch.back().second)
            ch.pop_back();
        
        i64 p = new_line.first_leq(ch.back().first);
        ch.push_back({new_line, p});
    }

    Line best = prev(upper_bound(ch.begin(), ch.end(), make_pair(Line{0, 0}, s.back()), [](const auto &a, const auto &b) {
        return a.second < b.second;
    }))->first;

    i64 t = best(s.back());
    cout << t << '\n';
}