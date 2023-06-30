#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
constexpr int BLOCK = 512;

struct Val {
    int coeff, exp;

    pair<bool, double> cmp(const Val &other) {
        bool order = exp >= other.exp;
        double limit = pow((double)other.coeff / coeff, 1.0 / (exp - other.exp));
        return {order, limit};
    }

    bool cmp_at(const Val &other, int pos) {
        auto [order, limit] = cmp(other);
        return order ? pos > limit : pos < limit;
    }

    long long eval(int pos) {
        long long ans = coeff, curr = pos;
        for (int e = exp; e; e >>= 1) {
            if (e & 1) ans = (ans * curr) % MOD;
            curr = (curr * curr) % MOD;
        }
        return ans;
    }

    Val() { }
    Val(int coeff, int exp) : coeff(coeff), exp(exp) { }
};

int main() {
    int N; cin >> N;
    vector<Val> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i].coeff;
        A[i].exp = 0;
    }

    int Q; cin >> Q;
    
    vector<tuple<int, int, Val>> buffer;
    buffer.reserve(BLOCK + 10);
    buffer.push_back({1, N + 1, Val(0, 0)});
    
    while (Q--) {
        int type; cin >> type;
        if (type == 1) {
            int x; cin >> x;
            auto [s, e, val] = *find_if(buffer.begin(), buffer.end(), [&](tuple<int, int, Val> t) {
                return get<0>(t) <= x && x < get<1>(t);
            });

            if (A[x].cmp_at(val, x)) {
                cout << A[x].eval(x) << "\n";
            } else {
                cout << val.eval(x) << "\n";
            }
        } else {
            int x, y, b, c; cin >> x >> y >> b >> c;
            y++;
            Val new_val(b, c);
            for (auto &[l, r, val]: buffer) {
                if (x >= r || y <= l) continue;
                if (r > y) {
                    buffer.push_back({y, r, val});
                    r = y;
                }
                if (l < x) {
                    buffer.push_back({l, x, val});
                    l = x;
                }

                auto [order, limit] = new_val.cmp(val);
                if (order) {
                    if (limit >= r - 1) continue;
                    if (limit <= l) {
                        val = new_val;
                        continue;
                    }
                    buffer.push_back({ceil(limit), r, new_val});
                    r = ceil(limit);
                } else {
                    if (limit <= l) continue;
                    if (limit >= r - 1) {
                        val = new_val;
                        continue;
                    }
                    buffer.push_back({l, ceil(limit), new_val});
                    l = ceil(limit);
                }
            }

            if (buffer.size() > BLOCK) {
                for (auto [l, r, val]: buffer) {
                    for (int i = l; i < r; i++) {
                        if (val.cmp_at(A[i], i)) {
                            A[i] = val;
                        }
                    }
                }
                buffer.clear();
                buffer.push_back({1, N + 1, Val(0, 0)});
            }
        }
    }
}