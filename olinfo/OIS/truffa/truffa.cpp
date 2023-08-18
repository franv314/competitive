#include <cstdio>
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#define MAXN 100000

int sfangate(int N, int V[]) {
    vector<int> a(V, V+N);
    sort(a.begin(), a.end());
    
    int tot = accumulate(a.begin(), a.end(), 0);
    int i = 0;
    for (auto x: a) {
        if (tot > 0) return i;
        tot -= (2 * x);
        i++;
    }
    if (tot > 0) return i;
    return -1;
}


int V[MAXN];

int main() {
    FILE *fr, *fw;
    int N, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));
    for(i=0; i<N; i++)
        assert(1 == fscanf(fr, "%d", &V[i]));

    fprintf(fw, "%d\n", sfangate(N, V));
    fclose(fr);
    fclose(fw);
    return 0;
}