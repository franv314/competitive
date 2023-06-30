#define MIN(a,b) (a < b ? a : b)
#define MAXN 5000000
#define MAXK 20

bool attack(int);

int N, K;
int memo[MAXK + 1][MAXN + 1];
int opt[MAXK + 1][MAXN + 1];

void init(int N, int K) {
    ::N = N, ::K = K;

    for (int x = 1; x <= N; x++) {
        for (int i = 1; i <= K; i++) {
            memo[i][x] = MIN(memo[i - 1][x - 1] + memo[i][x - 1] + 1, 2 * MAXN);
        }
    }

    for (int n = 1; n <= N; n++) {
        for (int k = 1; k <= K; k++) {
            int l = 1, r = N;
            while (l < r) {
                int m = (l + r) / 2;
                if (memo[k][m] >= n)
                    r = m;
                else
                    l = m + 1;
            }
            opt[k][n] = l;
        }
    }
}

int find_optimal(int lives, int floors) {
    if (lives == 1 || floors == 0 || floors == 1) return 0;

    int l = 1, r = floors;
    while (l < r) {
        int m = (l + r) / 2;
        if (opt[lives - 1][m] >= opt[lives][floors])
            r = m;
        else
            l = m + 1;
    }
    return l - 1;
}

int new_pokemon() {
    int min_floor = 0, max_floor = N, lives = K;

    while (min_floor < max_floor) {
        int opt = find_optimal(lives, max_floor - min_floor);
        if (attack(min_floor + opt)) {
            min_floor = min_floor + opt + 1;
        } else {
            lives--;
            max_floor = min_floor + opt; 
        };
    }
    return min_floor;
}