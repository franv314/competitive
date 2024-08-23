#include <bits/stdc++.h>
using namespace std;

pair<int, int> play(int x, int y) {
    cout << x << " " << y << endl;
    int new_x, new_y; cin >> new_x >> new_y;
    return {new_x, new_y};
}

int main() {
    int N; cin >> N;
    int block = 100 * N;

    int x = 0, y = 0;
    set<float> free;
    for (int i = 0; i <= block; i += N)
        free.insert(i);

    int pass = 0;
    int waste = 0;

    do {
        if (pass < N) {
            float pos = (block + x - y) / 2.;
            auto nxt = free.lower_bound(pos);
            auto prv = nxt == free.begin() ? free.end() : prev(nxt);

            set<float>::iterator nx;
            if (nxt == free.end())
                nx = prv;
            else if (prv == free.end())
                nx = nxt;
            else if (*nxt - pos <= pos - *prv)
                nx = nxt;
            else
                nx = prv;
            
            if (*nx < x || block - *nx < y) {
                pass++;
                free.clear();
                for (int i = 0; i <= block; i++)
                    if (i % N == pass)
                        free.insert(i);
                
                cerr << "Ok " << x + y << " " << block << endl;
                continue;
            }

            tie(x, y) = play(*nx, block - *nx);
            free.erase(nx);
        } else {
            tie(x, y) = play(block + 1, waste++);
        }
    } while (x != -1 || y != -1);
}
