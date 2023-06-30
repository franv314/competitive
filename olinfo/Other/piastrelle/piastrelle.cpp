#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

FILE *fr, *fw;
int M;

void recursive(string s) {
    if (s.size() == 3 * M) {
        fprintf(fw, "%s\n", s.c_str());
    } else if (s.size() == 3 * M - 3) {
        fprintf(fw, "%s[O]\n", s.c_str());
    } else {
        recursive(s + "[O]");
        recursive(s + "[OOOO]");
    }
}

int main() {
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    fscanf(fr, "%d", &M);
    recursive("");

    return 0;
}