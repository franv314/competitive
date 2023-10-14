#include <bits/stdc++.h>
using namespace std;

bool radar(int i, int a, int b, int c);

constexpr int CUT = 150;

bool maps(vector<int> v, vector<bool> f, bool val) {
    for (int x: v) {
        if (f[x] == val) return true;
    }
    return false;
}

void intersect(vector<vector<int>> &parts, vector<bool> incl) {
    assert(parts.size() >= 3);
    for (int i = 0; i < parts.size(); i++) {
        int i1 = (i+1)%parts.size(), i2 = (i+2)%parts.size();
        if (
            maps(parts[i], incl, 0) &&
            maps(parts[i1], incl, 0) &&
            maps(parts[i1], incl, 1) &&
            maps(parts[i2], incl, 1)
        ) {
            parts.insert(parts.begin()+i2, vector<int>());
            if (i2 < i1) i1++;
            int insI = 0;
            for (int x: parts[i1]) {
                if (incl[x]) parts[i2].push_back(x);
                else parts[i1][insI++] = x;
            }
            parts[i1].resize(insI);
            break;
        }
    }
    for (int i = 0; i < parts.size(); i++) {
        int i1 = (i+1)%parts.size(), i2 = (i+2)%parts.size();
        if (
            maps(parts[i], incl, 1) &&
            maps(parts[i1], incl, 1) &&
            maps(parts[i1], incl, 0) &&
            maps(parts[i2], incl, 0)
        ) {
            parts.insert(parts.begin()+i2, vector<int>());
            if (i2 < i1) i1++;
            int insI = 0;
            for (int x: parts[i1]) {
                if (incl[x]) parts[i1][insI++] = x;
                else parts[i2].push_back(x);
            }
            parts[i1].resize(insI);
            break;
        }
    }
}

