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

int data[MAXM];
bool used[MAXM];


char c;
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
    memset(used, 0, sizeof(used));

    int m = getInt();
    FOR(i, m) used[data[i] = getInt()] = true;

    qsort(data, m, sizeof(data[0]), cmp);

    FOR(i, m) FORE(j, i + 1, m)
        if (data[j] + data[j] - data[i] <= m && used[data[j] + data[j] - data[i]]) {
            printf("%d %d\n", data[i], data[j]);
            return 1;
        }
    return 0;
}
