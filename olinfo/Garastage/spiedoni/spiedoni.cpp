#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

void scambia(int x, int y);

void scambia(string &S, string &T, int x, int y) {
    string S1 = S.substr(0, x), S2 = S.substr(x);
    string T1 = T.substr(0, y), T2 = T.substr(y);

    S = T1 + S2;
    T = S1 + T2;
    scambia(x, y);
}

void preprocess(string &S, string &T) {
    vector<int> breaks_s(1), breaks_t(1);
    for (int i = 1; i < S.size(); i++)
        if (S[i] != S[i - 1])
            breaks_s.push_back(i);
    for (int i = 1; i < T.size(); i++)
        if (T[i] != T[i - 1])
            breaks_t.push_back(i);

    if (breaks_s.size() == 1 && breaks_t.size() == 1) return;
    if (breaks_s.size() == 1 && breaks_t.size() == 2) {
        scambia(0, breaks_t[1]);
        return;
    }
    if (breaks_t.size() == 1 && breaks_s.size() == 2) {
        scambia(breaks_s[1], 0);
        return;
    }
    if (breaks_s.size() == 1 || breaks_t.size() == 1) {
        if (breaks_s.size() == 1 && (breaks_t.size() & 1 || breaks_t.size() < 6)) {
            scambia(S, T, 0, breaks_t[2]);
            preprocess(S, T);
        } else if (breaks_t.size() == 1 && (breaks_s.size() & 1 || breaks_s.size() < 6)) {
            scambia(S, T, breaks_s[2], 0);
            preprocess(S, T);
        } else if (breaks_s.size() == 1) {
            scambia(S, T, 0, breaks_t[3]);
            preprocess(S, T);
        } else if (breaks_t.size() == 1) {
            scambia(S, T, breaks_s[3], 0);
            preprocess(S, T);
        }
        return;
    }

    int mod = (max(breaks_s.size(), breaks_t.size()) - min(breaks_s.size(), breaks_t.size())) % 4;
    if (mod == 0) {
        if (breaks_s.size() < breaks_t.size())
            scambia(S, T, breaks_s[1], breaks_t[(breaks_t.size() - breaks_s.size() + 2) / 2]);
        else if (breaks_s.size() > breaks_t.size())
            scambia(S, T, breaks_s[(breaks_s.size() - breaks_t.size() + 2) / 2], breaks_t[1]);
    } else if (mod == 1) {
        if (breaks_s.size() < breaks_t.size())
            scambia(S, T, 0, breaks_t[(breaks_t.size() - breaks_s.size() + 1) / 2]);
        else if (breaks_s.size() > breaks_t.size())
            scambia(S, T, breaks_s[(breaks_s.size() - breaks_t.size() + 1) / 2], 0);
    } else if (mod == 3) {
        if (breaks_s.size() < breaks_t.size())
            scambia(S, T, breaks_s[1], breaks_t[2]);
        else if (breaks_s.size() > breaks_t.size())
            scambia(S, T, breaks_s[2], breaks_t[1]);
        preprocess(S, T);
    } else {
        if (breaks_s.size() < breaks_t.size())
            scambia(S, T, 0, breaks_t[(breaks_t.size() - breaks_s.size()) / 2]);
        else if (breaks_s.size() > breaks_t.size())
            scambia(S, T, breaks_s[(breaks_s.size() - breaks_t.size()) / 2], 0);
    }
}

void prepreprocess(string &S, string &T) {
    vector<int> breaks_s(1), breaks_t(1);
    for (int i = 1; i < S.size(); i++)
        if (S[i] != S[i - 1])
            breaks_s.push_back(i);
    for (int i = 1; i < T.size(); i++)
        if (T[i] != T[i - 1])
            breaks_t.push_back(i);

    if (breaks_s.size() == 1 && breaks_t.size() == 2) {
        scambia(S, T, S.size(), breaks_t[1]);
        return;
    }
    if (breaks_s.size() == 2 && breaks_t.size() == 1) {
        scambia(S, T, breaks_s[1], T.size());
        return;
    }

    if (breaks_s.size() == 1 && (breaks_t.size() & 1)) {
        scambia(S, T, S.size(), breaks_t[2]);
        preprocess(S, T);
        return;
    }
    if (breaks_t.size() == 1 && (breaks_s.size() & 1)) {
        scambia(S, T, breaks_s[2], T.size());
        preprocess(S, T);
        return;
    }
    if (breaks_s.size() == 1) {
        scambia(S, T, S.size(), breaks_t[3]);
        preprocess(S, T);
        return;
    }
    if (breaks_t.size() == 1) {
        scambia(S, T, breaks_s[3], T.size());
        preprocess(S, T);
        return;
    }

    if (breaks_s.size() == 2 && breaks_t.size() == 5) {
        scambia(S, T, breaks_s[1], breaks_t[3]);
        prepreprocess(S, T);
        return;
    }
    if (breaks_s.size() == 5 && breaks_t.size() == 2) {
        scambia(S, T, breaks_s[3], breaks_t[1]);
        prepreprocess(S, T);
        return;
    }

    if (breaks_s.size() % 2 == breaks_t.size() % 2) {
        if (breaks_s.size() < breaks_t.size())
            scambia(S, T, S.size(), breaks_t.back());
        else
            scambia(S, T, breaks_s.back(), T.size());
        preprocess(S, T);
    } else {
        if ((breaks_s.size() + breaks_t.size()) % 4 == 1) {
            if (breaks_s.size() & 1)
                scambia(S, T, breaks_s.back(), T.size());
            else
                scambia(S, T, S.size(), breaks_t.back());
        } else {
            if (breaks_s.size() & 1)
                scambia(S, T, S.size(), breaks_t.back());
            else
                scambia(S, T, breaks_s.back(), T.size());
        }
        preprocess(S, T);
    }
}

void uniforma(string S, string T) {
    //cout << S _ T << endl;

    if (S.back() != T.back())
        preprocess(S, T);
    else
        prepreprocess(S, T);

    int pos_s = S.size() - 1, pos_t = T.size() - 1;
    for (;;) {
        while (pos_s && S[pos_s] == S[pos_s - 1]) pos_s--;
        while (pos_s && pos_t && T[pos_t] == T[pos_t - 1]) pos_t--;
        if (!pos_s || !pos_t) break;

        scambia(pos_s, pos_t);
        swap(S, T);
        swap(pos_s, pos_t);
        pos_s--, pos_t--;
    }
}