#include <bits/stdc++.h>
using namespace std;

enum t {
    NONE, SUM, MAX_PREF, MAX_SUFF, MAX_SUB
};

typedef tuple<t, int, int> Range;

char name[1000], temp[1000], temp2[1000];

int N;
char file_out[6];

int main() {
    scanf("%d %5s", &N, file_out);
    FILE *fw = fopen(file_out, "w");

    map<Range, string> names;
    vector<Range> ranges = {};
    int vars = 0;
    for (int i = 0; i < N; i++) {
        ranges.push_back({NONE, i, i});

        sprintf(name, "temp[%d]", vars++);
        fprintf(
            fw,
            "%s = in[%d] max 0\n",
            name,
            i
        );
        names[{MAX_PREF, i, i}] = name;
        names[{MAX_SUFF, i, i}] = name;
        names[{MAX_SUB, i, i}] = name;
        
        sprintf(name, "in[%d]", i);
        names[{SUM, i, i}] = name;
    }
    
    while (ranges.size() > 1) {
        vector<Range> new_ranges = {};
        for (int i = 0; i + 1 < ranges.size(); i += 2) {
            auto [_0, l, ml] = ranges[i];
            auto [_1, mr, r] = ranges[i + 1];
            new_ranges.push_back({NONE, l, r});

            // SUM of merged range
            sprintf(name, "temp[%d]", vars++);
            fprintf(
                fw,
                "%s = %s + %s\n",
                name,
                names[{SUM, l, ml}].c_str(),
                names[{SUM, mr, r}].c_str()
            );
            names[{SUM, l, r}] = name;

            // MAXPREF of merged range
            if (l != 0) {
                sprintf(temp, "temp[%d]", vars++);
                fprintf(
                    fw,
                    "%s = %s + %s\n",
                    temp,
                    names[{MAX_PREF, mr, r}].c_str(),
                    names[{SUM, l, ml}].c_str()
                );

                sprintf(name, "temp[%d]", vars++);
                fprintf(
                    fw,
                    "%s = %s max %s\n",
                    name,
                    temp,
                    names[{MAX_PREF, l, ml}].c_str()
                );
                names[{MAX_PREF, l, r}] = name;
            }

            // MAXSUFF of merged range
            if (r != N - 1) {
                sprintf(temp, "temp[%d]", vars++);
                fprintf(
                    fw,
                    "%s = %s + %s\n",
                    temp,
                    names[{SUM, mr, r}].c_str(),
                    names[{MAX_SUFF, l, ml}].c_str()
                );

                sprintf(name, "temp[%d]", vars++);
                fprintf(
                    fw,
                    "%s = %s max %s\n",
                    name,
                    temp,
                    names[{MAX_SUFF, mr, r}].c_str()
                );
                names[{MAX_SUFF, l, r}] = name;
            }

            // MAXSUB of merged range
            sprintf(temp, "temp[%d]", vars++);
            fprintf(
                fw,
                "%s = %s + %s\n",
                temp,
                names[{MAX_SUFF, l, ml}].c_str(),
                names[{MAX_PREF, mr, r}].c_str()
            );

            sprintf(temp2, "temp[%d]", vars++);
            fprintf(
                fw,
                "%s = %s max %s\n",
                temp2,
                temp,
                names[{MAX_SUB, l, ml}].c_str()
            );

            if (ranges.size() > 2) sprintf(name, "temp[%d]", vars++);
            else sprintf(name, "out[0]");
            fprintf(
                fw,
                "%s = %s max %s\n",
                name,
                temp2,
                names[{MAX_SUB, mr, r}].c_str()
            );
            names[{MAX_SUB, l, r}] = name;
        }
        if (ranges.size() & 1) {
            new_ranges.push_back(ranges.back());
        }
        ranges = new_ranges;
    }

    return 0;
}