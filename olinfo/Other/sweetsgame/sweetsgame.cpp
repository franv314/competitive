#include <bits/stdc++.h>
using namespace std;

int moves[] = {
    0b000000000001,
    0b000000000010,
    0b000000000100,
    0b000000000011,
    0b000000000110,
    0b000000000111,
    0b000000001000,
    0b000000010000,
    0b000000100000,
    0b000001000000,
    0b000000011000,
    0b000000110000,
    0b000001100000,
    0b000000111000,
    0b000001110000,
    0b000001111000,
    0b000010000000,
    0b000100000000,
    0b001000000000,
    0b010000000000,
    0b100000000000,
    0b000110000000,
    0b001100000000,
    0b011000000000,
    0b110000000000,
    0b001110000000,
    0b011100000000,
    0b111000000000,
    0b011110000000,
    0b111100000000,
    0b111110000000,
};

int rot[] = {2, 6, 11, 1, 5, 10, 15, 0, 4, 9, 14, 18, 3, 8, 13, 17, 7, 12, 16};
int dp[1 << 19];

int applyrot(int mask) {
    int newmask = 0;
    for (int i = 0; i < 19; i++)
        if ((mask >> rot[i]) & 1)
            newmask |= 1 << i;
    return newmask;
}

int rec(int st) {
    if (dp[st] != -1) return dp[st];

    for (int _ = 0; _ < 6; _++) {
        for (auto mv: moves)
            if ((st | mv) == st && !rec(st & ~mv)) {
                for (int _ = 0; _ < 6; _++) {
                    dp[st] = 1;
                    st = applyrot(st);
                }
                return 1;
            }
        st = applyrot(st);
    }

    for (int _ = 0; _ < 6; _++) {
        dp[st] = 0;
        st = applyrot(st);
    }
    return 0;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int st = 0;
    for (int i = 0; i < 19; i++) {
        string x; in >> x;
        if (x != ".")
            st |= 1 << i;
    }
    
    fill(dp, dp + (1 << 19), -1);
    out << (rec(st) ? "Karlsson\n" : "Lillebror\n");
}