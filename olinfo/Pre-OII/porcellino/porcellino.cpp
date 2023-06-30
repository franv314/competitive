#include <cstdbool>

bool chiedi(int);

int indovina() {
    chiedi(0);
    unsigned int P = 0;
    for (int i = 0; i < 31; i++)
        if (chiedi(1 << i))
            P += (1 << i);
    return P;
}