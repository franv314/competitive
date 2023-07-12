#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    int M, N; cin >> M >> N;
    int day = 0, spare = 0;

    for (int i = 0; i < N; i++) {
        //cout << day << " " << spare << endl;
        int E, L; cin >> E >> L;
        
        int today = spare / L;

        if (today >= E) {
            spare -= L * E;
            continue;
        }

        E -= today;
        day++;

        int episodes_per_day = M / L;
        //cout << "\t" << episodes_per_day << endl;
        day += (E + episodes_per_day - 1) / episodes_per_day - 1;
        int watched_last_day = E % episodes_per_day;
        if (watched_last_day == 0) watched_last_day = episodes_per_day;
        spare = M - (watched_last_day) * L;
    }
    cout << day << " " << spare;
}