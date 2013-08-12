// Just guessed the formula ...
// http://www.codechef.com/COOK36/problems/TAAPLUSB
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100100

double result[MAX_N];



char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}



int main(void) {
    double part2 = 0.45;
    double part1 = 0;
    FORE(i, 1, MAX_N) {
        result[i] = part1 + part2;
        part1 += 0.5;
        part2 = part2 / 10 + 0.4;
    }
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        printf("%.10lf\n", result[n]);
    }
}
