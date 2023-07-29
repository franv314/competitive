#include <bits/stdc++.h>
using namespace std;

#define MAXN 1'000'000

struct Fenwick {
    vector<int> arr;
    
    void remove(int x) {
        for (; x < arr.size(); x += x & -x)
            arr[x]--;
    }
    
    int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x)
            ans += arr[x];
        return ans;
    }
    
    int binsearch(int x) {
        int curr = 0;
        for (int b = 1 << 19; b; b >>= 1) {
            if (curr + b >= arr.size() || arr[curr + b] > x) continue;
            
            curr += b;
            x -= arr[curr];
        }
        return curr;
    }
    
    Fenwick() { }
    Fenwick(int size) : arr(size + 1) {
        for (int i = 1; i <= size; i++)
            arr[i] = i & -i;
    }  
};

Fenwick fenwick;
int all_pos[MAXN];
int ranking[MAXN + 1];

void inizia(int N, int ids[]) {
    copy(ids, ids + N, ranking + 1);
    fenwick = Fenwick(N);
	
	for (int i = 0; i < N; i++) {
	   all_pos[ids[i]] = i + 1;
	}
}

void supera(int id) {
    int pos = all_pos[id];
    int pos_prev = fenwick.binsearch(fenwick.query(pos) - 2) + 1;
    int over_id = ranking[pos_prev];
    
    swap(ranking[pos], ranking[pos_prev]);
    swap(all_pos[id], all_pos[over_id]);
}

void squalifica(int id) {
	fenwick.remove(all_pos[id]);
}

int partecipante(int pos) {
	return ranking[fenwick.binsearch(pos - 1) + 1];
}