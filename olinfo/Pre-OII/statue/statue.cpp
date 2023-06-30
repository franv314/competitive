#include <bits/stdc++.h>
using namespace std;

long long somma(int l, int r);
long long subarray_massimo(int l, int r);
long long subarray_minimo(int l, int r);

#define SUB_MAX(l, r) (l < r ? subarray_massimo(l, (r) - 1) : 0)
#define SUB_MIN(l, r) (l < r ? subarray_minimo(l, (r) - 1) : 0)
#define SUM(l, r) (l < r ? somma(l, (r) - 1) : 0)

#define SIZE 400

long long trova(int n) {
    long long tot_sum = 0, tot_max_sub = -1e14, tot_max_suff = -1e14;

    for (int l = 0, r = SIZE; l < n; r += SIZE, l += SIZE) {
        long long sum = SUM(l, r), max_sub = SUB_MAX(l, r), min_sub = SUB_MIN(l, r);
        long long max_pref, max_suff;

        if (max_sub >= -min_sub) {
            int _l = l, _r = r;
            while (_l < _r) {
                int m = (_l + _r) / 2;
                if (SUB_MAX(l, m) == max_sub)
                    _r = m;
                else
                    _l = m + 1;
            }
            max_pref = SUM(l, _l);
            max_suff = sum + max_sub - max_pref;
        } else {
            int _l = l, _r = r;
            while (_l < _r) {
                int m = (_l + _r) / 2;
                if (SUB_MIN(l, m) == min_sub)
                    _r = m;
                else
                    _l = m + 1;
            }
            max_suff = SUM(_l, r);
            max_pref = sum - min_sub - max_suff;
        }

        tot_max_sub = max({tot_max_sub, max_sub, tot_max_suff + max_pref});
        tot_max_suff = max(tot_max_suff + sum, max_suff);
        tot_sum += sum;
    }

    return tot_max_sub;
}