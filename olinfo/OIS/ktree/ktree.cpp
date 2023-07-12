#pragma GCC optimize("Ofast")
#include <unistd.h>
#include <fcntl.h>
#include <bits/stdc++.h>

using namespace std;

template<size_t BUFSIZE=1<<16>
class Scanner{
	private:
		char buf[BUFSIZE];
		char* it;
		char* ed;
		const int fd;
		Scanner(const Scanner&) = delete;
		Scanner& operator=(const Scanner&) = delete;
		void flush(){
			if(it==ed){
				ed=buf+read(fd,buf,BUFSIZE);
				it=buf;
			}
		}
		void ss(){
			flush();
			while(*it<=32){++it;flush();}
		}
		void scan(char& x){ss();x=*(it++);}
		void scan(string& x){
			do{
				ss();
				char * itbg=it;
				while(it!=ed&&*it>32)++it;
				x.append(itbg,it);
			} while(it==ed);
		}
		template<typename T> void scan_u(T& x){
			ss();
			x=0;
			do{
				x=T(x*10+*(it++)-'0');
				flush();
			} while(*it>32);
		}
		template<typename T> void scan_i(T& x){
			ss();
			x=0;
			bool sign=0;
			if(*it=='-'){
				sign=1;
				++it;
				flush();
			}
			do{
				x=T(x*10+*(it++)-'0');
				flush();
			} while(*it>32);
			if(sign)x=T(-x);
		}
		template<typename T> void scan_f(T& x){
			ss();
			x=0;
			bool sign=0;
			if(*it=='-'){
				sign=1;
				++it;
				flush();
			}
			while(*it>32 && *it!='.'){
				x=x*T(10.0)+T(*(it++)-'0');
				flush();
			}
			if(*it=='.'){
				++it;
				flush();
				T e=T(0.1);
				while(*it>32){
					x=x+e*T(*(it++)-'0');
					e=e*T(0.1);
					flush();
				};
			}
			if(sign)x=-x;
		}
		void scan(int8_t& x){scan_i(x);}
		void scan(int16_t& x){scan_i(x);}
		void scan(int32_t& x){scan_i(x);}
		void scan(int64_t& x){scan_i(x);}
		void scan(long long& x){scan_i(x);}
		void scan(uint8_t& x){scan_u(x);}
		void scan(uint16_t& x){scan_u(x);}
		void scan(uint32_t& x){scan_u(x);}
		void scan(uint64_t& x){scan_u(x);}
		void scan(unsigned long long& x){scan_u(x);}
		void scan(float& x){double d; scan_f(d); x=d;}
		void scan(double& x){scan_f(x);}
		void scan(long double& x){scan_f(x);}

		template<typename T> void scan(T& x){for(auto &i:x)scan(i);}
	public:
		~Scanner(){}
		Scanner(const int _fd=0):it(0),ed(0),fd(_fd){}
		void operator()(){}
		template<typename T, typename...R>
			void operator()(T& a,R&...rest){
				scan(a);
				operator()(rest...);
			}
};

template<size_t BUFSIZE=1<<16>
class Printer {
	private:
		char buf[BUFSIZE];
		char* it;
		const int fd;
		void fif(const size_t x){
			if(size_t(BUFSIZE+buf-it)<x)flush();
		}
		void print(const char x){fif(1);*(it++)=x;}
		void print(char* const x){
			size_t s = strlen(x);
			if(s>BUFSIZE/2){
				flush();
				write(fd,x,s);
			} else {
				fif(s);
				copy(x,x+s,it);
				it+=s;
			}
		}
		void print(const char* const x){print((char*)x);}
		void print(const string& x){
			if(x.size()>BUFSIZE/2){
				flush();
				write(fd,x.data(),x.size());
			} else {
				fif(x.size());
				copy(x.begin(),x.end(),it);
				it+=x.size();
			}
		}
		template<typename T> void print_u(T x){
			constexpr size_t siz = size_t(sizeof(T) * log10(256)) + 1;
			uint8_t i=siz;
			char b[siz];
			do {
				b[--i]=char(x%10+'0');
				x=T(x/10);
			}while(x);
			fif(siz-i);
			copy(b+i,b+siz,it);
			it+=siz-i;
		}
		template<typename T> void print_i(T x){
			constexpr size_t siz = size_t(sizeof(T) * 2.4082399653118496) + 2;
			size_t i=siz;
			char b[siz];
			const bool neg=(x<0);
			if(neg)x=-x;
			do {
				b[--i]=char(x%10+'0');
				x=T(x/10);
			}while(x);
			if(neg)b[--i]='-';
			fif(siz-i);
			copy(b+i,b+siz,it);
			it+=siz-i;
		}
		void print_f(const double x){
			const uint64_t d = *((uint64_t*)&x);
			const bool neg = d>>63;
			int32_t e = (d>>52)&((1ull<<11)-1);
			uint64_t m = d&((1ull<<52)-1);
			if(e){
				e-=1075;
				m+=(1ull<<52);
			} else e=-1074ll;
			int32_t re=e;
			if(e<0){
				while(e++){
					if(m&0xe000000000000000){
						m>>=1;
						re++;
					} else m*=5;
				}
			} else {
				while(e--){
					if(m&0x8000000000000000) m/=5;
					else {
						m<<=1;
						re--;
					}
				}
			}
			if(neg)print('-');
			print(m);
			print('e');
			print(re);
		}
		void print(int8_t x){print_i(x);}
		void print(int16_t x){print_i(x);}
		void print(int32_t x){print_i(x);}
		void print(int64_t x){print_i(x);}
		void print(long long x){print_i(x);}
		void print(uint8_t x){print_u(x);}
		void print(uint16_t x){print_u(x);}
		void print(uint32_t x){print_u(x);}
		void print(uint64_t x){print_u(x);}
		void print(unsigned long long x){print_u(x);}
		void print(const float x){print_f(x);}
		void print(const double x){print_f(x);}
		void print(const long double x){print_f(x);}

