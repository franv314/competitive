#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegTree {
    vector<int> arr;
    vector<int> lazy;
    int s;

    void push(int n, int nb, int ne) {
        if (lazy[n] != -1) {
            arr[n] = lazy[n];

            if (nb + 1 != ne) {
                lazy[2 * n] = lazy[2 * n + 1] = lazy[n];
            }
            lazy[n] = -1;
        }
    }

    void update(int l, int r, int x, int n, int nb, int ne) {
        push(n, nb, ne);
        if (l >= ne || r <= nb) return;
        if (l <= nb && ne <= r) {
            lazy[n] = x;
            push(n, nb, ne);
            return;
        }

        update(l, r, x, 2 * n, nb, (nb + ne) / 2);
        update(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
        arr[n] = min(arr[2 * n], arr[2 * n + 1]);
    }

    optional<int> find_leftmost(int l, int r, int x, int n, int nb, int ne) {
        push(n, nb, ne);
        if (l >= ne || r <= nb || arr[n] > x) return {};
        if (nb + 1 == ne) return nb;

        optional<int> try_left = find_leftmost(l, r, x, 2 * n, nb, (nb + ne) / 2);
        if (try_left) return try_left;

        return find_leftmost(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
    }

    optional<int> find_rightmost(int l, int r, int x, int n, int nb, int ne) {
        push(n, nb, ne);
        if (l >= ne || r <= nb || arr[n] > x) return {};
        if (nb + 1 == ne) return nb;

        optional<int> try_right = find_rightmost(l, r, x, 2 * n + 1, (nb + ne) / 2, ne);
        if (try_right) return try_right;

        return find_rightmost(l, r, x, 2 * n, nb, (nb + ne) / 2);
    }

public:

    void update(int l, int r, int x) { update(l, r, x, 1, 0, s); }
    optional<int> find_leftmost(int l, int r, int x) { return find_leftmost(l, r, x, 1, 0, s); }
    optional<int> find_rightmost(int l, int r, int x) { return find_rightmost(l, r, x, 1, 0, s); }

    SegTree(int N, int def = 0) {
        s = 1 << (int)ceil(log2(N));
        arr.assign(2 * s, def);
        lazy.assign(2 * s, -1);
    }
};

struct Line {
    char dir;
    int idx, len, x, y;
};

struct Intersection {
    int line, x, y;
};

struct Event {
    bool type;
    int x, l, r, idx;
};

Intersection check_hor_overlap(const vector<Line> &lines) {
    map<int, vector<Line>> rows;
    for (auto line: lines)
        if (line.dir == 'L' || line.dir == 'R')
            rows[line.y].push_back(line);
    
    for (auto [_, ranges]: rows) {
        vector<int> xs;
        for (auto [dir, idx, len, x, _]: ranges) {
            xs.push_back(x);
            xs.push_back(dir == 'L' ? x - len + 1 : x + len - 1);
        }

        sort(xs.begin(), xs.end());
        xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
        SegTree segtree(xs.size(), 1);

        for (auto [dir, idx, len, x, y]: ranges) {
            int l = dir == 'L' ? x - len + 1 : x;
            int r = dir == 'R' ? x + len - 1 : x;

            int sl = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
            int sr = lower_bound(xs.begin(), xs.end(), r) - xs.begin() + 1;

            if (dir == 'L') {
                optional<int> hit = segtree.find_rightmost(sl, sr, 0);
                if (hit) return {idx, xs[hit.value()], y};
            }
            if (dir == 'R') {
                optional<int> hit = segtree.find_leftmost(sl, sr, 0);
                if (hit) return {idx, xs[hit.value()], y};
            }

            segtree.update(sl, sr, 0);
        }
    }

    return {(int)1e9, 0, 0};
}

Intersection check_ver_overlap(const vector<Line> &lines) {
    vector<Line> rotated_lines = lines;
    for (auto &[dir, idx, len, x, y]: rotated_lines) {
        switch (dir) {
        case 'L': dir = 'U'; break;
        case 'R': dir = 'D'; break;
        case 'U': dir = 'L'; break;
        case 'D': dir = 'R'; break;
        }
        swap(x, y);
    }

    Intersection intersection = check_hor_overlap(rotated_lines);
    swap(intersection.x, intersection.y);
    return intersection;
}

Intersection check_hor_ver(const vector<Line> &lines) {
    vector<pair<int, int>> ys;
    vector<Event> events;

    auto min_int = [&](const Intersection &a, const Intersection &b) {
        if (a.line < b.line) return a;
        if (a.line > b.line) return b;

        switch (lines[a.line].dir) {
        case 'L': return a.x > b.x ? a : b;
        case 'R': return a.x < b.x ? a : b;
        case 'U': return a.y > b.y ? a : b;
        case 'D': return a.y < b.y ? a : b;
        }
    };

    for (auto &[dir, idx, len, x, y]: lines) {
        if (dir == 'L' || dir == 'R') {
            ys.emplace_back(y, idx);

            int l = dir == 'L' ? x - len + 1 : x;
            int r = dir == 'R' ? x + len - 1 : x;
            events.push_back({false, l,     y, +1, idx});
            events.push_back({false, r + 1, y, -1, idx});
        } else {
            int l = dir == 'U' ? y - len + 1 : y;
            int r = dir == 'D' ? y + len - 1 : y;
            events.push_back({true, x, l, r, idx});
        }
    }

    if (ys.empty()) return {(int)1e9, 0, 0};

    sort(ys.begin(), ys.end());
    ys.resize(unique(ys.begin(), ys.end()) - ys.begin());
    sort(events.begin(), events.end(), [&](const Event &a, const Event &b) {
        return tie(a.x, a.type) < tie(b.x, b.type);
    });

    SegTree segtree(ys.size(), 1e9);
    Intersection intersection = {(int)1e9, 0, 0};

    for (auto [type, x, l, r, idx]: events) {
        if (!type) {
            int pos = lower_bound(ys.begin(), ys.end(), make_pair(l, idx)) - ys.begin();
            segtree.update(pos, pos + 1, r == 1 ? idx : 1e9);
        } else {
            int sl = lower_bound(ys.begin(), ys.end(), make_pair(l, LLONG_MIN)) - ys.begin();
            int sr = upper_bound(ys.begin(), ys.end(), make_pair(r, LLONG_MAX)) - ys.begin();

            if (lines[idx].dir == 'U') {
                optional<int> hit = segtree.find_rightmost(sl, sr, idx);
                if (hit)  intersection = min_int(intersection, {idx, x, ys[hit.value()].first});
            } else {
                optional<int> hit = segtree.find_leftmost(sl, sr, idx);
                if (hit)  intersection = min_int(intersection, {idx, x, ys[hit.value()].first});
            }
        }
    }

    return intersection;
}

Intersection check_ver_hor(const vector<Line> &lines) {
    vector<Line> rotated_lines = lines;
    for (auto &[dir, idx, len, x, y]: rotated_lines) {
        switch (dir) {
        case 'L': dir = 'U'; break;
        case 'R': dir = 'D'; break;
        case 'U': dir = 'L'; break;
        case 'D': dir = 'R'; break;
        }
        swap(x, y);
    }

    Intersection intersection = check_hor_ver(rotated_lines);
    swap(intersection.x, intersection.y);
    return intersection;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<Line> lines(n);
    
    for (int i = 0; i < n; i++) {
        lines[i].idx = i;
        cin >> lines[i].dir >> lines[i].len;
    }

    int cx = 0, cy = 0;
    for (auto &[dir, idx, len, x, y]: lines) {
        x = cx, y = cy;

        switch (dir) {
        case 'L': cx -= len; break;
        case 'R': cx += len; break;
        case 'U': cy -= len; break;
        case 'D': cy += len; break;
        }
    }

    auto min_int = [&](const Intersection &a, const Intersection &b) {
        if (a.line == 1e9) return b;
        if (b.line == 1e9) return a;
        if (a.line < b.line) return a;
        if (a.line > b.line) return b;

        switch (lines[a.line].dir) {
        case 'L': return a.x > b.x ? a : b;
        case 'R': return a.x < b.x ? a : b;
        case 'U': return a.y > b.y ? a : b;
        case 'D': return a.y < b.y ? a : b;
        }
    };

    Intersection intersection = min_int(
        min_int(check_hor_overlap(lines), check_ver_overlap(lines)),
        min_int(check_hor_ver(lines), check_ver_hor(lines))
    );

    for (int i = 0; i < n - 1; i++) {
        if (
            (lines[i].dir == 'L' && lines[i + 1].dir == 'R') ||
            (lines[i].dir == 'R' && lines[i + 1].dir == 'L') ||
            (lines[i].dir == 'U' && lines[i + 1].dir == 'D') ||
            (lines[i].dir == 'D' && lines[i + 1].dir == 'U')
        ) {
            intersection = min_int(intersection, {i, lines[i + 1].x, lines[i + 1].y});
        }
    }

    auto [idx, x, y] = intersection;
    if (idx == 1e9) {
        int tot = 0;
        for (int i = 0; i < n; i++) tot += lines[i].len;
        cout << tot << '\n';
    } else {
        int tot = 0;
        for (int i = 0; i < idx; i++) tot += lines[i].len;
        cout << tot + abs(lines[idx].x - x) + abs(lines[idx].y - y) << '\n';
    }
}
