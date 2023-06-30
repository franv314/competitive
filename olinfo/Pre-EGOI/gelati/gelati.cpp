#include <vector>
#include <algorithm>
using namespace std;

int presta(int N, int C, vector<int> P) {
    sort(P.begin(), P.end());
    int sum = 0, i = 0;
    while (sum < C) {
        sum += P.back();
        P.pop_back();
        i++;
    }
    return i;
}