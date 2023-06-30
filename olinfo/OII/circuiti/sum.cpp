#include <bits/stdc++.h>
using namespace std;

int N;
char file_out[6];

FILE *fw;
int vars;
char name[1000];

string recursive(int l, int r) {
    if (l + 1 == r) {
        sprintf(name, "in[%d]", l);
        return name;
    }
    string s1 = recursive(l, (l + r) / 2);
    string s2 = recursive((l + r) / 2, r);
    r - l != N ? sprintf(name, "temp[%d]", vars++) : sprintf(name, "out[0]");
    fprintf(fw, "%s = %s + %s\n", name, s1.c_str(), s2.c_str());

    return name;
}

int main() {
    scanf("%d %5s", &N, file_out);
    fw = fopen(file_out, "w");

    recursive(0, N);

    return 0;
}