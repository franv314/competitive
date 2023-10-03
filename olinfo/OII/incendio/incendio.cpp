#define abs(a) ((a) > 0 ? (a) : -(a))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define MAXM 12'002
#define START (M)
#define END (M + 1)

bool visited[MAXM];
int distance[MAXM];

int alzati(int N, int M, int X[], int Y[]) {
    auto dist = [&](int i, int j) -> int {
        if (i == END && j == START) return 2e9;
        if (j == END && i == START) return 2e9;

        if (i == START) return min(N - X[j] - 1, Y[j]);
        if (j == START) return min(N - X[i] - 1, Y[i]);

        if (i == END) return min(X[j], N - Y[j] - 1);
        if (j == END) return min(X[i], N - Y[i] - 1);

        int dx = abs(X[i] - X[j]);
        int dy = abs(Y[i] - Y[j]);
        if (dx == 0) return dy / 2;
        if (dy == 0) return dx / 2;
        return (dx + dy - 1) / 2;
    };

    for (int i = 0; i < M + 2; i++) distance[i] = 2e9;
    distance[START] = 0;

    for (int _ = 0; _ < M + 2; _++) {
        int dst = 2e9, closest;
        for (int i = 0; i < M + 2; i++)
            if (!visited[i] && distance[i] < dst)
                dst = distance[closest = i];

        visited[closest] = true;
        for (int i = 0; i < M + 2; i++) {
            distance[i] = min(distance[i], max(dst, dist(closest, i)));
        }
    }

    return distance[END] - 1;
}