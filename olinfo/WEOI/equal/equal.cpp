#include <bits/stdc++.h>
using namespace std;

void add(vector<int> S, long long X);
bool compare(int i, int j);

void make_all_equal(int N, int Q_add, int Q_compare) {
    for (int b = 0; (1 << b) < N; b++) {
        int bit = 1 << b;
        vector<int> S;
        for (int i = 0; i < N; i++)
            if (!(i & bit))
                S.push_back(i);
        for (int i = 20 + b; i >= 0; i--)
            add(S, 1 << i);

        S.clear();
        for (int i = 0; i < N; i += 2 * bit)
            if (!compare(i, i + bit))
                for (int j = i; j < i + bit; j++)
                    S.push_back(j);
        add(S, 1);
    }
}
