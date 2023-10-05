#include <vector>
using namespace std;

void riprogramma(int N, int K, vector<int>& C) {
    for (auto &c: C) c--;

    if (K > 2) {
        for (int i = 1; i < N; i++) {
            if (C[i] == C[i - 1]) {
                if (i == N - 1 || C[i + 1] != (C[i] + 1) % K) C[i] = (C[i] + 1) % K;
                else C[i] = (C[i] + 2) % K;
            }
        }
    } else {
        int same = 0, diff = 0;
        for (int i = 0; i < N; i++) {
            same += (C[i] % 2) == i % 2;
            diff += (C[i] % 2) != i % 2;
        }

        for (int i = 0; i < N; i++) {
            C[i] = (diff > same) ^ (i & 1);
        }
    }

    for (auto &c: C) c++;
}
