#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int riga;
    int colonna;
} cella_t;

typedef enum {
    SOPRA,
    SOTTO,
    DESTRA,
    SINISTRA
} direzione_t;

cella_t posizione_mela();
void muovi(direzione_t);

void gioca(int R, int C) {
    if (R & 1) {
        for (int _ = 0; _ < R * C; _++) {
            int i = 1;
            for (; i < C; i++)
                muovi(DESTRA);
            muovi(SOTTO);
            for (i--; i >= 0; i--) {
                for (int j = 2; j < R; j++) {
                    muovi(i & 1 ? SOTTO : SOPRA);
                }
                muovi(i ? SINISTRA : SOPRA);
            }
        }
    } else {
        for (int _ = 0; _ < R * C; _++) {
            int i = 1;
            for (; i < R; i++)
                muovi(SOTTO);
            muovi(DESTRA);
            for (i--; i >= 0; i--) {
                for (int j = 2; j < C; j++) {
                    muovi(i & 1 ? DESTRA : SINISTRA);
                }
                muovi(i ? SOPRA : SINISTRA);
            }
        }
    }
}