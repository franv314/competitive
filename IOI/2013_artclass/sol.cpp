#include <bits/stdc++.h>
#include "artclass.h"
using namespace std;

int diff(array<int, 3> a, array<int, 3> b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]);
}

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]) {
    
    array<int, 3> img[500][500];
    for (int i = 0; i < H; i++)
        for (int j = 0; j < H; j++)
            img[i][j] = { R[i][j], G[i][j], B[i][j] };

    double difference = 0.;
    for (int i = 1; i < H - 1; i++) {
        for (int j = 1; j < W - 1; j++) {
            difference += diff(img[i][j], img[i - 1][j - 1])
                        + diff(img[i][j], img[i - 1][j    ])
                        + diff(img[i][j], img[i - 1][j + 1])
                        + diff(img[i][j], img[i    ][j + 1])
                        + diff(img[i][j], img[i + 1][j + 1])
                        + diff(img[i][j], img[i + 1][j    ])
                        + diff(img[i][j], img[i + 1][j - 1])
                        + diff(img[i][j], img[i    ][j - 1]);
        }
    }
    
    difference /= (H * W);

    if (difference <= 85) return 4;
    if (difference >= 400) return 3;
    
    double brightness = 0.;

    for (int i = 0; i < H; i++)
        for (int j = 0; j < H; j++)
            brightness += R[i][j] + G[i][j] + B[i][j];
    
    brightness /= (H * W);

    //cout << brightness << endl;
    if (brightness >= 330) return 1;
    return 2;
}