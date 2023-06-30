#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<

struct Result {
    short a, b;

    void operator~() {
        if (a == 3) a = 1, b = 1;
        else if (a == 1) a = 0, b = 3;
        else if (a == 0) a = -1;
    }

    operator bool() {
        return a >= 0;
    }
};

struct RankingEntry {
    short team;
    short points;
    short matches;
};

bool operator<(RankingEntry a, RankingEntry b) {
    if (a.points != b.points) return a.points > b.points;
    return a.matches > b.matches;
}

// input data
int N, T;
int V;

unordered_map<long long, int> group[5];

string pad(string s) {
    string a = s;
    while (a.size() < 3)
        a = "0" + a;
    return a;
}

void setup_2() {
    unordered_map<long long, long long> results;

    Result res[2][2];
    for (res[0][1] = {3, 0}; res[0][1]; ~res[0][1]) {
    for (res[1][0] = {3, 0}; res[1][0]; ~res[1][0]) {
        array<RankingEntry, 2> ranking;
        for (int team = 0; team < 2; team++) {
            ranking[team] = {(short)team, 0, 0};
            for (int opp = 0; opp < 2; opp++) {
                if (team == opp) continue;
                ranking[team].points += res[team][opp].a + res[opp][team].b;
                ranking[team].matches += res[team][opp].a == 3 ? 100 : (res[team][opp].a == 1 ? 10 : 1);
                ranking[team].matches += res[opp][team].b == 3 ? 100 : (res[opp][team].b == 1 ? 10 : 1);
            }
        }
        sort(ranking.begin(), ranking.end());
        
        long long assign = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (i != j)
                    assign = (10 * assign) + (res[ranking[i].team][ranking[j].team].a == 3 ? i :
                        (res[ranking[i].team][ranking[j].team].a == 1 ? 9 : j));

        long long r = 0;
        for (int i = 0; i < 2; i++)
            r = (1000 * r) + ranking[i].matches;

        if (results[r] == 0) {
            results[r] = assign;
            group[2][r] = 1;
        } else if (results[r] != assign) {
            group[2][r] = 2;
        }
    }
    }
}

void setup_3() {
    unordered_map<long long, long long> results;

    Result res[3][3];
    for (res[0][1] = {3, 0}; res[0][1]; ~res[0][1]) {
    for (res[1][0] = {3, 0}; res[1][0]; ~res[1][0]) {
    for (res[0][2] = {3, 0}; res[0][2]; ~res[0][2]) {
    for (res[2][0] = {3, 0}; res[2][0]; ~res[2][0]) {
    for (res[1][2] = {3, 0}; res[1][2]; ~res[1][2]) {
    for (res[2][1] = {3, 0}; res[2][1]; ~res[2][1]) {
        array<RankingEntry, 3> ranking;
        for (int team = 0; team < 3; team++) {
            ranking[team] = {(short)team, 0, 0};
            for (int opp = 0; opp < 3; opp++) {
                if (team == opp) continue;
                ranking[team].points += res[team][opp].a + res[opp][team].b;
                ranking[team].matches += res[team][opp].a == 3 ? 100 : (res[team][opp].a == 1 ? 10 : 1);
                ranking[team].matches += res[opp][team].b == 3 ? 100 : (res[opp][team].b == 1 ? 10 : 1);
            }
        }
        sort(ranking.begin(), ranking.end());
        
        long long assign = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (i != j)
                    assign = (10 * assign) + (res[ranking[i].team][ranking[j].team].a == 3 ? i :
                        (res[ranking[i].team][ranking[j].team].a == 1 ? 9 : j));
        
        long long r = 0;
        for (int i = 0; i < 3; i++)
            r = (1000 * r) + ranking[i].matches;

        if (results[r] == 0) {
            results[r] = assign;
            group[3][r] = 1;
        } else if (results[r] != assign) {
            group[3][r] = 2;
        }
    }
    }
    }
    }
    }
    }
}

void setup_4() {
    unordered_map<long long, long long> results;

    Result res[4][4];
    for (res[0][1] = {3, 0}; res[0][1]; ~res[0][1]) {
    for (res[1][0] = {3, 0}; res[1][0]; ~res[1][0]) {
    for (res[0][2] = {3, 0}; res[0][2]; ~res[0][2]) {
    for (res[2][0] = {3, 0}; res[2][0]; ~res[2][0]) {
    for (res[0][3] = {3, 0}; res[0][3]; ~res[0][3]) {
    for (res[3][0] = {3, 0}; res[3][0]; ~res[3][0]) {
    for (res[1][2] = {3, 0}; res[1][2]; ~res[1][2]) {
    for (res[2][1] = {3, 0}; res[2][1]; ~res[2][1]) {
    for (res[1][3] = {3, 0}; res[1][3]; ~res[1][3]) {
    for (res[3][1] = {3, 0}; res[3][1]; ~res[3][1]) {
    for (res[2][3] = {3, 0}; res[2][3]; ~res[2][3]) {
    for (res[3][2] = {3, 0}; res[3][2]; ~res[3][2]) {
        array<RankingEntry, 4> ranking;
        for (int team = 0; team < 4; team++) {
            ranking[team] = {(short)team, 0, 0};
            for (int opp = 0; opp < 4; opp++) {
                if (team == opp) continue;
                ranking[team].points += res[team][opp].a + res[opp][team].b;
                ranking[team].matches += res[team][opp].a == 3 ? 100 : (res[team][opp].a == 1 ? 10 : 1);
                ranking[team].matches += res[opp][team].b == 3 ? 100 : (res[opp][team].b == 1 ? 10 : 1);
            }
        }
        sort(ranking.begin(), ranking.end());
        
        long long assign = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (i != j)
                    assign = (10 * assign) + (res[ranking[i].team][ranking[j].team].a == 3 ? i :
                        (res[ranking[i].team][ranking[j].team].a == 1 ? 9 : j));
        
        long long r = 0;
        for (int i = 0; i < 4; i++)
            r = (1000 * r) + ranking[i].matches;

        if (results[r] == 0) {
            results[r] = assign;
            group[4][r] = 1;
        } else if (results[r] != assign) {
            group[4][r] = 2;
        }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
}

int main() {
    setup_2();
    setup_3();
    setup_4();

    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        long long res = 0;
        for (int i = 0; i < N; i++) {
            cin >> V;
            res = (1000 * res) + V;
        }
        if (group[N][res] == 0) cout << "Invalid\n";
        else if (group[N][res] == 1) cout << "Unique\n";
        else cout << "Not unique\n";
    }

    return 0;
}