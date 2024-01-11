#include <bits/stdc++.h>
using namespace std;

typedef complex<double> cx;

constexpr int POW = 19;
constexpr int MAX_SIZE = 1 << POW;

cx pow_r[POW], pow_ir[POW];
cx temp[MAX_SIZE], a[MAX_SIZE], b[MAX_SIZE], ans[MAX_SIZE];

void precalc() {
    pow_r[0] = exp(2i * (M_PI / MAX_SIZE));
    pow_ir[0] = exp(-2i * (M_PI / MAX_SIZE));
    for (int i = 1; i < POW; i++) {
        pow_r[i] = pow_r[i - 1] * pow_r[i - 1];
        pow_ir[i] = pow_ir[i - 1] * pow_ir[i - 1];
    }
}

template<bool inv>
void fft(cx arr[], int start = 0, int depth = 0) {
    int size = MAX_SIZE >> depth;
    int step = 1 << depth;

    if (size == 1) return;

    fft<inv>(arr, start, depth + 1);
    fft<inv>(arr, start + step, depth + 1);

    for (int i = 0; i < size; i++) {
        temp[i] = arr[start + i * step];
    }

    cx w = (inv ? pow_ir : pow_r)[depth];
    cx o = 1;

    for (int j = 0; j < size / 2; j++) {
        arr[start + j * step]
            = temp[2 * j] + o * temp[2 * j + 1];
        arr[start + (j + size / 2) * step]
            = temp[2 * j] - o * temp[2 * j + 1];

        o *= w;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;

    precalc();

    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        a[cnt] += 1.0;
        cnt += s[i] == '1';
    }
    a[cnt] += 1.0;

    cnt = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        b[cnt] += 1.0;
        cnt += s[i] == '1';
    }
    b[cnt] += 1.0;

    fft<0>(a);
    fft<0>(b);

    for (int i = 0; i < MAX_SIZE; i++) ans[i] = a[i] * b[i];

    fft<1>(ans);

    for (int i = 0; i < MAX_SIZE; i++) ans[i] /= MAX_SIZE;

    vector<long long> out(s.size() + 1);
    int block = 0;
    for (auto c: s) {
        if (c == '1') {
            out[0] += (long long)block * (block + 1) / 2;
            block = 0;
        } else {
            block++;
        }
    }
    out[0] += (long long)block * (block + 1) / 2;

    int ones = count(s.begin(), s.end(), '1');
    for (int i = 0; i < ones; i++) {
        out[ones - i] = (long long)(ans[i].real() + 0.5);
    }

    for (auto x: out) cout << x << ' ';
    cout << '\n';
}