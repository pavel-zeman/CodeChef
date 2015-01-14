// Precalculate values for all segments of size sqrt(n) and use them to calculate requested value in time of O(sqrt(n))
// http://www.codechef.com/JAN15/problems/QSET
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MAX_SEGMENTS 320


char digit[MAX_N];
//int substringCount[MAX_N][3];
//long long int sumSubtringCount[MAX_N];
//int sum[MAX_N];
//int sumRemainderCount[MAX_N][3];
int n;
int segmentSize;

int segmentSum[MAX_SEGMENTS];
int segmentStartRemainderCount[MAX_SEGMENTS][3];
int segmentEndRemainderCount[MAX_SEGMENTS][3];
int segmentDivisibleCount[MAX_SEGMENTS];
int tempRemainderCount[MAX_SEGMENTS][3];

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

void getDigits() {
    char *result = digit;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        *result++ = c - '0';
        c = getc_unlocked(stdin);
    }
}

int calcDivisibleCount(int a, int b) {
    int total = 0;
    FOR(j, 3) tempRemainderCount[0][j] = 0;
    FORE(i, a, b) {
        FOR(j, 3) tempRemainderCount[i - a + 1][(digit[i] + j) % 3] = tempRemainderCount[i - a][j];
        tempRemainderCount[i - a + 1][digit[i] % 3]++;
        total += tempRemainderCount[i - a + 1][0];
    }
    return total;
}


void calcSegment(int s, int a, int b) {
    segmentDivisibleCount[s] = calcDivisibleCount(a, b);

    int remainderCount[3];
    int sum = 0;
    FOR(j, 3) remainderCount[j] = 0;
    FORE(i, a, b) {
        sum += digit[i];
        remainderCount[sum % 3]++;
    }
    FOR(j, 3) segmentStartRemainderCount[s][j] = remainderCount[j];
    segmentSum[s] = sum;

    sum = 0;
    FOR(j, 3) remainderCount[j] = 0;
    FORE(i, a, b) {
        sum += digit[b - 1 - (i - a)];
        remainderCount[sum % 3]++;
    }
    FOR(j, 3) segmentEndRemainderCount[s][j] = remainderCount[j];
}

int min(int a, int b) {
    return a < b ? a : b;
}

void calcAllSegments() {
    int segment = 0;
    int segmentStart = 0;
    while (segmentStart < n) {
        calcSegment(segment, segmentStart, min(segmentStart + segmentSize, n));
        segmentStart += segmentSize;
        segment++;
    }
}


int main(void) {
    n = getInt();
    int m = getInt();
    getDigits();
    segmentSize = sqrt(n) + 1;
    if (segmentSize > n) segmentSize = n;
    calcAllSegments();

    FOR(mm, m) {
        int type = getInt();
        int a = getInt() - 1;
        int b = getInt();
        int segment = a / segmentSize;

        switch (type) {
            case 1: // value change
                digit[a] = b;
                calcSegment(segment, segment * segmentSize, min((segment + 1) * segmentSize, n));
                break;

            case 2: // query
                long long int total = 0;
                if (b - a <= segmentSize) total = calcDivisibleCount(a, b);
                else {
                    long long int endRemainderCount[3];
                    int segmentEnd = segment * segmentSize + segmentSize;
                    total += calcDivisibleCount(a, segmentEnd);

                    FOR(j, 3) endRemainderCount[j] = 0;
                    int sum = 0;
                    FORE(i, a, segmentEnd) {
                        sum += digit[segmentEnd - 1 - (i - a)];
                        endRemainderCount[sum % 3]++;
                    }
                    segment++;

                    while (segmentEnd + segmentSize <= b) {
                        total += segmentDivisibleCount[segment];
                        FOR(j, 3) total += endRemainderCount[j] * segmentStartRemainderCount[segment][(3 - j) % 3];

                        long long int endRemainderCountTemp[3];
                        sum = segmentSum[segment];
                        FOR(j, 3) endRemainderCountTemp[(j + sum) % 3] = endRemainderCount[j];
                        FOR(j, 3) endRemainderCount[j] = endRemainderCountTemp[j] + segmentEndRemainderCount[segment][j];

                        segmentEnd += segmentSize;
                        segment++;
                    }

                    if (segmentEnd < b) {
                        total += calcDivisibleCount(segmentEnd, b);
                        int remainderCount[3];
                        FOR(j, 3) remainderCount[j] = 0;
                        sum = 0;
                        FORE(i, segmentEnd, b) {
                            sum += digit[i];
                            remainderCount[sum % 3]++;
                        }
                        FOR(j, 3) total += endRemainderCount[j] * remainderCount[(3 - j) % 3];
                    }
                }
                printf("%lld\n", total);
                break;
        }
    }
}

