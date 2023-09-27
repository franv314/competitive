//Benq->Brionix->Bamber->Me

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vpi = V<pair<int,int>>;
#define sz(x) int((x).size())
#define pb push_back
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define each(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
template<class T> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0; } // set $a = \min(a,b)$
template<class T> bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0; } // set a = max(a,b)
template<int SZ> struct WeightedMatch { //Time: $\mathcal{O}(N^3)$?
  struct edge { int u,v;long long w; }; edge g[SZ*2][SZ*2];
  void ae(int u, int v, long long w){g[u][v].w=g[v][u].w=w;}
  int N,NX,match[SZ*2],slack[SZ*2],st[SZ*2];
  long long lab[SZ*2]; //per sicurezza sovrastima SZ
  int par[SZ*2],floFrom[SZ*2][SZ],S[SZ*2],aux[SZ*2]; 
  vi flo[SZ*2]; queue<int> q; 
  void init(int _N) { N = _N; // init all edges
    FOR(u,1,N+1) FOR(v,1,N+1) g[u][v] = {u,v,0}; }
  long long eDelta(edge e) { // >= 0 at all times
    return lab[e.u]+lab[e.v]-g[e.u][e.v].w*2; } 
  void updSlack(int u, int x) { //smallest edge -> blossom x
    if (!slack[x] || eDelta(g[u][x])<eDelta(g[slack[x]][x]))
      slack[x] = u; }
  void setSlack(int x) {
    slack[x] = 0; FOR(u,1,N+1) if (g[u][x].w > 0
     && st[u] != x && S[st[u]] == 0) updSlack(u,x); }
  void qPush(int x) {
    if (x <= N) q.push(x);
    else each(t,flo[x]) qPush(t); }
  void setSt(int x, int b) {
    st[x] = b; if (x > N) each(t,flo[x]) setSt(t,b); }
  int getPr(int b, int xr) { // get even position of xr
    int pr = find(all(flo[b]),xr)-begin(flo[b]);
    if(pr&1){reverse(1+all(flo[b])); return sz(flo[b])-pr;} 
    return pr; }
  void setMatch(int u, int v) { // rearrange flo[u], matches
    edge e = g[u][v]; match[u] = e.v; if (u <= N) return;
    int xr = floFrom[u][e.u], pr = getPr(u,xr);
    F0R(i,pr) setMatch(flo[u][i],flo[u][i^1]);
    setMatch(xr,v); rotate(begin(flo[u]),pr+all(flo[u])); }
  void augment(int u, int v) { // set matches including u->v
    while (1) { // and previous ones
      int xnv = st[match[u]]; setMatch(u,v); 
      if (!xnv) return; 
      setMatch(xnv,st[par[xnv]]); 
      u = st[par[xnv]], v = xnv; 
    }
  }
  int lca(int u, int v) { // same as in unweighted
    static int t = 0; // except maybe return 0
    for (++t;u||v;swap(u,v)) {
      if (!u) continue;
      if (aux[u] == t) return u;
      aux[u] = t; u = st[match[u]];
      if (u) u = st[par[u]];
    }
    return 0;
  }
  void addBlossom(int u, int anc, int v) { 
    int b = N+1; while (b <= NX && st[b]) ++b;
    if (b > NX) ++NX; // new blossom
    lab[b] = S[b] = 0; match[b] = match[anc]; flo[b] ={anc};
    auto blossom = [&](int x) {
      for (int y; x != anc; x = st[par[y]]) 
        flo[b].pb(x), flo[b].pb(y = st[match[x]]), qPush(y);
    };
    blossom(u);reverse(1+all(flo[b]));blossom(v);setSt(b,b);
    // identify all nodes in current blossom
    FOR(x,1,NX+1) g[b][x].w = g[x][b].w = 0;
    FOR(x,1,N+1) floFrom[b][x] = 0;
    each(xs,flo[b]) { // find tightest constraints
      FOR(x,1,NX+1) if (g[b][x].w == 0 || eDelta(g[xs][x])< 
        eDelta(g[b][x])) g[b][x]=g[xs][x], g[x][b]=g[x][xs];
      FOR(x,1,N+1) if (floFrom[xs][x]) floFrom[b][x] = xs;
    } // floFrom to deconstruct blossom
    setSlack(b); // since didn't qPush everything
  }
  void expandBlossom(int b) {
    each(t,flo[b]) setSt(t,t); // undo setSt(b,b)
    int xr = floFrom[b][g[b][par[b]].u], pr = getPr(b,xr);
    for(int i = 0; i < pr; i += 2) {
      int xs = flo[b][i], xns = flo[b][i+1];
      par[xs] = g[xns][xs].u; S[xs] = 1; //no setSlack(xns)?
      S[xns] = slack[xs] = slack[xns] = 0; qPush(xns);
    }
    S[xr] = 1, par[xr] = par[b];
    FOR(i,pr+1,sz(flo[b])) { // matches don't change
      int xs = flo[b][i]; S[xs] = -1, setSlack(xs); }
    st[b] = 0; // blossom killed
  }
  bool onFoundEdge(edge e) {
    int u = st[e.u], v = st[e.v];
    if (S[v] == -1) { // v unvisited, matched with smth else
      par[v] = e.u, S[v] = 1; slack[v] = 0;
      int nu = st[match[v]]; S[nu] = slack[nu]=0; qPush(nu);
    } else if (S[v] == 0) {
      int anc = lca(u,v); // if 0 then match found!
      if (!anc) return augment(u,v),augment(v,u),1;
      addBlossom(u,anc,v);
    }
    return 0;
  }
  bool matching() {
    q = queue<int>(); 
    FOR(x,1,NX+1) {
      S[x] = -1, slack[x] = 0; // all initially unvisited
      if (st[x] == x && !match[x]) par[x]=S[x]=0, qPush(x); 
    } 
    if (!sz(q)) return 0;
    while (1) {
      while (sz(q)) { //unweighted matching with tight edges
        int u = q.front(); q.pop(); if(S[st[u]]==1)continue;
        FOR(v,1,N+1) if (g[u][v].w > 0 && st[u] != st[v]) { 
          if (eDelta(g[u][v]) == 0) { //condition is strict
            if (onFoundEdge(g[u][v])) return 1;
          } else updSlack(u,st[v]);
        }
      }
      long long d = LLONG_MAX; 
      FOR(b,N+1,NX+1) if (st[b] == b && S[b] == 1) 
        ckmin(d,lab[b]/2); // decrease lab[b]
      FOR(x,1,NX+1) if (st[x] == x && slack[x]) {
        if (S[x] == -1) ckmin(d,eDelta(g[slack[x]][x]));
        else if(S[x]==0)ckmin(d,eDelta(g[slack[x]][x])/2);
      } // edge weights shouldn't go below 0
      FOR(u,1,N+1) {
        if (S[st[u]] == 0) {
          if (lab[u] <= d) return 0; // why?
          lab[u] -= d;
        } else if (S[st[u]] == 1) lab[u] += d;
      } // lab has opposite meaning for verts and blossoms
      FOR(b,N+1,NX+1) if (st[b] == b && S[b] != -1) 
        lab[b] += (S[b] == 0 ? 1 : -1)*d*2;
      q = queue<int>();
      FOR(x,1,NX+1)if(st[x]==x && slack[x]//new tight edge
        && st[slack[x]] != x && eDelta(g[slack[x]][x])==0)
          if (onFoundEdge(g[slack[x]][x])) return 1;
      FOR(b,N+1,NX+1) if (st[b]==b && S[b]==1 && lab[b]==0) 
        expandBlossom(b); // odd dist blossom taken apart
    }
    return 0;
  }
  pair<ll,int> calc() {
    NX = N; st[0] = 0; FOR(i,1,2*N+1) aux[i] = 0;
    FOR(i,1,N+1) match[i] = 0, st[i] = i, flo[i].clear();
    long long wMax = 0;
    FOR(u,1,N+1) FOR(v,1,N+1)
      floFrom[u][v]=(u==v ? u : 0),ckmax(wMax,g[u][v].w);
    FOR(u,1,N+1) lab[u] = wMax; //start high and decrease
    int num = 0; ll wei = 0; while (matching()) ++num;
    FOR(u,1,N+1) if (match[u] && match[u] < u) 
      wei += g[u][match[u]].w; // edges in matching
    return {wei,num};
  }
};

WeightedMatch<500> wm;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    int K; cin >> K;
    vector<int> C(K);
    for (auto &c: C) cin >> c;
    C.push_back(0);
    C.push_back(N - 1);

    vector<vector<long long>> mat(N, vector<long long>(N, 1e18));
    for (int i = 0; i < N; i++)
        mat[i][i] = 0;

    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        mat[u][v] = mat[v][u] = w;
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }

    wm.init(N);

    for (int i = 0; i < C.size(); i++) {
        for (int j = i + 1; j < C.size(); j++) {
            wm.ae(C[i] + 1, C[j] + 1, mat[C[i]][C[j]]);
        }
    }

    cout << wm.calc().first << '\n';
}