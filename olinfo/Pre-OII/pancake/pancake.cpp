const int fact[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int N;
int calls = 0;

int x(int X) {
    for (int i = N - 1; i; i--)
        if (X % fact[i] == 0)
            return i;
}

void prepara(int N) {
    ::N = N;
}

int ribalta() {
    return 1 + x(++calls);
}