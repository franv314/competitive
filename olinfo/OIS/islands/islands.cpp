/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 * NOTE: it is recommended to use this even if you don't
 * understand the following code.
 */

#include <bits/stdc++.h>
using namespace std;

// constraints
#define MAXN 1000

// input data
int R, C, i, j;
int M[MAXN * MAXN];
bool T[MAXN * MAXN];

int main() {
//  uncomment the following lines if you want to read/write from files
  freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &R, &C));

    for (int i = 0; i < MAXN*MAXN; i++) T[i] = true;

    for(i=0; i<R; i++) {
        for (j=0; j<C; j++) {
            assert(1 == scanf("%d", &M[i * MAXN + j]));
            T[i * MAXN + j] = false;
        }
    }

    int isles = 0;
    int c = 0;
    // insert your code here
    for (;;) {
        while (T[c]) c++;
        if (c >= MAXN * R + C) break;
        
        set<int> isle;
        isle.clear();
        isle.insert(c);
        
        T[c] = true;
        if (!M[c]) continue;

        vector<int> touched = {c};
        int counts = 1;
        while (!touched.empty()) {
            int curr = touched.back();
            touched.pop_back();

            if (curr >= MAXN && isle.find(curr - MAXN) == isle.end() && M[curr - MAXN]) {
                touched.push_back(curr - MAXN);
                isle.insert(curr - MAXN);
                T[curr - MAXN] = true;
            }
            if (curr < MAXN * (R - 1) && isle.find(curr + MAXN) == isle.end() && M[curr + MAXN]) {
                touched.push_back(curr + MAXN);
                isle.insert(curr + MAXN);
                T[curr + MAXN] = true;
            }
            if (curr % MAXN > 0 && isle.find(curr - 1) == isle.end() && M[curr - 1]) {
                touched.push_back(curr - 1);
                isle.insert(curr - 1);
                T[curr - 1] = true;
            }
            if (curr % MAXN < C - 1 && isle.find(curr + 1) == isle.end() && M[curr + 1]) {
                touched.push_back(curr + 1);
                isle.insert(curr + 1);
                T[curr + 1] = true;
            }
            if (curr < MAXN || curr >= MAXN * (R - 1) || curr % MAXN <= 0 || curr % MAXN >= C - 1) counts = 0;
        }
        isles+=counts;
    }

    printf("%d\n", isles); // print the result
    return 0;
}
