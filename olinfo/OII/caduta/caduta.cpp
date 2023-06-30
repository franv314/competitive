#include <bits/stdc++.h>
using namespace std;

typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;

stato_t correggi(int N, int H[], coppia_t* scambio) {
    vector<int> min_suff(N);
    set<int> ok;
    ok.insert(N - 1);
    
    for (int i = N - 1; i >= 0; i--) {
        min_suff[i] = *ok.lower_bound(i) - i + 1;
        if (H[i] >= min_suff[i])
            ok.insert(i);
    }

    if (ok.find(0) != ok.end()) return OK;
    
    long long hs = accumulate(H, H + N, 0LL);
    assert(hs <= 1e8);

    int reached = 0;
    for (int i = 0; i < N; i++) {
        if (i > reached) break;
        reached = max(reached, i + H[i] - 1);
    }
    return IMPOSSIBILE;
}