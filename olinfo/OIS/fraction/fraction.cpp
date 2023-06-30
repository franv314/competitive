#include <bits/stdc++.h>
using namespace std;

int period(int N) {
    vector<int> last_occurrence(N, -1);
    int curr_remainder = 1, i;
    for (i = 0; last_occurrence[curr_remainder] == -1; i++) {
        last_occurrence[curr_remainder] = i;
        curr_remainder = (10 * curr_remainder) % N;
        if (curr_remainder == 0) return 0;
    }
    return i - last_occurrence[curr_remainder];
}

int cycle(int N) {
    int max_p = INT_MIN, max_n;
    for (int i = 2; i < N; i++) {
        int p = period(i);
        if (p >= max_p) {
            max_p = p;
            max_n = i;
        }
    }
    return max_n;
}


int main() {
    int N;

    assert(1 == scanf("%d", &N));
    printf("%d\n", cycle(N));
    return 0;
}
