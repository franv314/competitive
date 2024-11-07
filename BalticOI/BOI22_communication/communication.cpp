#include <bits/stdc++.h>
#include "communication.h"
using namespace std;

struct Range {
    int l, r;

    int size() const { return r - l; }

    pair<Range, Range> split(int take) const { return {{l, l + take}, {l + take, r}}; }
};

struct Set {
    vector<Range> ranges;

    bool has(int x) const {
        return any_of(ranges.begin(), ranges.end(), [&](const Range &r) { return r.l <= x && x < r.r; });
    }

    int size() const {
        int ans = 0;
        for (auto range: ranges)
            ans += range.size();
        return ans;
    }

    pair<Set, Set> split(bool extra_left) const {
        int size_left = (size() + extra_left) / 2;

        Set l, r;
        for (auto &range: ranges) {
            if (size_left == 0) {
                r.ranges.push_back(range);
            } else if (range.size() <= size_left) {
                l.ranges.push_back(range);
                size_left -= range.size();
            } else {
                auto [left, right] = range.split(size_left);
                l.ranges.push_back(left);
                r.ranges.push_back(right);
                size_left -= left.size();
            }
        }

        return {l, r};
    }

    Set join(const Set &o) const {
        Set ans = o;
        copy(ranges.begin(), ranges.end(), back_inserter(ans.ranges));
        return ans;
    }

    vector<int> enumerate() const {
        vector<int> ans;
        for (auto [l, r]: ranges)
            for (int i = l; i < r; i++)
                ans.push_back(i);
        return ans;
    }
};

void encode(int N, int X) {    
    Set T = {{{1, N + 1}}};
    Set F = {{}};

    while (T.size() + F.size() > 3) {
        auto [I_T, D_T] = T.split(true);
        auto [I_F, D_F] = F.split(false);

        bool recv = send(I_T.has(X) || I_F.has(X));
        if (recv) {
            T = I_T.join(I_F);
            F = D_T;
        } else {
            T = D_T.join(D_F);
            F = I_T;
        }
    }

    vector<int> T_left = T.enumerate();
    vector<int> F_left = F.enumerate();

    vector<int> left;
    copy(T_left.begin(), T_left.end(), back_inserter(left));
    copy(F_left.begin(), F_left.end(), back_inserter(left));

    int last = find(left.begin(), left.end(), X) - left.begin();

    switch (last) {
    case 0: send(0); send(0); send(0); send(0); break;
    case 1: send(0); send(1); send(1); send(0); break;
    case 2: send(1); send(0); send(0); send(1); break;
    }
}

pair<int, int> ending_guesses(vector<int> packet) {
    int val = packet[0] | 2 * packet[1] | 4 * packet[2] | 8 * packet[3];
    switch (val) {
        case  0: return {0, 2};
        case  1: return {0, 2};
        case  2: return {0, 1};
        case  3: return {1, 2};
        case  4: return {0, 1};
        case  5: return {0, 0};
        case  6: return {1, 1};
        case  7: return {1, 1};
        case  8: return {0, 2};
        case  9: return {0, 2};
        case 10: return {0, 0};
        case 11: return {2, 2};
        case 12: return {1, 2};
        case 13: return {2, 2};
        case 14: return {1, 1};
        case 15: return {1, 1};
    }
}

pair<int, int> decode(int N) {
    Set T = {{{1, N + 1}}};
    Set F = {{}};

    while (T.size() + F.size() > 3) {
        auto [I_T, D_T] = T.split(true);
        auto [I_F, D_F] = F.split(false);

        if (receive()) {
            T = I_T.join(I_F);
            F = D_T;
        } else {
            T = D_T.join(D_F);
            F = I_T;
        }
    }

    vector<int> T_left = T.enumerate();
    vector<int> F_left = F.enumerate();

    vector<int> left;
    copy(T_left.begin(), T_left.end(), back_inserter(left));
    copy(F_left.begin(), F_left.end(), back_inserter(left));

    auto [t1, t2] = ending_guesses({receive(), receive(), receive(), receive()});
    return {left[t1], left[t2]};
}
