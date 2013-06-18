/**
 * This solution simply sorts input numbers and takes one by one, if there is no collision.
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
int maxn;
int result[MAXR];
int finalResult[MAXR];
bool used[MAXM];

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

int main(void) {
    clock_t startTime = clock();

    m = getInt();
    FOR(i, m) data[i] = getInt();

    qsort(data, m, sizeof(data[0]), cmp);




    maxn = 0;
    FOR(k, m) {
        memset(used, 0, sizeof(used[0]) * (data[m - 1 ] + 1));
        n = 0;
        result[n++] = data[k];
        FORE(i, k + 1, m) {
            int test = data[i];
            if (!used[test]) {
                result[n++] = test;
                for(int j=n-2;j>=0;j--) {
                    int next = test + (test - result[j]); // 2 * test - result[j]
                    if (next <= data[m - 1]) used[next] = true; else break;
                }
            }
        }
        if (n > maxn) {
            maxn = n;
            FOR(i, n) finalResult[i] = result[i];
        }
        if (clock() - startTime > 0.97 * CLOCKS_PER_SEC) { break;}
    }

    /*int max = data[0];
    n = 0;
    result[n++] = max;
    int last = max;
    FORE(i, 1, m) {
        if (data[i] + (last - data[i]) * 2 > max) {
            last = result[n++] = data[i];
        }
    }*/
    printf("%d\n", maxn);
    printf("%d", finalResult[0]);
    FORE(i, 1, maxn) printf(" %d", finalResult[i]);
}
