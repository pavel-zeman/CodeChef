// Dijkstra's algorithm on a graph with vertices based on all the combinations of point (pile) and disk
// http://www.codechef.com/JULY13/problems/RIVPILE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 2100

int n;
int x[MAX_N];
int y[MAX_N];
int dist[MAX_N][MAX_N];

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}


int sqr(int a) {
    return a * a;
}

long long int sqrl(long long int a) {
    return a * a;
}

int main(void) {
    int n = getInt();
    FOR(i, n) x[i] = 2 * getInt(), y[i] = 2 * getInt();

    FOR(i, n) FOR(j, n) dist[i][j] = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);

    /*int result = 0;
    FOR(i, n) {
        FORE(j, i + 1, n) {
            int l1 = sqr(x[j] - x[i]) + sqr(y[j] - y[i]);
            //int l1 = dist[i][j];
            FORE(k, j + 1, n) {
                int l2 = sqr(x[k] - x[i]) + sqr(y[k] - y[i]);
                int l3 = sqr(x[k] - x[j]) + sqr(y[k] - y[j]);
                //int l2 = dist[i][k];
                //int l3 = dist[j][k];
                int total = l1 + l2 + l3;
                if (l1 * 2 >= total) continue;
                if (l2 * 2 >= total) continue;
                if (l3 * 2 >= total) continue;
                result++;
            }
        }
    }*/
    long long int all = 0;
    long long int fail = 0;
    FOR(i, n) {
        FORE(j, i + 1, n) {
            int sx = (x[j] + x[i]) >> 1;
            int sy = (y[j] + y[i]) >> 1;
            int r = sqr(x[i] - sx) + sqr(y[i] - sy);
            FORE(k, j + 1, n) {
                all++;
                if (sqr(x[k] - sx) + sqr(y[k] - sy) <= r) fail++;
                /*int l2 = dist[i][k];
                int l3 = dist[j][k];
                if (l3 >= 4 * r + l2) continue;
                if (l2 >= 4 * r + l3) continue;


                result++;*/
            }
        }
    }


    printf("%lld %lld", all, all - fail);

}
