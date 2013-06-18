#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXN 110
#define RIGHT 0
#define DOWN 1


int n, m;

bool data[MAXN][MAXN];
int minScare[MAXN][MAXN][2];

int min(int a, int b) {
    return a < b ? a : b;
}

int scare(int a, int b) {
    if (a < 0 || b < 0 || a >= n || b >= m) return 0;
    return data[a][b] ? 1 : 0;
}


int calc(int a, int b, int dir) {
    if (minScare[a][b][dir] != -1) return minScare[a][b][dir];

    int result = -1;
    int origDir = dir;
    if (dir == RIGHT && a == n - 1) dir = DOWN;
    if (dir == DOWN && b == m - 1) dir = RIGHT;

    switch (dir) {
        case RIGHT:
            result = min(calc(a + 1, b, RIGHT) + scare(a, b - 1) + scare(a, b + 1) + scare(a - 1, b),
                         calc(a + 1, b, DOWN) + scare(a, b - 1) + scare(a - 1, b));
            break;

        case DOWN:
            result = min(calc(a, b + 1, RIGHT) + scare(a - 1, b) + scare(a, b - 1),
                         calc(a, b + 1, DOWN) + scare(a - 1, b) + scare(a, b - 1) + scare(a + 1, b));
            break;
    }
    return minScare[a][b][origDir] = result;
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%d%d", &n, &m);
        FOR(i, n) {
            char row[MAXN];
            scanf("%s", row);
            FOR(j, m) data[i][j] = row[j] == '1';
        }
        FOR(i, n) FOR(j, m) FOR(k, 2) minScare[i][j][k] = -1;
        minScare[n - 1][m - 1][RIGHT] = minScare[n - 1][m - 1][DOWN] = (data[n - 1][m - 1] ? 1 : 0) + (data[n - 2][m - 1] ? 1 : 0) + (data[n - 1][m - 2] ? 1 : 0);

        printf("%d\n", min(calc(0, 0, RIGHT), calc(0, 0, DOWN)));
    }
}
