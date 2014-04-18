// Divide both numbers by 2 until they are equal
// http://www.codechef.com/APRIL14/problems/BINTREE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

char result[100][4];

char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

int main(void) {
    FOR(i, 100) sprintf(result[i], "%d", i);
    int n = getInt();
    FOR(tt, n) {
        int i = getInt(), j = getInt();
        int dist = 0;
        while (i != j) {
            while (i > j) { i >>= 1; dist++; }
            while (i < j) { j >>= 1; dist++; }
        }
        puts(result[dist]);
    }
}
