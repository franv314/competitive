#include <bits/stdc++.h>
using namespace std;

constexpr long long max_len = 1e18;

struct Info {
    long long mult;
    vector<int> add;

    Info() : mult(1), add() { }
};

void solve() {
    int n, q; cin >> n >> q;

    vector<Info> info;
    Info curr_info;

    long long curr_len = 0;
    bool done = false;

    while (n--) {
        int b, x; cin >> b >> x;
        if (done) continue;
        if (b == 1) {
            curr_info.add.push_back(x);
            curr_len++;
        } else {
            curr_info.mult = x + 1;
            if (curr_info.mult >= (max_len + curr_len - 1) / curr_len) {
                curr_info.mult = (max_len + curr_len - 1) / curr_len;
                curr_len *= curr_info.mult;
                done = true;
            } else {
                curr_len *= curr_info.mult;
                info.push_back(curr_info);
                curr_info = Info();
            }
        }
    }

    info.push_back(curr_info);

    reverse(info.begin(), info.end());

    while (q--) {
        long long k; cin >> k;
        k--;
        long long l = curr_len;

        for (auto [mult, add]: info) {
            long long block_size = l / mult;

            k %= block_size;
            l /= mult;

            if ((int)add.size() - (block_size - k) >= 0) {
                cout << add[add.size() - (block_size - k)] << " ";
                break;
            }

            l -= add.size();
        }
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}