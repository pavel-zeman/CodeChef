// Try all possible combinations with the given sum from left, right or left and right
// http://www.codechef.com/FEB14/problems/TWODOGS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_T 1000010
#define MAX_N 500010

int lPos[MAX_T];
int rPos[MAX_T];


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

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int n = getInt();
    int k = getInt();
    int t[MAX_N];
    FOR(i, n) t[i] = getInt();

    int m = INT_MAX;
    FOR(i, MAX_T) lPos[i] = rPos[i] = -1;

    FOR(i, n) {
        int v = t[i];
        if (lPos[v] == -1) lPos[v] = i;
        v = t[n - 1 - i];
        if (rPos[v] == -1) rPos[v] = i;
    }

    for(int v1 = 1;v1<k && v1 < (k - v1);v1++) {
        int v2 = k - v1;
        if (lPos[v1] != -1) {
            if (lPos[v2] != -1) m = min(m, max(lPos[v1], lPos[v2]));
            if (rPos[v2] != -1) m = min(m, max(lPos[v1], rPos[v2]));
        }
        if (rPos[v1] != -1) {
            if (rPos[v2] != -1) m = min(m, max(rPos[v1], rPos[v2]));
            if (lPos[v2] != -1) m = min(m, max(rPos[v1], lPos[v2]));
        }
    }
    printf("%d\n", m == INT_MAX ? -1 : m + 1);
}
