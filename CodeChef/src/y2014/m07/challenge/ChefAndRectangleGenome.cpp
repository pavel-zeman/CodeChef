// Try adding non-A nucleotids until reaching the required number of different submatrices (or run out of time)
// http://www.codechef.com/JULY14/problems/GERALD09
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <map>
#include <sys/resource.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 32
#define MOD 100000007
#define MAX_T 128


int data[MAX_T][MAX_N][MAX_N];
int lastCount[MAX_T];
int n[MAX_T], m[MAX_T], k[MAX_T];
int lastPos;
int lastValue;
bool done[MAX_T];
const char *letters = "ACGT";

map<int, bool> used;

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

__inline__ int getValue(int tt, int x, int y, int sx, int sy) {
    int value = 0;
    FOR(i, sx) FOR(j, sy) {
        value |= data[tt][i + x][j + y];
        value <<= 2;
        value %= MOD;
    }
    return value;
}

int calc(int tt) {
    int nn = n[tt];
    int mm = m[tt];
    int total = 0;
    FOR(i, nn) FOR(j, mm) {
        used.clear();
        FOR(k, nn - i) FOR(l, mm - j) {
            int value = getValue(tt, k, l, i + 1, j + 1);
            map<int, bool>::iterator it = used.find(value);
            if (it == used.end()) {
                // not found
                total++;
                used.insert(pair<int, bool>(value, true));
            }
        }
    }
    return total;
}

int startTime;

int getTime() {
    struct rusage t;
    struct timeval tv;
    getrusage(RUSAGE_SELF, &t);
    tv = t.ru_utime;
    return t.ru_utime.tv_sec * 1000000 + t.ru_utime.tv_usec + t.ru_stime.tv_sec * 1000000 + t.ru_stime.tv_usec;
}

void startTimer() {
    startTime = getTime();
}

int currentTime() {
    return getTime() - startTime;
}

void generateValue(int tt) {
    lastPos = rand() % (n[tt] * m[tt]);
    lastValue = data[tt][lastPos / m[tt]][lastPos % m[tt]];
    data[tt][lastPos / m[tt]][lastPos % m[tt]] = 1 + rand() % 3;
}

int main(void) {
    startTimer();
    int t = getInt();
    int missing = t;
    FOR(tt, t) {
        n[tt] = getInt(), m[tt] = getInt(), k[tt] = getInt();
        FOR(i, n[tt]) FOR(j, m[tt]) data[tt][i][j] = 0;
        done[tt] = false;
        lastCount[tt] = calc(tt);
        if (lastCount[tt] >= k[tt]) {
            done[tt] = true;
            missing--;
        }
    }

    while (currentTime() < 950000 && missing > 0) {
        FOR(tt, t) {
            if (currentTime() > 950000) break;
            if (!done[tt]) {
                generateValue(tt);
                int c = calc(tt);
                if (c < lastCount[tt]) {
                    data[tt][lastPos / m[tt]][lastPos % m[tt]] = lastValue;
                } else {
                    if (c >= k[tt]) {
                        done[tt] = true;
                        missing--;
                        if (c - k[tt] > k[tt] - lastCount[tt]) {
                            data[tt][lastPos / m[tt]][lastPos % m[tt]] = lastValue;
                        }
                    }
                    lastCount[tt] = c;
                }
            }
        }
    }


    FOR(tt, t) {
        //printf("%d ", lastCount[tt]);
        FOR(i, n[tt]) {
            FOR(j, m[tt]) printf("%c", letters[data[tt][i][j]]);
            printf("\n");
        }
    }

}