vector<int> activate(int N) {
    vector<int> hull, notHull;
    // sol in O(n^(5/3))
    for (int i = 0; i < min(CUT, N); i++) {
        vector<int> new_hull;
        vector<bool> contained(hull.size(), true);
        for (int yh = 1; yh < hull.size(); yh++) {
            for (int zh = 1; zh < yh; zh++) {
                if (radar(i, hull[0], hull[yh], hull[zh])) {
                    notHull.push_back(i);
                    goto no;
                }
            }
        }
        new_hull.push_back(i);
        for (int ih = 0; ih < hull.size(); ih++) {
            for (int yh = 0; yh < hull.size(); yh++) {
                for (int zh = 0; zh < yh; zh++) {
                    if (ih != yh && ih != zh && contained[yh] && contained[zh] && radar(hull[ih], i, hull[yh], hull[zh])) {
                        contained[ih] = false;
                        notHull.push_back(hull[ih]);
                        goto done;
                    }                    
                }
            }
done:
            if (contained[ih]) {
                new_hull.push_back(hull[ih]);
            }
        }
        hull = new_hull;
no:     ;
    }
    if (N <= CUT) {
        return hull;
    }
    // ordinamento polare del convex hull
    vector<vector<int>> parts(2);
    int innerI = 0;
    for ( ; ; innerI++) {
        // 0, 1 -> rand(), rand()
        for (int ha = 0; ha < hull.size(); ha++) {
            for (int hb = 0; hb < ha; hb++) {
                parts[0].push_back(ha);
                parts[0].push_back(hb);
                for (int hi = 0; hi < hull.size(); hi++) {
                    if (hi == ha || hi == hb) continue;
                    parts[radar(notHull[innerI], hull[ha], hull[hb], hull[hi])].push_back(hi);
                }
                // Una divisione più equa dovrebbe essere favorevole nello step successivo
                if (parts[0].size() >= hull.size()/4 && parts[1].size() >= hull.size()/4) goto endSearch1;
                parts[0].clear();
                parts[1].clear();
            }
        }
    }
endSearch1:
    vector<bool> incl(hull.size());
    for (innerI++ ; ; innerI++) {
        for (int ha = 0; ha < hull.size(); ha++) {
            for (int hb = 0; hb < ha; hb++) {
                incl[ha] = false;
                incl[hb] = false;
                for (int hi = 0; hi < hull.size(); hi++) {
                    if (hi == ha || hi == hb) continue;
                    incl[hi] = radar(notHull[innerI], hull[ha], hull[hb], hull[hi]);
                }
                if (
                    maps(parts[0], incl, 0) &&
                    maps(parts[0], incl, 1) &&
                    maps(parts[1], incl, 0) &&
                    maps(parts[1], incl, 1)
                ) {
                    int pi = 0;
                    parts.push_back({});
                    for (int x: parts[0]) {
                        if (incl[x]) parts[2].push_back(x);
                        else parts[0][pi++] = x;
                    }
                    parts[0].resize(pi);
                    goto endSearch2;
                }
            }
        }
    }
endSearch2:
    while (parts.size() != hull.size()) {
        int a = rand()%min(N, CUT), b = rand()%min(N, CUT), pv = notHull[rand()%notHull.size()];
        if (a == b || a == pv || b == pv) continue;
        for (int hi = 0; hi < hull.size(); hi++) {
            if (hull[hi] == a || hull[hi] == b) incl[hi] = false;
            else incl[hi] = radar(pv, a, b, hull[hi]);
        }
        intersect(parts, incl);
    }
    {
        vector<int> hullCopy(hull.begin(), hull.end());
        for (int i = 0; i < hull.size(); i++) {
            hull[i] = hullCopy[parts[i][0]];
        }
    }
    auto nxt = [&](int i) {
        return (i+1)%hull.size();
    };
    // soluzione in O(N^(4/3)) (hull è sempre sortato)
    for (int i = CUT; i < N; i++) {
        // qua per evitare cross-initialization
        int insertIndex = -1;
        int cnt;
        queue<array<int, 2>> triangles; // incluso-incluso
        // triangolazione efficiente
        cnt = 1;
        if (radar(i, hull[0], hull[hull.size()/3], hull[hull.size()*2/3])) {
            goto no2;
        }
        triangles.push({0, (int)hull.size()/3});
        triangles.push({(int)hull.size()/3, (int)hull.size()*2/3});
        triangles.push({(int)hull.size()*2/3, (int)hull.size()});
        while (triangles.size()) {
            cnt++;
            auto [cl, cr] = triangles.front();
            triangles.pop();
            int cm = (cl+cr)/2;
            if (radar(i, hull[cl], hull[cm], hull[cr == hull.size() ? 0 : cr])) {
                goto no2;
            }
            if (cl+2 <= cm) triangles.push({cl, cm});
            if (cm+2 <= cr) triangles.push({cm, cr});
        }
        assert(cnt==hull.size()-2);
        // Inserisci nel convex hull
        for (int hi = 0; hi < hull.size(); ) {
            if (radar(hull[hi], i, hull[nxt(hi)], hull[(hi+hull.size()-1+hull.size())%hull.size()])) {
                if (insertIndex == -1) {
                    insertIndex = hi;
                }
                hull.erase(hull.begin() + hi);
            } else {
                hi++;
            }
        }
        if (insertIndex != -1) {
            hull.insert(hull.begin()+insertIndex, i);
        } else {
            // if the pair <i, i+1> could be the insertion point
            vector<char> valid(hull.size(), true);
            for (int pv: notHull) {
                int hopp = -1;
                for (int hi = 0; hi < N; hi++) {
                    if (radar(pv, i, hull[hi], hull[nxt(hi)])) {
                        hopp = hi;
                        break;
                    }
                }
                assert(hopp >= 0);
                valid[hopp] = false;
                int validCnt = 0, validI;
                for (int hi = 0; hi < hull.size(); hi++) {
                    if (hi == hopp) continue;
                    // l'operator short-circuiting salva un buon numero di query
                    if (nxt(hi) == hopp) {
                        valid[hi] = valid[hi] && radar(pv, hull[hi], hull[hopp], hull[nxt(hopp)]);
                    } else if (hi == nxt(hopp)) {
                        valid[hi] = valid[hi] && radar(pv, hull[hopp], hull[hi], hull[nxt(hi)]);
                    } else {
                        valid[hi] = valid[hi] && (
                            radar(pv, hull[hopp], hull[hi], hull[nxt(hi)]) ||
                            radar(pv, hull[hopp], hull[nxt(hopp)], hull[hi])
                        );
                    }
                    if (valid[hi]) {
                        validCnt++;
                        validI = hi;
                    }
                }
                assert(validCnt);
                if (validCnt == 1) {
                    hull.insert(hull.begin()+validI+1, i);
                    goto no2;
                }
            }
            assert(false);
        }
no2:     ;
    }
    return hull;
}
