#include <vector>

using namespace std;

int scarta(int M, vector<bool> L, vector<bool> D, vector<bool> N){
	int res = 0;
	for (int i = 0; i < M; i++)
	    res += (L[i] + D[i] + N[i]) != 1;
	return res;
}