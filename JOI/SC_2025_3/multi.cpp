#include <bits/stdc++.h>
using namespace std;

constexpr int N = 32;
ofstream out("output_02.txt");

struct Strat {
    vector<array<bool, N>> write;
    vector<array<int, N>> ask;
} strat;

array<bool, N> check(array<bool, N> write, array<int, N> ask) {
    // Output
    strat.write.push_back(write);
    strat.ask.push_back(ask);

    // Answer
    array<bool, N> ans;
    for (int i = 0; i < N; i++)
        ans[i] = write[ask[i]];
    return ans;
}

void solve(int parent) {
    array<bool, N> write;
    write[parent] = true;

    for (int i = 0; i < 4; i++) {
        array<int, N> ask;
        for (int j = 1; j <= N; j++) {
            if (__builtin_ctz(j) <= i)
                ask[j - 1] = (j - 1 + (2 << i)) % N;
            else
                ask[j - 1] = (j - 1 - (1 << i) + N) % N;
        }

        array<bool, N> ans = check(write, ask);

        for (int j = 0; j < N; j++) {
            write[j] |= ans[j];
        }
    }

    array<vector<int>, N> questions;
    questions.fill({1 - 1, 2 - 1, 4 - 1, 8 - 1, 16 - 1});

    for (int i = 0; i < N; i++) {
        questions[i].erase(questions[i].begin() + __builtin_ctz(i + 1));
    }

    for (int i = 0; i < 4; i++) {
        array<int, N> ask;
        for (int j = 0; j < N; j++)
            ask[j] = questions[j][i];
        check(write, ask);
    }
}

int main() {
    out << "?\n";
    for (int i = 0; i < N; i++) {
        out << i + 1 << '\n';

        strat.write.clear();
        strat.ask.clear();

        solve(i);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < strat.write.size(); j++) {
                out << (strat.write[j][i] ? 'T' : 'F') << ' ' << (strat.ask[j][i] + 1) << ' ';
            }
            out << '\n';
        }
    }
}