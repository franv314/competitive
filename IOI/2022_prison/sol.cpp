    #include <bits/stdc++.h>
    #include "prison.h"
    using namespace std;
     
    vector<vector<int>> devise_strategy(int N) {
        vector<vector<int>> ans;
     
        auto rec = [&](auto &&rec, int l, int r, int pl, int pr, bool fst, int st) -> void {
            if (ans.size() <= st)
                ans.resize(st + 1, vector<int>(N + 1));
            ans[st][0] = !fst;

            for (int i = pl; i <= l; i++)
                ans[st][i] = fst ? -1 : -2;
            for (int i = r - 1; i < pr; i++)
                ans[st][i] = fst ? -2 : -1;

            if (r - l <= 2)
                return;

            int rec_l = (st + 2) / 3 * 3 + 1;
            int rec_m = (st + 2) / 3 * 3 + 2;
            int rec_r = (st + 2) / 3 * 3 + 3;

            int len = (r - l - 2);
            int m1 = l + 1 + len / 3;
            int m2 = m1 + len / 3 + (len % 3 == 2);

            if (r - l <= 6) {
                m1 = (l + r) / 2;
                m2 = r - 1;
            }

            for (int i = l + 1; i < m1; i++)
                ans[st][i] = rec_l;
            for (int i = m1; i < m2; i++)
                ans[st][i] = rec_m;
            for (int i = m2; i < r - 1; i++)
                ans[st][i] = rec_r;

            rec(rec, l + 1, m1, l, r, !fst, rec_l);
            rec(rec, m1, m2, l, r, !fst, rec_m);
            if (r - l > 6)
                rec(rec, m2, r - 1, l, r, !fst, rec_r);
        };
     
        rec(rec, 1, N + 1, 1, N + 1, true, 0);

        return ans;
    }