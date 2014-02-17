// Try to find submatrix with the highest number of new zeros - loop until there is one
// http://www.codechef.com/FEB14/problems/LMATRIX2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <sys/resource.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 110
#define MAX_S 9
#define MAX_K 10

int a[MAX_N][MAX_N], p[MAX_N][MAX_N];

int sum[MAX_N][MAX_N];
int balance[MAX_K][MAX_N][MAX_N];
int n, m;


struct Result {
    int x1, y1, x2, y2;
    int k;
} result[MAX_N * MAX_N];

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


int startTime;

int getTime() {
    struct rusage t;
    struct timeval tv;
    getrusage(RUSAGE_SELF, &t);
    tv = t.ru_utime;
    return t.ru_utime.tv_sec * 1000000 + t.ru_utime.tv_usec;
}

void startTimer() {
    startTime = getTime();
}

int currentTime() {
    return getTime() - startTime;
}


int main(void) {
    startTimer();

    n = getInt();
    m = getInt();

    FOR(i, n) FOR(j, m) p[i][j] = getInt();
    FOR(i, n) FOR(j, m) a[i][j] = getInt();

    FOR(i, m) sum[0][i] = 0;

    int total = 0;
    int td = 0;
    int lastMax = n * m;
    int lastX1 = 0;
    int lastY1 = 0;
    int lastX2 = n;
    int lastY2 = m;

    int lastK = 1;
    int remain = 0;
    FOR(i, n) FOR(j, m) if (a[i][j] > 0) remain++;


    FORE(kk, 1, MAX_K) FOR(i, n) FOR(j, m) {
        int a2 = (a[i][j] + kk) % p[i][j];
        balance[kk][i][j] = a2 == 0 ? 1 : 0;
        balance[kk][i][j] -= a[i][j] == 0 ? 1 : 0;
    }

    while (true) {
        int max = 0;
        int maxX1 = -1, maxX2 = -1, maxY1 = -1, maxY2 = -1, maxK = -1;

        secondTry:
        FORE(kk, 1, 10) {
            /*FOR(i, n) FOR(j, m) {
                int a2 = (a[i][j] + kk) % p[i][j];
                balance[i][j] = a2 == 0 ? 1 : 0;
                balance[i][j] -= a[i][j] == 0 ? 1 : 0;
            }*/
            FOR(i, n) {
                int total = 0;
                FOR(j, m) {
                    total += balance[kk][i][j];
                    sum[i][j + 1] = total;
                }
            }
            int sX1 = lastX1 - MAX_S;
            if (sX1 < 0) sX1 = 0;
            int sY1 = lastY1 - MAX_S;
            if (sY1 < 0) sY1 = 0;
            FORE(i, sX1, lastX2) {
                int nEnd = i + MAX_S;
                if (nEnd > n) nEnd = n;
                FORE(j, sY1, lastY2) {
                    int mEnd = j + MAX_S;
                    if (mEnd > m) mEnd = m;
                    FORE(l, j, mEnd) {
                        int total = 0;
                        FORE(k, i, nEnd) {
                            total += sum[k][l + 1] - sum[k][j];
                            if (total > max) {
                                max = total;
                                maxX1 = i;
                                maxX2 = k;
                                maxY1 = j;
                                maxY2 = l;
                                maxK = kk;
                                if (max > lastMax) goto end;
                            }
                        }
                    }
                }
            }
        }
        if (max <= 1 && (lastX1 != 0 || lastY1 != 0 || lastX2 != n || lastY2 != m)) {
            lastX1 = 0;
            lastY1 = 0;
            lastX2 = n;
            lastY2 = m;
            lastK = 1;
            //printf("Second ");
            goto secondTry;
        }
        end:
        if (max > 1 && currentTime() < 950000) {
            td += max;
            remain -= max;
            //printf("Deleting %d %d %d %d %d\n", max, td, maxX2 - maxX1, maxY2 - maxY1, maxK);
            result[total].x1 = maxX1;
            result[total].x2 = maxX2;
            result[total].y1 = maxY1;
            result[total].y2 = maxY2;
            result[total].k = maxK;
            total++;

            lastX1 = maxX1;
            lastX2 = maxX2 + 1;
            lastY1 = maxY1;
            lastY2 = maxY2 + 1;


            maxX2++;
            maxY2++;
            FORE(i, maxX1, maxX2) FORE(j, maxY1, maxY2) a[i][j] = (a[i][j] + maxK) % p[i][j];
            FORE(kk, 1, MAX_K) FORE(i, maxX1, maxX2) FORE(j, maxY1, maxY2) {
                int a2 = (a[i][j] + kk) % p[i][j];
                balance[kk][i][j] = a2 == 0 ? 1 : 0;
                balance[kk][i][j] -= a[i][j] == 0 ? 1 : 0;
            }

            lastMax = max;
            lastK = maxK;
        } else {
            FOR(i, n) FOR(j, m) {
                if (a[i][j] != 0) {
                    result[total].x1 = result[total].x2 = i;
                    result[total].y1 = result[total].y2 = j;
                    result[total].k = p[i][j] - a[i][j];
                    total++;
                    remain--;
                }
            }
            break;
        }
    }


    printf("%d\n", total);
    FOR(i, total) {
        printf("%d %d %d %d %d\n", result[i].x1 + 1, result[i].y1 + 1, result[i].x2 + 1, result[i].y2 + 1, result[i].k);
    }
    //printf("%d\n", remain);
}
