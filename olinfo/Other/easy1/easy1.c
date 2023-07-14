#include <stdio.h>
#include <assert.h>

/* reg[0] = instruction pointer
 * reg[1] = status
 * reg[1] = input register
 * reg[2] = output register
 */
#define ip (reg[0])
#define st (reg[1])
#define in (reg[2])
#define out (reg[3])
static unsigned short reg[10];

static const char* prog[] = {
    "%1$60000s%15$hn",           // 0
    " %13$hn",                   // 1
    "%1$*4$s%1$65535s%21$hn",    // 2
    
    " %13$hn",                   // 3
    "%1$*4$s%17$hn",             // 4
    "%1$*5$s%19$hn",             // 5
    
    "%7$hu%1$*2$s%12$hn",        // 6
    "%1$12s%12$hn",              // 7
    "%1$12s%12$hn",              // 8
    "%1$12s%12$hn",              // 9
    "%1$12s%12$hn",              // 10
    "%1$19s%12$hn",              // 11 - MAX HIT
    "",                          // 12
    "%9$hu%1$*2$s%12$hn",        // 13
    "%1$18s%12$hn",              // 14
    "%1$18s%12$hn",              // 15
    "%1$18s%12$hn",              // 16
    "%1$18s%12$hn",              // 17
    "%1$26s%12$hn",              // 18 - MAX HIT
    "%1$21s%12$hn",              // 19
    "%1$*4$s%15$n",              // 20 - CHMAX
    "%1$26s%12$n",               // 21
    " %1$*7$s%17$hn",            // 22 - ITERATE
    " %1$*9$s%19$hn",            // 23
    "%1$5s%12$hn",               // 24
    NULL,                        // 25
    NULL,                        // 26
    "%1$*11$s%1$65535s%21$hn",   // 27 - NEW CYCLE
    "%11$hu%1$*2$s%12$hn",       // 28
    "%1$2s%12$hn",               // 29
    "%1$2s%12$hn",               // 30
    "%1$2s%12$hn",               // 31
    "%1$2s%12$hn",               // 32
    "%1$2s%12$hn",               // 33
    "  %13$hn",                  // 34
    "",                          // 35
    NULL,                        // 36
};

int main() {
    FILE *ifs = fopen("input.txt", "r");
    FILE *ofs = fopen("output.txt", "w");
    FILE *null = fopen("/dev/null", "w");
    
    while (prog[ip] != NULL) {
        if (st == 1) {
            fscanf(ifs, "%hd", &in);
            st = 0;
        } else if (st == 2) {
            fprintf(ofs, "%hd", out);
            st = 0;
        } else {
            fprintf(
                null, prog[ip], "",
                ip, st, in, out, reg[4], reg[5], reg[6], reg[7], reg[8], reg[9],
                &ip, &st, &in, &out, &reg[4], &reg[5], &reg[6], &reg[7], &reg[8], &reg[9]
            );
            ip++;
        }
    }
}