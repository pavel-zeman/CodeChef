/**
 * This solution takes number, which has the least number of collisions with the remaining numbers.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXM 100010
#define MAXR 3000

int m;
int data[MAXM];
int n;
int result[MAXR];
bool used[MAXM];
bool full[MAXM];
bool inputItem[MAXM];
int blocked[MAXM];

char c = 0;
int getInt() {
    int r = 0;
    while (c < '0' || c > '9') c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

int cmp(const void *v1, const void *v2) {
     return (*(int *)v1 - *(int *)v2);
}

int g1(int a, int b) {
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
    return a - (b - a);
}

int g2(int a, int b) {
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
    return b + (b - a);
}

int g3(int a, int b) {
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
    return ((a + b) & 1) == 0 ? (a + b) / 2 : -1;
}

bool isInInput(int a, int k) {
    return a >= 0 && a <= data[m - 1] && inputItem[a] && !full[a] && blocked[a] != k;
}

void setBlocked(int a, int k) {
    if (a >=0 && a <= data[m - 1]) blocked[a] = k;
}

void setFull(int a) {
    if (a >=0 && a <= data[m - 1]) full[a] = true;
}

int main(void) {
    //clock_t startTime = clock();

    m = getInt();
    FOR(i, m) data[i] = getInt();

    qsort(data, m, sizeof(data[0]), cmp);

    n = 0;
    result[n++] = data[0];

    memset(full, 0, sizeof(full[0]) * (data[m - 1] + 1));
    memset(used, 0, sizeof(used[0]) * m);
    memset(inputItem, 0, sizeof(inputItem[0]) * (data[m - 1] + 1));
    FOR(i, m) inputItem[data[i]] = true;

    used[0] = true;

    int lastMin = -1;
    int lastK = 0;
    while (true) {
        memset(blocked, -1, sizeof(blocked[0]) * (data[m - 1] + 1));
        int minTotal = MAXM;
        int minIndex = -1;

        int remain = 0;
        FORE(k, lastK, m) {
            if (!used[k]) {
                if (full[data[k]]) {
                    used[k] = true;
                } else {
                    remain++;
                    int total = 0;
                    FOR(i, n) {
                        int a1 = g1(result[i], data[k]);
                        int a2 = g2(result[i], data[k]);
                        int a3 = g3(result[i], data[k]);
                        total += (isInInput(a1, k) ? 1 : 0) + (isInInput(a2, k) ? 1 : 0) + (isInInput(a3, k) ? 1 : 0);
                        setBlocked(a1, k);
                        setBlocked(a2, k);
                        setBlocked(a3, k);
                    }
                    if (total < minTotal) {
                        minTotal = total;
                        minIndex = k;
                    }
                }
            }
        }
        printf("%d %d %d %d\n", n, minIndex, minTotal, remain);
        if (minIndex == -1) break;
        lastMin = minTotal;
        FOR(i, n) {
            setFull(g1(result[i], data[minIndex]));
            setFull(g2(result[i], data[minIndex]));
            setFull(g3(result[i], data[minIndex]));
        }
        result[n++] = data[minIndex];
        used[minIndex] = true;
    }

    FOR(k, m) {
        if (!used[k]) {
            if (full[data[k]]) {
                used[k] = true;
            } else {
                FOR(i, n) {
                    setFull(g1(result[i], data[k]));
                    setFull(g2(result[i], data[k]));
                    setFull(g3(result[i], data[k]));
                }
                result[n++] = data[k];
            }
        }
    }

    printf("%d\n", n);
    printf("%d", result[0]);
    FORE(i, 1, n) printf(" %d", result[i]);
}
