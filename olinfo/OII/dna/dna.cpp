#include <bits/stdc++.h>
using namespace std;

bool test(string T);

string sub(string a, int u, int v) {
    string ret = "";
    for (int i = u; i < v; i++)
        ret += a[i];
    return ret;
}

string analizza(int N) {
    int k = 128;
    int l, r, m;
    string testing;

    if (!test(string(k, '0'))) {
        l = 0, r = k;
        while (l < r) {
            m = (l + r + 1) / 2;
            if (test(string(m, '0')))
                l = m;
            else
                r = m - 1;
        }
        
        int max_0 = l, curr_0 = l;
        testing = string(max_0, '0');
        while (curr_0 <= max_0 && testing.size() <= N) {
            if (test(testing + "1")) {
                testing += "1";
                curr_0 = 0;
                l = testing.size();
            } else {
                testing += "0";
                curr_0++;
            }
        }
    } else {
        int max_0 = k, curr_0;
        
        testing = string(k, '0');
        while (test(testing) && testing.length() < N) {
            l = testing.size();
            curr_0 = 0;
            while (curr_0 <= max_0 && testing.size() <= N) {
                if (test(testing + "1")) {
                    testing += "1";
                    curr_0 = 0;
                    l = testing.size();
                } else {
                    testing += "0";
                    curr_0++;
                }
            }
        }
    }
    r = testing.size();
    while (l < r - 1) {
        if (test(sub(testing, 0, (l + r) / 2)))
            l = (l + r) / 2;
        else
            r = (l + r) / 2;
    }
    testing = sub(testing, 0, l);
    
    while (testing.size() < N) {
        if (test("0" + testing))
            testing = "0" + testing;
        else
            testing = "1" + testing;
    }

    return testing;
}