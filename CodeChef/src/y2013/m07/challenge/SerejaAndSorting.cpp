// Simply finds maximum in each step and moves it to the end
// http://www.codechef.com/JULY13/problems/SEASOR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1100
#define STEPS_MAX 1040000

int data[MAX_N];
int steps[STEPS_MAX];



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


int findMax(int from, int to) {
    int max = 0;
    int pos = -1;
    FORE(i, from, to + 1) {
        if (data[i] >= max) {
            max = data[i];
            pos = i;
        }
    }
    return pos;
}


int cmp(const void *p1, const void *p2) {
    return *((int *)p1) - *((int *)p2);
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        FOR(i, n) data[i] = getInt();

        int stepCount = 0;

        FOR(i, n) {
            int targetPos = n - i - 1;
            int pos = findMax(0, targetPos);
            while (pos < targetPos) {
                int sortStart = pos;
                if (sortStart + k - 1 > targetPos) sortStart = targetPos - k + 1;
                if (sortStart < 0) sortStart = 0;
                qsort(data + sortStart, k, sizeof(data[0]), cmp);
                steps[stepCount++] = sortStart;
                pos = sortStart + k - 1;
                if (stepCount >= STEPS_MAX) break;
            }
            if (stepCount >= STEPS_MAX) break;
        }
        printf("%d\n", stepCount);
        FOR(i, stepCount) printf("%d ", steps[i] + 1);
        printf("\n");
    }
}
