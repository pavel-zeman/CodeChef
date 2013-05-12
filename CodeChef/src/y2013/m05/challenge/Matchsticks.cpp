#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define MIN 1000000000
#define MAXSTICKS 110000

int n;
int maxa[MAXSTICKS * 2], mina[MAXSTICKS * 2];
int levels[30];
int levelSize[30];
int totalLevels;



int maxInterval(int level, int i1, int i2, int l1, int l2) {
    if (i1 == l1 && i2 == l2) return maxa[levels[level] + l1 / levelSize[level]];
    int halfSize = levelSize[level - 1];
    int max1 = 0;
    if (i1 < l1 + halfSize) {
        max1 = maxInterval(level - 1, i1, i2 >= l1 + halfSize ? l1 + halfSize - 1 : i2, l1, l1 + halfSize - 1);
    }
    int max2 = 0;
    if (i2 >= l1 + halfSize) {
        max2 = maxInterval(level - 1, i1 < l1 + halfSize ? l1 + halfSize : i1, i2, l1 + halfSize, l2);
    }
    if (max2 > max1) max1 = max2;
    return max1;
}

int maxInterval(int i1, int i2) {
    return maxInterval(totalLevels, i1, i2, 0, n - 1);
}


int minInterval(int level, int i1, int i2, int l1, int l2) {
    if (i1 == l1 && i2 == l2) return mina[levels[level] + l1 / levelSize[level]];
    int halfSize = levelSize[level - 1];
    int min1 = MIN;
    if (i1 < l1 + halfSize) {
        min1 = minInterval(level - 1, i1, i2 >= l1 + halfSize ? l1 + halfSize - 1 : i2, l1, l1 + halfSize - 1);
    }
    int min2 = MIN;
    if (i2 >= l1 + halfSize) {
        min2 = minInterval(level - 1, i1 < l1 + halfSize ? l1 + halfSize : i1, i2, l1 + halfSize, l2);
    }
    if (min2 < min1) min1 = min2;
    return min1;
}

int minInterval(int i1, int i2) {
    return minInterval(totalLevels, i1, i2, 0, n - 1);
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

int main(void) {
    scanf("%d", &n);
    FOR(i, n) scanf("%d", &maxa[i]);
    FOR(i, n) mina[i] = maxa[i];
    //printf("Read %d values\n", n);
    levels[0] = 0;
    levelSize[0] = 1;
    calcLevels(1, 0, n - 1);

    //printf("Calculated levels\n");
    int q;
    scanf("%d", &q);
    FOR(i, q) {
        int l, r;
        scanf("%d%d", &l, &r);
        int max1 = 0;
        if (l > 0) max1 = maxInterval(0, l - 1);
        int max2 = 0;
        if (r < n - 1) max2 = maxInterval(r + 1, n - 1);
        if (max2 > max1) max1 = max2;

        max2 = maxInterval(l, r);

        int min = minInterval(l, r);
        int p2 = max1 * 2;
        //printf("%d %d %d %d %d\n", max2, min, mina[99999], mina[levels[totalLevels]], levelSize[totalLevels]);
        if (max2 - min > p2) p2 = max2 - min;
        double res = min + ((double)p2) / 2;

        printf("%.1lf\n", res);
    }
}
