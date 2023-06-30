#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int N, m;
    int curr = 0, _max = 2e9, _min = -2e9;

    input >> N;
    for (int i = 0; i < N; i++) {
        input >> m;
        if (i & 1)
            _max = min(_max, m - curr);
        else
            _min = max(_min, curr - m);
        curr = 2 * m - curr;
    }

    output << (_max >= _min ? _max - _min + 1 : 0) << endl;

    return 0;
}