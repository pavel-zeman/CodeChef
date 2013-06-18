#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXN 2000
#define MAXK 20

int n, k;
int originalValues[MAXN];
int values[MAXN];

int fixed[MAXK];
int selected[MAXK * 2];
bool firstSet[MAXK * 2];
int totalSelected;
int a, b;
long long total;


int cmp(const void *v1, const void *v2) {
     return (*(int *)v2 - *(int *)v1);
}

bool check(int remain, int pos, long long runningTotal) {
    if (runningTotal > a) {
        FOR(i, remain) runningTotal += selected[totalSelected - remain + i];
        if (total - runningTotal > b) {
            FOR(i, remain) firstSet[totalSelected - remain + i] = true;
            return true;
        }
        return false;
    }
    if (remain == 0) {
        return runningTotal > a && total - runningTotal > b;
    }
    FORE(i, pos, totalSelected - remain + 1) {
        firstSet[i] = true;
        if (check(remain - 1, i + 1, runningTotal + selected[i])) return true;
        firstSet[i] = false;
    }
    return false;
}

int findIndex(int value) {
    FOR(i, n) if (originalValues[i] == value) {
        originalValues[i] = -1;
        return i + 1;
    }
    return -1;
}

int main(void) {
    scanf("%d%d", &n, &k);
    FOR(i, n) {
        scanf("%d", &values[i]);
        originalValues[i] = values[i];
    }

    qsort(values, n, sizeof(values[0]), cmp);

    bool found = false;
    int firstSetCount = -1;

    FOR(i, n - 2 * k + 1) {
        a = values[i];
        FORE(j, i + 1, n - k + 1) {
            b = values[j];
            long long runningTotal = 0;
            int l = i + 1;
            for(int m=0;l<j && l < i + k;l++,m++) {
                runningTotal += values[l];
                fixed[m] = values[l];
            }
            total = runningTotal;

            firstSetCount = l - i - 1;
            if (l <= j) l = j + 1;
            totalSelected = 2 * k - 2 - firstSetCount;
            for(int m = 0;m < totalSelected;m++,l++) {
                selected[m] = values[l];
                firstSet[m] = false;
                total += selected[m];
            }

            if (total >= a + b + 2) {
                if (check(k - 1 - firstSetCount, 0, runningTotal)) {
                    found = true;
                    break;
                }
            }
        }
        if (found) break;
    }

    printf("%s", found ? "Yes\n" : "No");
    if (found) {
        printf("%d", findIndex(a));
        FOR(i, firstSetCount) {
            printf(" %d", findIndex(fixed[i]));
        }
        FOR(i, totalSelected) {
            if (firstSet[i]) printf(" %d", findIndex(selected[i]));
        }
        printf(" %d", findIndex(b));
        FOR(i, totalSelected) {
            if (!firstSet[i]) printf(" %d", findIndex(selected[i]));
        }
    }
}

