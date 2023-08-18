int trova_massimo(int N, int V[]) {
    int max = -2000;

    for (int i = 0; i < N; i++) {
        if (V[i] > max) max = V[i];
    }

    return max;
}