#include <bits/stdc++.h>
 
#define k std::
#define M [8<<15]
#define u int64_t
#define j ;for (u _ = 1; _ <= n; _++)
#define b(x) ;for (u c: a[e]) if (!x[c])
 
k set<u> a M;
 
u r,w M,n,s M,x,y;
 
void d(u e, u h) {
    r += h;
    s[e]=1
 
    b(s) d(c, h + 1), s[e] += s[c];
}
 
void f(u e, u l) {
    w[e]=l
 
    b(w) f(c, l + n - 2 * s[c]);
}
 
main() {
    k cin >> n
    j k cin >> x >> y,a[x].insert(y),a[y].insert(x);
 
    d(1, 0);
 
    f(1, r)
 
    j k cout << w[_] << " ";
}