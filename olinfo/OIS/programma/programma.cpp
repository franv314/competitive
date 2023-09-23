#include <bits/stdc++.h>
using namespace std;

struct Move {
    int x, y, rot;

    Move operator+(const Move &other) const {
        switch (rot) {
        case 0: return {x + other.x, y + other.y, (rot + other.rot) % 4};
        case 1: return {x - other.y, y + other.x, (rot + other.rot) % 4};
        case 2: return {x - other.x, y - other.y, (rot + other.rot) % 4};
        case 3: return {x + other.y, y - other.x, (rot + other.rot) % 4};
        }
    }

    Move operator-() const {
        switch (rot) {
        case 0: return {-x, -y, 0};
        case 1: return {-y, +x, 3};
        case 2: return {+x, +y, 2};
        case 3: return {+y, -x, 1};
        }
    }

    bool operator==(const Move &other) const {
        return x == other.x && y == other.y && rot == other.rot;
    }

    constexpr Move(int x, int y, int d) : x(x), y(y), rot(d) { }
    constexpr Move() : Move(0, 0, 0) { }
};

constexpr Move R( 0, 0, 3);
constexpr Move L( 0, 0, 1);
constexpr Move F( 1, 0, 0);
constexpr Move B(-1, 0, 0);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N, M; in >> N >> M;
    string S; in >> S;

    vector<Move> prefix(N + 1);
    set<int> explosions;
    explosions.insert(1e9);

    for (int i = 0; i < N; i++) {
        switch (S[i]) {
        case 'R': prefix[i + 1] = prefix[i] + R; break;
        case 'L': prefix[i + 1] = prefix[i] + L; break;
        case 'F': prefix[i + 1] = prefix[i] + F; break;
        case 'B': prefix[i + 1] = prefix[i] + B; break;
        case 'X': prefix[i + 1] = prefix[i]; explosions.insert(i); break;
        }
    }

    Move status;

    while (M--) {
        int S, E; in >> S >> E;
        int X = *explosions.lower_bound(S);
        
        if (X <= E) {
            status = status + (-prefix[S] + prefix[X]);
            break;
        } else {
            status = status + (-prefix[S] + prefix[E + 1]);
        }
    }

    out << status.x << " " << status.y;
}