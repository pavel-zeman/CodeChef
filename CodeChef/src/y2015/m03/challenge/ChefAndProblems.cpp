// Pre-calculate results for each interval of the type of (i * sqrt(N), j * sqrt(N)). Then use this pre-calculated value and extend the interval to the required upper and lower bound.
// http://www.codechef.com/MARCH15/problems/QCHEF
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MAX_NSQ 640

int n, m, k;
int a[MAX_N];

struct First {
    int round;
    int pos;
} first[MAX_N];

struct PosCache {
    int round;
    int pos;
} firstPos[MAX_N], lastPos[MAX_N];

vector<int> positions[MAX_N];

int memo[MAX_NSQ][MAX_NSQ];
int segmentSize;
int segments;
int l, r;

int hist[MAX_N];
int maxHist;


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

int max(int a, int b) {
    return a > b ? a : b;
}

int findLast(int what, int round) {
    if (maxHist < 500) {
        // this is a hack - the target server seems to have low CPU cache and for small lists the brute force approach is much faster
        int i = positions[what].size() - 1;
        while (positions[what][i] > r) i--;
        return positions[what][i];
    }

    if (lastPos[what].round != round) {
        int a = 0;
        int b = positions[what].size() - 1;
        while (a < b) {
            int mid = (a + b) >> 1;
            if (positions[what][mid] <= r) a = mid + 1; else b = mid - 1;
        }
        while (a >= positions[what].size()) a--;
        while (positions[what][a] > r) a--;

        lastPos[what].round = round;
        lastPos[what].pos = positions[what][a];
    }
    return lastPos[what].pos;
}

int findFirst(int what, int round) {
    if (maxHist < 500) {
        int i = 0;
        while (positions[what][i] < l) i++;
        return positions[what][i];
    }

    if (firstPos[what].round != round) {
        int a = 0;
        int b = positions[what].size() - 1;
        while (a < b) {
            int mid = (a + b) >> 1;
            if (positions[what][mid] >= l) b = mid - 1; else a = mid + 1;
        }
        while (b < 0) b++;
        while (positions[what][b] < l) b++;

        firstPos[what].round = round;
        firstPos[what].pos = positions[what][b];
    }
    return firstPos[what].pos;
}


int main(void) {
    n = getInt();
    m = getInt();
    k = getInt();
    FOR(i, n) {
        a[i] = getInt();
        hist[a[i]]++;
    }
    FOR(i, m + 1) positions[i].reserve(hist[i]);
    FOR(i, m + 1) maxHist = max(maxHist, hist[i]);

    FOR(i, n) positions[a[i]].push_back(i);

    FOR(i, m + 1) first[i].round = -1;
    segmentSize = sqrt(n) / 2 + 1;
    segments = n / segmentSize;
    if (segments * segmentSize < n) segments++;
    FOR(i, segments) {
        int result = 0;
        int pos = i * segmentSize;
        FORE(j, i, segments) {
            FOR(k, segmentSize) {
                if (pos < n) {
                    if (first[a[pos]].round != i) {
                        first[a[pos]].round = i;
                        first[a[pos]].pos = pos;
                    }
                    int d = pos - first[a[pos]].pos;
                    if (d > result) result = d;
                }
                pos++;
            }
            memo[i][j] = result;
        }
    }

    FOR(i, m + 1) first[i].round = firstPos[i].round = lastPos[i].round = -1;

    FOR(i, k) {
        l = getInt() - 1;
        r = getInt() - 1;
        int sl = l / segmentSize;
        int sr = r / segmentSize;
        int result = 0;
        if (sl == sr) {
            r++;
            FORE(j, l, r) {
                if (first[a[j]].round != i) {
                    first[a[j]].round = i;
                    first[a[j]].pos = j;
                }
                int d = j - first[a[j]].pos;
                if (d > result) result = d;
            }
        } else {
            int segment = sl;
            if (l % segmentSize != 0) {
                int end = sl * segmentSize + segmentSize;
                FORE(j, l, end) {
                    int d = findLast(a[j], i);
                    result = max(result, d - j);
                }
                segment++;
            }
            if (segment != sr) result = max(result, memo[segment][sr - 1]);
            int start = sr * segmentSize;
            r++;
            FORE(j, start, r) {
                int d = findFirst(a[j], i);
                result = max(result, j - d);
            }
        }
        printf("%d\n", result);
    }
}
