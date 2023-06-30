#include <bits/stdc++.h>
using namespace std;

#define MAXN 100'000
#define LSB(x) ((x) & -(x))

void nuovo_gruppo();
void aggiungi(int bambino);

int *nemico;
int gruppo[MAXN + 1];
bool visto[MAXN];

void rec(int bambino, int came_from = MAXN) {
    if (gruppo[bambino]) return;
    bool recur = !visto[bambino];
    visto[bambino] = true;
    if (recur) rec(nemico[bambino], bambino);

    gruppo[bambino] = LSB(7 & ~gruppo[came_from] & ~gruppo[nemico[bambino]]);
}

void smista(int N, int nemico[]) {
    ::nemico = nemico;
	for (int i = 0; i < N; i++) {
        if (visto[i]) continue;
        rec(i);
    }
    for (auto x: {1, 2, 4}) {
        nuovo_gruppo();
        for (int i = 0; i < N; i++)
            if (gruppo[i] == x)
                aggiungi(i);
    }
}
