#include <vector>
using namespace std;

long long aggiorna(int N, vector<int> A, vector<int> B) {
    long long updates = 0;
    for (int i = N - 2; i >= 0; i--) {
        long long can_update = (A[i + 1] - A[i]) / B[i];
        A[i] += B[i] * can_update;
        updates += can_update;
    }
    return updates;
}