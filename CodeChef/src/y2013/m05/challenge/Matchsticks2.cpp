/** Faster version */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <iostream>
#include <cstdio>
#include <sys/time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define MIN 1000000000
#define MAXSTICKS 110000

int n;
int maxa[MAXSTICKS * 2], mina[MAXSTICKS * 2];
int levels[30];
int levelSize[30];
int totalLevels;

int inline fmax(int a, int b) {
    return a > b ? a : b;
}

int inline fmin(int a, int b) {
    return a > b ? b : a;
}


int maxInterval(int i1, int i2) {
    int level = 0;
    int mult = 1;
    int pos = i1;
    int max = 0;

    // first part
    int c = pos;
    while (pos + mult <= i2 + 1) {
        if ((c & 1) != 0) {
            max = fmax(max, maxa[levels[level] + c]);
            pos += mult;
        }
        c++;
        c >>= 1;
        mult <<= 1;
        level++;
    }

    while (pos <= i2) {
        if (pos + mult <= i2 + 1) {
            max = fmax(max, maxa[levels[level] + (pos >> level)]);
            pos += mult;
        }
        mult >>= 1;
        level--;
    }
    return max;
}


int minInterval(int i1, int i2) {
    int level = 0;
    int mult = 1;
    int pos = i1;
    int min = MIN;

    // first part
    int c = pos;
    while (pos + mult <= i2 + 1) {
        if ((c & 1) != 0) {
            min = fmin(min, mina[levels[level] + c]);
            pos += mult;
        }
        c++;
        c >>= 1;
        mult <<= 1;
        level++;
    }

    while (pos <= i2) {
        if (pos + mult <= i2 + 1) {
            min = fmin(min, mina[levels[level] + (pos >> level)]);
            pos += mult;
        }
        mult >>= 1;
        level--;
    }
    return min;
}

void calcLevels(int level, int pa, int pb) {
    if (pb - pa <= 0) return;
    totalLevels = level;
    int dst = pb + 1;
    int src = pa;
    levels[level] = dst;
    levelSize[level] = levelSize[level - 1] * 2;


    while (src <= pb) {
        int max = maxa[src];
        if (src + 1 <= pb && maxa[src + 1] > max) max = maxa[src + 1];
        maxa[dst] = max;

        int min = mina[src];
        if (src + 1 <= pb && mina[src + 1] < min) min = mina[src + 1];
        mina[dst++] = min;
        src += 2;
    }
    calcLevels(level + 1, pb + 1, dst - 1);
}

char c = 0;
int getInt() {
    int r = 0;
    while (c < '0' || c > '9') c = getc(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc(stdin);
    }
    return r;
}

int getTime() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec % 60) * 1000000 + time.tv_usec;
}

int main(void) {
    n = getInt();
    FOR(i, n) maxa[i] = getInt();
    FOR(i, n) mina[i] = maxa[i];

    levels[0] = 0;
    levelSize[0] = 1;
    calcLevels(1, 0, n - 1);

    int q;
    scanf("%d", &q);
    FOR(i, q) {
        int l, r;
        l = getInt();
        r = getInt();
        int max1 = fmax(l > 0 ? maxInterval(0, l - 1) : 0, r < n - 1 ? maxInterval(r + 1, n - 1) : 0);
        int max2 = maxInterval(l, r);
        int min = minInterval(l, r);
        int p2 = max1 * 2;
        if (max2 - min > p2) p2 = max2 - min;
        double res = min + ((double)p2) / 2;

        printf("%.1lf\n", res);
    }
}
