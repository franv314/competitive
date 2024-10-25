#include <bits/stdc++.h>
#include "message.h"
using namespace std;

constexpr int MAXS = 1024;
constexpr int SIZE = 31;
constexpr int PACKETS = 66;
constexpr int GOOD_BITS = 16;

void send_message(vector<bool> M, vector<bool> C) {
    M.push_back(1);
    while (M.size() <= MAXS)
        M.push_back(0);
    
    vector<int> nxt(SIZE);
    for (int i = 0; i < SIZE; i++) {
        while (C[(i + nxt[i] + 1) % SIZE])
            nxt[i]++;
    }

    int idx = 0;
    for (int i = 0; i < PACKETS; i++) {
        vector<bool> packet(SIZE);
        for (int j = 0; j < SIZE; j++) {
            if (C[j])
                continue;
            
            if (i < nxt[j])
                packet[j] = 1;
            else if (i == nxt[j])
                packet[j] = 0;
            else
                packet[j] = M[idx++];
        }

        send_packet(packet);
    }
}

vector<bool> receive_message(vector<vector<bool>> R) {
    vector<int> nxt(SIZE), true_nxt(SIZE);
    for (int i = 0; i < SIZE; i++) {
        while (nxt[i] < GOOD_BITS - 1 && R[nxt[i]][i])
            nxt[i]++;
        true_nxt[i] = (i + nxt[i] + 1) % SIZE;
    }

    vector<int> good_bits;

    for (int i = 0; i < SIZE; i++) {
        vector<bool> vis(SIZE);
        deque<int> cycle;
        
        int curr;
        for (curr = i; !vis[curr]; curr = true_nxt[curr]) {
            vis[curr] = true;
            cycle.push_back(curr);
        }

        while (cycle.front() != curr)
            cycle.pop_front();
        
        if (cycle.size() == GOOD_BITS)
            good_bits = vector(cycle.begin(), cycle.end());
    }

    sort(good_bits.begin(), good_bits.end());
    
    vector<bool> message;
    for (int i = 0; i < PACKETS; i++)
        for (auto j: good_bits)
            if (i > nxt[j])
                message.push_back(R[i][j]);
    
    while (!message.back())
        message.pop_back();
    message.pop_back();
    return message;
}
