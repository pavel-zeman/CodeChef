// For each segment of size sqrt(n) keep the cummulative sums of number of Ais. The algorithm runs in O(m * sqrt(n)) time and to speed it up, there are in fact 2 levels of segments - in the second level, the segment size is 10*sqrt(n).
// http://www.codechef.com/SEPT14/problems/CHEFINV
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 200002
#define MAX_SEGMENTS 450
#define MAX_SEGMENTS2 46
#define MULT 10

int n, m;
int a[MAX_N];
int a2[MAX_N];
int at[MAX_N];
long long int totalInversions;
int segmentSize;
int segmentSize2;
short segments[MAX_SEGMENTS][MAX_N];
short segments2[MAX_SEGMENTS2][MAX_N];
short counts[MAX_N];
int totalNumbers;
int renum[MAX_N];

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


void sort(int a, int b) {
    if (a == b) return;
    if (b == a + 1) {
        if (a2[a] > a2[b]) {
            int t = a2[a];
            a2[a] = a2[b];
            a2[b] = t;
            totalInversions++;
        }
        return;
    }
    int s = (a + b) >> 1;
    sort(a, s);
    sort(s + 1, b);

    int i1 = a;
    int i2 = s + 1;
    int i = a;

    while (i1 <= s && i2 <= b) {
        if (a2[i2] < a2[i1]) {
            at[i++] = a2[i2++];
            totalInversions += s - i1 + 1;
        } else {
            at[i++] = a2[i1++];
        }
    }

    while (i1 <= s) at[i++] = a2[i1++];
    while (i2 <= b) at[i++] = a2[i2++];
    memcpy(a2 + a, at + a, (b - a + 1) * sizeof(int));
}

int find(int value) {
    int a = 0, b = totalNumbers - 1;
    int mid = (a + b) >> 1;
    while (renum[mid] != value) {
        if (value < renum[mid]) b = mid - 1; else a = mid + 1;
        mid = (a + b) >> 1;
    }
    return mid;
}

void reNumber() {
    int num = 0;
    int lastValue = 0;
    renum[0] = 0;
    FOR(i, n) if (a2[i] != lastValue) {
        lastValue = a2[i];
        num++;
        renum[num] = lastValue;
    }
    totalNumbers = num + 1;
    FOR(i, n) a[i] = find(a[i]);
}

void createSegments() {
    segmentSize = sqrt(n);
    if (segmentSize < 1) segmentSize = 1;
    if (segmentSize > n) segmentSize = n;

    int start = 0;
    int segment = 0;
    while (start < n) {
        int end = start + segmentSize;
        if (end > n) end = n;
        FOR(i, totalNumbers) counts[i] = 0;
        FORE(i, start, end) counts[a[i]]++;
        segments[segment][0] = counts[0];
        int sum = counts[0];
        FORE(i, 1, totalNumbers) {
            segments[segment][i] = (sum << 1) + counts[i];
            sum += counts[i];
        }
        start = end;
        segment++;
    }
    int totalSegments = segment;

    segmentSize2 = MULT;
    int segment2 = 0;
    start = 0;
    while (start < totalSegments) {
        int end = start + segmentSize2;
        if (end > totalSegments) end = totalSegments;
        FOR(i, totalNumbers) segments2[segment2][i] = segments[start][i];
        FORE(i, start + 1, end) FOR(j, totalNumbers) segments2[segment2][j] += segments[i][j];
        start = end;
        segment2++;
    }
}

int calcIntervalBruteForce(int i1, int i2, int v1, int v2) {
    int total = 0;
    FORE(i, i1, i2) {
        if (a[i] >= v1 && a[i] <= v2) {
            total++;
            if (a[i] > v1 && a[i] < v2) total++;
        }
    }
    return total;
}

long long int getChanges(int i1, int i2) {
    if (i1 == i2) return 0;
    int v1 = a[i1];
    int v2 = a[i2];
    if (v1 == v2) return 0;

    int sign = v1 < v2 ? 1 : -1;
    if (i2 == i1 + 1) return sign;

    if (v1 > v2) {
        int t = v1;
        v1 = v2;
        v2 = t;
    }

    long long int total = 0;
    i1++;
    if (i1 % segmentSize != 0) {
        int end = (i1 / segmentSize + 1) * segmentSize;
        if (end > i2) end = i2;
        total += calcIntervalBruteForce(i1, end, v1, v2);
        i1 = end;
    }
    if (i1 % segmentSize == 0) {
        int segment = i1 / segmentSize;
        if (segment % segmentSize2 != 0) {
            int end = (segment / segmentSize2 + 1) * segmentSize2;
            if (end * segmentSize <= i2) {
                int segment = i1 / segmentSize;
                while (segment < end) {
                    total += segments[segment][v2] - segments[segment][v1];
                    segment++;
                }
                i1 = segment * segmentSize;
            }
        }
    }

    if (i1 % (segmentSize * segmentSize2) == 0) {
        int segment = i1 / segmentSize;
        int segment2 = segment / segmentSize2;
        while (i1 + segmentSize * segmentSize2 <= i2) {
            total += segments2[segment2][v2] - segments2[segment2][v1];
            segment2++;
            i1 += segmentSize * segmentSize2;
        }
    }

    int segment = i1 / segmentSize;

    while (i1 + segmentSize <= i2) {
        total += segments[segment][v2] - segments[segment][v1];
        segment++;
        i1 += segmentSize;
    }
    if (i1 < i2) total += calcIntervalBruteForce(i1, i2, v1, v2);
    total++;

    return total * sign;
}

int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, n) a2[i] = a[i] = getInt();
    totalInversions = 0;

    sort(0, n - 1);
    reNumber();
    createSegments();
    FOR(i, m) {
        int i1 = getInt() - 1;
        int i2 = getInt() - 1;
        if (i1 > i2) {
            int t = i1;
            i1 = i2;
            i2 = t;
        }
        printf("%lld\n", totalInversions + getChanges(i1, i2));
    }

}
