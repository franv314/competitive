#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct Fraction {
    i64 num, den;

    Fraction(i64 num, i64 den) : num(num), den(den) { }
    Fraction() : Fraction(0, 0) { }
    Fraction operator-() const { return Fraction(-num, den); }
    Fraction operator+(const Fraction &o) const { return Fraction(num * o.den + den * o.num, den * o.den); }
    Fraction operator-(const Fraction &o) const { return (*this) + (-o); }
    Fraction operator*(const Fraction &o) const { return Fraction(num * o.num, den * o.den); }
};

struct Line {
    i64 m, q;
    Line(i64 m, i64 q) : m(m), q(q) { }
    Line() : Line(0, 0) { }
    Fraction operator()(Fraction &x) {
        return Fraction(m, 1) * x + Fraction(q, 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;

    vector<pair<Line, int>> dishes(N);
    for (int i = 0; i < N; i++) {
        int t, p; cin >> t >> p;
        dishes[i] = {{t - p, p}, i};
    }

    vector<pair<Fraction, int>> people(M);
    for (int i = 0; i < M; i++) {
        int t, p; cin >> t >> p;
        people[i] = {Fraction(t, t + p), i};
    }

    sort(dishes.begin(), dishes.end(), [&](const pair<Line, int> &a, const pair<Line, int> &b) {
        return tie(a.first.m, a.second) < tie(b.first.m, b.second); 
    });
    sort(people.begin(), people.end(), [&](const pair<Fraction, int> &a, const pair<Fraction, int> &b) {
        auto [na, da] = a.first;
        auto [nb, db] = b.first;

        return na * db < nb * da;
    });
    vector<int> ans(M);

    function<void(int, int, int, int)> rec = [&](int dl, int dr, int pl, int pr) {
        if (pl >= pr) return;

        int pm = (pl + pr) / 2;
        pair<Fraction, int> curr_best = {Fraction(-1, 1), -1};

        for (int i = dl; i < dr; i++) {
            auto [old_num, old_den] = curr_best.first;
            auto [new_num, new_den] = dishes[i].first(people[pm].first);
            
            if (
                new_num * old_den > old_num * new_den ||
                (new_num * old_den == old_num * new_den && dishes[i].second < dishes[curr_best.second].second)
            ) {
                curr_best = {Fraction(new_num, new_den), i};
            }
        }

        ans[people[pm].second] = dishes[curr_best.second].second;

        rec(dl, curr_best.second + 1, pl, pm);
        rec(curr_best.second, dr, pm + 1, pr);
    };

    rec(0, N, 0, M);

    for (auto x: ans) cout << x + 1 << '\n';
}