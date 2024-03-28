#include <bits/stdc++.h>
using namespace std;

void solve() {
    char str[6]; scanf("%5s", str);
    str[2] = '\0';
    int h = atoi(str);
    int m = atoi(str + 3);

    printf("%02d:%02d %s\n", h % 12 ? h % 12 : 12, m, h < 12 ? "AM" : "PM");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; scanf("%d", &t);
    while (t--) solve();
}