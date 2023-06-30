int quadri(int N, long long M, int V[]) {
    long long sum = 0;
    int B = N, j = -1;
    for (int i = 0; ; i++) { 
        while (sum <= M) {
            if (++j >= N) return B;
            sum += V[j];
        }
        if (j - i < B) B = j - i;
        sum -= V[i];
    }
} 
