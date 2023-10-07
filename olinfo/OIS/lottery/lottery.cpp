#include <bits/stdc++.h>
using namespace std;

#define MAXD 10'000

bool check_sum(int len, int fst_last, int snd_last, int test) {
    int mi, ma;
    if (len == 0) {
        return test == 0;
    }
    if (len == 1) {
        if (fst_last != snd_last) return 0 <= test && test <= 9;
        else return 0 <= test && test <= 9 && test != fst_last;
    }

    if (fst_last != 0) mi = len / 3;
    else if (snd_last != 0) mi = 1 + (len - 2) / 3;
    else mi = 1 + (len - 1) / 3;

    if (fst_last != 9) ma = 26 * (len / 3) + 9 * (len % 3);
    else if (snd_last != 9) ma = 17 + 26 * ((len - 2) / 3) + 9 * ((len - 2) % 3);
    else ma = 8 + 26 * ((len - 1) / 3) + 9 * ((len - 1) % 3);

    return mi <= test && test <= ma;
}

string solve(int S, string N) {
    vector<int> digits(MAXD + 2);
    vector<int> digits_ps(MAXD + 3);
    transform(N.rbegin(), N.rend(), digits.rbegin(), [](char x) { return x - '0'; });
    for (int i = 0; i < MAXD + 2; i++) digits_ps[i + 1] = digits_ps[i] + digits[i];

    bool meaniningful = false;
    bool triple = false;
    int forced_stop = MAXD + 1;
    for (int i = 0; i < MAXD; i++) {
        meaniningful |= (digits[i] != 0);
        if (meaniningful && digits[i] == digits[i + 1] && digits[i] == digits[i + 2]) {
            forced_stop = i + 2;
            triple = true;
            break;
        }
    }

    if (!triple && accumulate(digits.begin(), digits.end(), 0) == S) return N;

    for (; forced_stop > 0; forced_stop--) {
        bool found = false;
        for (int digit = digits[forced_stop] + 1; digit <= 9; digit++) {
            if (forced_stop > 1 && digit == digits[forced_stop - 1] && digit == digits[forced_stop - 2]) continue;

            int len = MAXD + 1 - forced_stop;
            int test = S - digits_ps[forced_stop] - digit;

            if (check_sum(len, digit, digits[forced_stop - 1], test)) {
                found = true;
                digits[forced_stop] = digit;
                break;
            }
        }
        if (found) break;
    }

    if (forced_stop == 0) return "-1";

    int part_sum = digits_ps[forced_stop] + digits[forced_stop];
    for (int i = forced_stop + 1; i < MAXD + 2; i++) {
        for (int digit = 0; digit <= 9; digit++) {
            if (digit == digits[i - 1] && digit == digits[i - 2]) continue;

            int len = MAXD + 1 - i;
            int test = S - part_sum - digit;

            if (check_sum(len, digit, digits[i - 1], test)) {
                digits[i] = digit;
                part_sum += digit;
                break;
            }
        }
    }
    string ans;
    transform(
        find_if(digits.begin(), digits.end(), [](int x) { return x != 0; }),
        digits.end(),
        back_inserter(ans),
        [](int x) { return x + '0'; }  
    );
    return ans;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int S; cin >> S;
        string N; cin >> N;
        cout << solve(S, N) << '\n';
    }
}