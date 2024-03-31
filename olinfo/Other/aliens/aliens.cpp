bool examine(int X, int Y);
void solution(int Xc, int Yc);

void find_centre(int N, int Xi, int Yi) {
    long long l, r;

    l = Xi, r = N + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (examine(m, Yi)) l = m;
        else r = m;
    }
    long long x0 = l;

    l = Yi, r = N + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (examine(x0, m)) l = m;
        else r = m;
    }
    long long y0 = l;

    l = 0, r = N + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        
        long long qx = x0 + m, qy = y0 + m;
        if (qx > N || qy > N || !examine(qx, qy)) r = m;
        else l = m;
    }
    long long x1 = x0 + l, y1 = y0 + l;

    l = 0, r = N + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        
        long long qx = x0 - m, qy = y0 - m;
        if (qx <= 0 || qy <= 0 || !examine(qx, qy)) r = m;
        else l = m;
    }
    long long x2 = x0 - l, y2 = y0 - l;

    long long x3 = (x1 + x2) / 2, y3 = (y1 + y2) / 2;

    l = 0, r = N + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        
        long long qx = x3 + m, qy = y3 - m;
        if (qx > N || qy <= 0 || !examine(qx, qy)) r = m;
        else l = m;
    }
    long long x4 = x3 + l, y4 = y3 - l;

    l = 0, r = N + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        
        long long qx = x3 - m, qy = y3 + m;
        if (qx <= 0 || qy > N || !examine(qx, qy)) r = m;
        else l = m;
    }
    long long x5 = x3 - l, y5 = y3 + l;

    long long x6 = (x4 + x5) / 2, y6 = (y4 + y5) / 2;

    solution(x6, y6);
}
