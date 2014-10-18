// Just naive algorithm
// http://www.codechef.com/AUG14/problems/SEASHUF
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

#define MAX_N 100010
#define MAX_V 1000000010
#define MAX_RESULT 400
int a[MAX_N];
int rl[MAX_RESULT];
int rr[MAX_RESULT];
int resultCount;

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

long long int abs(long long int x) {
    return x >= 0 ? x : -x;
}


int findMax(int from, int to, int lessThan) {
    int max = 1;
    int pos = -1;
    for(int i=to - 1;i>=from;i--) if (a[i] > max && a[i] < lessThan) {
        max = a[i];
        pos = i;
    }
    return pos;
}

int findMin(int from, int to, int greaterThan) {
    int min = MAX_V;
    int pos = -1;
    for(int i=to - 1;i>=from;i--) if (a[i] < min && a[i] > greaterThan) {
        min = a[i];
        pos = i;
    }
    return pos;
}


int main(void) {
    int n = getInt();
    FOR(i, n) a[i] = getInt();
    int firstRight = n / 2;
    long long int suml = 0, sumr = 0;
    FOR(i, firstRight) suml += a[i];
    FORE(i, firstRight, n) sumr += a[i];

    int l = -1, r = -1;
    int resultCount = 0;
    long long int origDif = suml - sumr;
    long long int lastDif = suml - sumr;
    int totalMoves = 0;

    long long int bestDif = abs(origDif);
    int bestStep = 0;
    while (totalMoves < 2 * n && resultCount < MAX_RESULT) {
        r = firstRight + MAX_RESULT;
        if (r >= n) r = n - 1;
        l = firstRight - 1;
        int minL = l - 400 >= 0 ? l - 400 : 0;

        long long int minDif = abs(lastDif + 2 * a[firstRight] - 2 * a[l]) + 1;
        for(int i=l;i>=minL;i--) {
            long long int newDif = abs(lastDif + 2 * a[firstRight] - 2 * a[i]);
            if (newDif < minDif) {
                l = i;
                minDif = newDif;
            }
        }
        lastDif = lastDif + 2 * a[firstRight] - 2 * a[l];
        int temp = a[l];
        FORE(i, l, r) a[i] = a[i + 1];
        a[r] = temp;
        rl[resultCount] = l;
        rr[resultCount] = r;
        resultCount++;
        totalMoves += r - l + 1;
        if (abs(lastDif) < bestDif && totalMoves <= 2 * n) {
            bestDif = abs(lastDif);
            bestStep = resultCount;
        }
    }
    printf("%d\n", bestStep);
    FOR(i, bestStep) printf("%d %d\n", rl[i] + 1, rr[i] + 1);
}
