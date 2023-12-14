#include <utility>
#include <vector>
#include "robot.h"
using namespace std;
    
#define NORTH 3
#define EAST 4
#define SOUTH 5
#define WEST 6
    
pair<int, char> instr(int C, int N, int E, int S, int W) {
    if (C == 0 && N == -2 && W == -2) return {NORTH, 'H'};
    
    if (C == NORTH || C == EAST || C == SOUTH || C == WEST) {
        if (N == 0 || N == SOUTH) return {1, 'N'};
        if (E == 0 || E == WEST) return {1, 'E'};
        if (S == 0 || S == NORTH) return {1, 'S'};
        if (W == 0 || W == EAST) return {1, 'W'};
    }
    
    if (S == -2 && E == -2) return {1, 'T'};
    
    if (C == 1) {
        if (N == 0 || N == SOUTH) return {1, 'N'};
        if (E == 0 || E == WEST) return {1, 'E'};
        if (S == 0 || S == NORTH) return {1, 'S'};
        if (W == 0 || W == EAST) return {1, 'W'};
    
        return {2, 'H'};
    }
    
    if (C == 0) {
        if (N == 1) return {2, 'N'};
        if (E == 1) return {2, 'E'};
        if (S == 1) return {2, 'S'};
        if (W == 1) return {2, 'W'};
    }
    
    if (C == 2) {
        bool is_root = N == 1 || E == 1 || S == 1 || W == 1 || (N == -2 && W == -2); 
    
        if (N == 2) return {is_root ? 2 : NORTH, 'N'};
        if (E == 2) return {is_root ? 2 : EAST, 'E'};
        if (S == 2) return {is_root ? 2 : SOUTH, 'S'};
        if (W == 2) return {is_root ? 2 : WEST, 'W'};
    
        if (N == 1) return {2, 'N'};
        if (E == 1) return {2, 'E'};
        if (S == 1) return {2, 'S'};
        if (W == 1) return {2, 'W'};
    
        if (N == -2 && W == -2) return {NORTH, 'H'};
    }
    
    return {0, 'H'};
}
    
void program_pulibot() {
    for (int n = -2; n <= 6; n++) {
        for (int e = -2; e <= 6; e++) {
            for (int s = -2; s <= 6; s++) {
                for (int w = -2; w <= 6; w++) {
                    for (int c = -2; c <= 6; c++) {
                        auto [cc, m] = instr(c, n, e, s ,w);
                        set_instruction({c, w, s, e, n}, cc, m);
                    }
                }
            }
        }
    }
}