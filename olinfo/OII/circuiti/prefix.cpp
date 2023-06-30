#include <bits/stdc++.h>
using namespace std;

#define lo first
#define hi second
typedef pair<int, int> Range;

char name[1000];

int N;
char file_out[6];

int main() {
    scanf("%d %5s", &N, file_out);
    FILE *fw = fopen(file_out, "w");

    map<Range, string> names;
    vector<bool> known(N, false);
    int vars = 0;
    known[0] = known[1] = true;
    
    // Inserisco nella mappa i nomi dell'input
    for (int i = 0; i < N; i++) {
        sprintf(name, "in[%d]", i);
        names[{i + 1, i + 1}] = string(name);
    }

    // Costruisco il segment tree
    for (int size = 2; size <= N; size *= 2) {
        known[size] = true;

        sprintf(name, "out[%d]", size - 1);
        names[{1, size}] = name;
        fprintf(
            fw,
            "%s = %s + %s\n",
            names[{1, size}].c_str(),
            names[{1, size/ 2}].c_str(),
            names[{size / 2 + 1, size}].c_str()
        );

        for (Range r = {size + 1, 2 * size}; r.hi <= N; r.lo += size, r.hi += size) {
            sprintf(name, "temp[%d]", vars++);
            names[r] = name;
            fprintf(
                fw,
                "%s = %s + %s\n",
                names[r].c_str(),
                names[{r.lo, (r.lo + r.hi )/ 2}].c_str(),
                names[{(r.lo + r.hi) / 2 + 1, r.hi}].c_str()
            );
        }
    }
    
    // Costruisco le soluzioni
    for (int i = 1; i <= N; i++) {
        if (names.find({1, i}) != names.end()) continue;

        int from = i;
        for (int j = 0; !known[from]; j++) {
            from &= ~(1 << j);
        }
        
        fprintf(
            fw,
            "out[%d] = %s + %s\n",
            i - 1,
            names[{1, from}].c_str(),
            names[{from + 1, i}].c_str()
        );

        sprintf(name, "out[%d]", i - 1);
        names[{1, i}] = name;
        known[i] = true;
    }
    fputs("out[0] = in[0] + 0\n", fw);

    fclose(fw);
    return 0;
}