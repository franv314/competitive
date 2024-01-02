#include <bits/stdc++.h>
using namespace std;

#define MAXN 25

long long f[MAXN + 1], g[MAXN + 1];

void calc() {
    f[0] = g[0] = 1;
    for (int n = 1; n <= MAXN; n++) {
        for (int i = 0; i < n; i++) {
            f[n] += g[i] * g[n - 1 - i];
        }
        for (int i = 1; i <= n; i++) {
            g[n] += f[i] * g[n - i];
        }
    }
}

struct NodeInfo {
    long long small_mrg[MAXN + 1];
    long long small_cat[MAXN + 1];

    NodeInfo() {
        fill(small_mrg, small_mrg + MAXN + 1, 0);
        fill(small_cat, small_cat + MAXN + 1, 0);
    }
};

long long encode(int n, string s) {
    auto find_closed = [&](const string &s, bool split) {
        int open = 0;
        if (s[0] == '|') return -1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') open++;
            if (s[i] == ')') open--;

            if (open == 0 && (!split || s[i + 1] == '|')) return i;
        }
        assert(false);
    };

    function<NodeInfo(string)> tree = [&](string s) {
        NodeInfo info;
        if (s == "") {
            return info;
        }

        int close = find_closed(s, false);
        if (close < s.size() - 1) {
            string l = s.substr(0, close + 1);
            string r = s.substr(close + 1);

            NodeInfo info_l = tree(l);
            NodeInfo info_r = tree(r);

            for (int s = 1; s <= MAXN; s++) {
                for (int sl = 1; sl < s; sl++) {
                    int sr = s - sl;
                    info.small_cat[s] += info_l.small_mrg[sl] * g[sr];
                }
            }

            for (int s = l.size() / 3 + 1; s <= MAXN; s++) {
                int sr = s - l.size() / 3;
                info.small_cat[s] += info_r.small_cat[sr] + info_r.small_mrg[sr];
            }
            info.small_cat[0] = 1;

            return info;
        }

        s = s.substr(1, s.size() - 1);
        close = find_closed(s, true);

        string l = s.substr(0, close + 1);
        string r = s.substr(close + 2, s.size() - l.size() - 2);

        NodeInfo info_l = tree(l);
        NodeInfo info_r = tree(r);

        for (int s = 1; s <= MAXN; s++) {
            info.small_cat[s] = g[s] - f[s];
            for (int sl = 0; sl < s; sl++) {
                int sr = s - sl - 1;
                info.small_mrg[s] += (info_l.small_cat[sl] + info_l.small_mrg[sl]) * g[sr];
            }
        }
        for (int s = l.size() / 3 + 1; s <= MAXN; s++) {
            int sr = s - 1 - l.size() / 3;
            info.small_mrg[s] += info_r.small_cat[sr] + info_r.small_mrg[sr];
        }
        info.small_cat[0] = 1;

        return info;
    };

    NodeInfo info = tree(s);

    return info.small_cat[n] + info.small_mrg[n];
}

string decode(int n, long long s) {
    deque<tuple<bool, bool, string>> st;

    auto cat = [&](const string &a, const string &b) { return a + b; };
    auto mrg = [&](const string &a, const string &b) { return "(" + a + "|" + b + ")"; };

    function<string()> rec = [&]() -> string {
        int used = 0;
        int last_free_right = 0;
        bool free_right_fixed = false;

        for (int i = 0; i < st.size(); i++) {
            auto [t, side, str] = st[i];

            used += str.size() / 3 + t;
            if (!side) {
                if (!free_right_fixed) last_free_right = i + 1;
                if (!t) free_right_fixed = true;
            }
        }

        if (used == n) return "";

        string curr_try_mrg = "(|)";
        string mrg_last_mrg = "";
        string curr_try_cat = "(|)";
        for (int i = 1; i < n - used; i++) {
            mrg_last_mrg += "(|)";
            curr_try_cat += "(|)";
        }

        if (last_free_right == 0) curr_try_mrg = mrg("", mrg_last_mrg);

        for (int i = 0; i < st.size(); i++) {
            auto [t, side, str] = st[i];


            string str_mrg = str;
            if (last_free_right == i + 1) {
                str_mrg = str + mrg_last_mrg;
            }

            if (t) {
                if (!side) {
                    curr_try_mrg = mrg(curr_try_mrg, str_mrg);
                    curr_try_cat = mrg(curr_try_cat, str);
                } else {
                    curr_try_mrg = mrg(str_mrg, curr_try_mrg);
                    curr_try_cat = mrg(str, curr_try_cat);
                }
            } else {
                if (!side) {
                    curr_try_mrg = cat(curr_try_mrg, str_mrg);
                    curr_try_cat = cat(curr_try_cat, str);
                } else {
                    curr_try_mrg = cat(str_mrg, curr_try_mrg);
                    curr_try_cat = cat(str, curr_try_cat);
                }
            }
        }

        bool merge = s >= encode(n, curr_try_mrg);
        bool concat = s >= encode(n, curr_try_cat);

        if (merge) {
            st.emplace_front(true, false, "");
        } else if (concat) {
            st.emplace_front(false, false, "(|)");
        } else {
            return "";
        }

        string l = rec();
        st.pop_front();
        st.emplace_front(merge, true, l);

        string r = rec();
        st.pop_front();

        return merge ? mrg(l, r) : cat(l, r);
    };

    return rec();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    calc();

    string type; cin >> type;
    int t; cin >> t;
    
    while (t--) {
        int n; cin >> n;
        if (type == "encode") {
            string s; cin >> s;
            cout << encode(n, s) << '\n';
        }
        if (type == "decode") {
            long long s; cin >> s;
            cout << decode(n, s) << '\n';
        }
    }
}