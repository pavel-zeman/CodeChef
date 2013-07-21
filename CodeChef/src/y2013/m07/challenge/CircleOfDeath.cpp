// http://www.codechef.com/JULY13/problems/CIRKILL
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 50

int n;
int x[MAX_N], y[MAX_N];

int totalKills;
bool used[MAX_N];

int trPos[3];

bool linear(int a, int b, int c) {
    int dx1 = x[a] - x[b];
    int dy1 = y[a] - y[b];
    int dx2 = x[c] - x[b];
    int dy2 = y[c] - y[b];

    return dx1 * dy2 == dx2 * dy1;
}

long long int sqr(long long int a) {
    return a * a;
}

void generateTR(int level, int startPos) {
    if (level < 3) {
        FORE(i, startPos, n) {
            used[i] = true;
            trPos[level] = i;
            generateTR(level + 1, i + 1);
            used[i] = false;
        }
    } else {
        int a = trPos[0];
        int b = trPos[1];
        int c = trPos[2];
        if (!linear(a, b, c)) {
            long long int d = 2 * (x[a] * (y[b] - y[c]) + x[b] * (y[c] - y[a]) + x[c] * (y[a] - y[b]));
            long long int uxtd = (x[a] * x[a] + y[a] * y[a]) * (y[b] - y[c]) + (x[b] * x[b] + y[b] * y[b]) * (y[c] - y[a]) + (x[c] * x[c] + y[c] * y[c]) * (y[a] - y[b]);
            long long int uytd = (x[a] * x[a] + y[a] * y[a]) * (x[c] - x[b]) + (x[b] * x[b] + y[b] * y[b]) * (x[a] - x[c]) + (x[c] * x[c] + y[c] * y[c]) * (x[b] - x[a]);

            FOR(i, n) {
                if (!used[i]) {
                    if (sqr(d * x[i] - uxtd) + sqr(d * y[i] - uytd) <= sqr(d * x[a] - uxtd) + sqr(d * y[a] - uytd)) totalKills++;
                }
            }
        }
    }
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(i, t) {
        scanf("%d", &n);
        FOR(j, n) scanf("%d%d", &x[j], &y[j]);
        FOR(j, n) used[j] = false;
        totalKills = 0;
        generateTR(0, 0);
        printf("%lf\n", (double)totalKills / (n * (n - 1) * (n - 2) * (n - 3) / 6));
    }
}