		template<typename T> void print(const T& x){
			for(auto &i:x){
				print(i);
				print(' ');
			}
		}
	public:
		~Printer(){flush();}
		Printer(const int _fd=1):it(buf),fd(_fd){}
		void flush(){
			write(fd,buf,it-buf);
			it=buf;
		}
		void operator()(){}
		template<typename T, typename...R>
			void operator()(T&& a,R&&...rest){
				print(a);
				operator()(rest...);
			}
};

#define MAXN 250'001

int V[MAXN];
vector<int> children[MAXN];

int path[MAXN];
int path_size;
int lift[MAXN][20];
int lift_size[MAXN];
int depth[MAXN];

struct Node {
    int sum;
    int nb, ne;
    Node *lc, *rc;

    Node() { }
    Node(int nb, int ne, Node *lc, Node *rc, int sum = 0) :
        sum(sum), nb(nb), ne(ne), lc(lc), rc(rc) { }
};

Node pool[6'000'000];
int no;

Node* get(int nb, int ne, Node *lc, Node *rc, int sum = 0) {
    pool[no] = Node(nb, ne, lc, rc, sum);
    return &pool[no++];
}

struct SegTree {
    Node *roots[MAXN];

    Node* build(int nb, int ne) {
        if (nb + 1 == ne) return get(nb, ne, NULL, NULL);
        Node *lc = build(nb, (nb + ne) / 2);
        Node *rc = build((nb + ne) / 2, ne);
        return get(nb, ne, lc, rc);
    }

    Node* add(int x, Node *node) {
        if (node->nb > x || node->ne <= x) return node;
        if (node->nb + 1 == node->ne) {
            return get(node->nb, node->ne, NULL, NULL, node->sum + 1);
        }
        Node *lc = add(x, node->lc);
        Node *rc = add(x, node->rc);
        return get(node->nb, node->ne, lc, rc, lc->sum + rc->sum);
    }

    int query(int l, int r, Node *node) {
        if (node->nb >= r || node->ne <= l) return 0;
        if (l <= node->nb && node->ne <= r) return node->sum;
        return query(l, r, node->lc) + query(l, r, node->rc);
    }

public:

    void add_node(int node, int val) {
        roots[node] = add(val, roots[lift[node][0]]);
    }

    int query_path(int node, int ma) {
        return query(ma + 1, MAXN, roots[node]);
    }

    SegTree() {
        roots[0] = build(0, MAXN);
    }
} segtree;

void dfs(int node) {
    depth[node] = path_size;
    path[path_size++] = node;
    int h = 0;
    for (int i = 1; i < path_size; i <<= 1, h++) {
        lift[node][h] = path[path_size - 1 - i];
    }
    lift_size[node] = h;

    segtree.add_node(node, V[node]);

    for (auto child: children[node]) {
        dfs(child);
    }

    path_size--;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    for (int i = lift_size[v] - 1; i >= 0; i--) {
        if (lift_size[v] > i && depth[lift[v][i]] >= depth[u]) {
            v = lift[v][i];
        }
    }
    
    if (u == v) return u;

    for (int i = lift_size[u] - 1; i >= 0; i--) {
        if (lift_size[u] > i && lift[u][i] != lift[v][i]) {
            u = lift[u][i];
            v = lift[v][i];
        }
    }
    return lift[u][0];
}

Scanner<> scan;
Printer<> prnt;

int main() {
    int N; scan(N);
    for (int i = 1; i <= N; i++) {
        scan(V[i]);
    }

    for (int i = 2; i <= N; i++) {
        int P; scan(P);
        children[P].push_back(i);
    }

    depth[0] = -1;
    lift[1][0] = 0;
    lift_size[1] = 1;
    dfs(1);

    int Q; scan(Q);
    while (Q--) {
        int u, v, k; scan(u, v, k);
        int l = lca(u, v);

        int L = 0, R = N + 1;
        while (L + 1 < R) {
            int M = (L + R) / 2;

            int count
                = segtree.query_path(u, M)
                + segtree.query_path(v, M)
                - 2 * segtree.query_path(l, M);

            if (V[l] > M) count++;

            if (count >= k) L = M;
            else R = M;
        }
        prnt(R, '\n');
    }
}