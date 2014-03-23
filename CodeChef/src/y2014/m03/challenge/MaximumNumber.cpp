// Range maximum query using a pre-calculated lookup table for each primer number from 2 to 100000
// http://www.codechef.com/MARCH14/problems/ANUGCD
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MAX_PRIMES 9600
#define MAX_NS 320

using namespace std;

int n, m;
int a[MAX_N];
bool prime[MAX_N];
int primes[MAX_PRIMES];
int primeMapping[MAX_N];
int maxT[MAX_PRIMES][MAX_NS];
int count[MAX_PRIMES][MAX_NS];
int primeCount = 0;
int segment;


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

int min(int a, int b) {
    return a < b ? a : b;
}

void calcPrimes() {
    prime[0] = prime[1] = false;
    FORE(i, 2, MAX_N) prime[i] = true;
    int i = 2;
    while (i * i <= MAX_N) {
        if (prime[i]) for(int j=i+i;j<MAX_N;j+=i) prime[j] = false;
        i++;
    }
    FOR(i, MAX_N) {
        if (prime[i]) {
            primes[primeCount] = i;
            primeMapping[i] = primeCount++;
        }
    }
}

int factor(int number, int *result) {
    int count = 0;
    if (prime[number]) {
        *result = primeMapping[number];
        count = 1;
    } else {
        FOR(j, primeCount) {
            if (number % primes[j] == 0) {
                do {
                    number /= primes[j];
                } while (number % primes[j] == 0);
                result[count++] = j;
            }
            if (primes[j] * primes[j] > number) {
                if (number > 1) result[count++] = primeMapping[number];
                break;
            }
        }
    }
    return count;
}

void calculateAll() {
    int i = 0;
    int resultPos = 0;
    while (i < n) {
        int stop = min(i + segment, n);
        int localCount[MAX_N];
        memset(localCount, 0, sizeof(localCount));
        vector<int> used;
        while (i < stop) {
            if (localCount[a[i]] == 0) {
                used.push_back(a[i]);
            }
            localCount[a[i]]++;
            i++;
        }
        for(vector<int>::iterator it = used.begin(); it != used.end();it++) {
            int factors[20];
            int fc = factor(*it, factors);
            FOR(j, fc) {
                if (*it > maxT[factors[j]][resultPos]) {
                    maxT[factors[j]][resultPos] = *it;
                    count[factors[j]][resultPos] = localCount[*it];
                }
            }
        }
        resultPos++;
    }
}


void findMax(int primePos, int x, int y, int *maxResult,int *countResult) {
    int primeNumber = primes[primePos];

    int segmentStart = x / segment + 1;
    if (x % segment == 0) segmentStart--;
    int segmentStartPos = segmentStart * segment;
    int segmentEnd = y / segment - 1;
    int segmentEndPos = segmentEnd * segment + segment;

    int localMax = -1;
    int localCount = -1;

    if (segmentStart > segmentEnd) {
        FORE(i, x, y + 1) {
            if (a[i] > localMax && a[i] % primeNumber == 0) {
                localCount = 0;
                localMax = a[i];
            }
            if (a[i] == localMax) localCount++;
        }
    } else {
        // first check all the segments
        FORE(i, segmentStart, segmentEnd + 1) {
            int mv = maxT[primePos][i];
            if (mv > localMax) {
                localMax = mv;
                localCount = 0;
            }
            if (mv == localMax) localCount += count[primePos][i];
        }
        // then check beginning
        if (segmentStart > 0 && maxT[primePos][segmentStart - 1] >= localMax) {
            FORE(i, x, segmentStartPos) {
                if (a[i] > localMax && a[i] % primeNumber == 0) {
                    localCount = 0;
                    localMax = a[i];
                }
                if (a[i] == localMax) localCount++;
            }
        }
        // and end
        if (segmentEndPos < n && maxT[primePos][segmentEnd + 1] >= localMax) {
            FORE(i, segmentEndPos, y + 1) {
                if (a[i] > localMax && a[i] % primeNumber == 0) {
                    localCount = 0;
                    localMax = a[i];
                }
                if (a[i] == localMax) localCount++;
            }
        }
    }
    *maxResult = localMax;
    *countResult = localCount;
}

int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, n) a[i] = getInt();

    segment = 1;
    while (segment * segment < n) segment++;
    calcPrimes();
    calculateAll();

    FOR(i, m) {
        int g = getInt();
        int x = getInt() - 1;
        int y = getInt() - 1;
        if (g == 1) {
            printf("-1 -1\n");
        } else {
            int factors[20];
            int fc = factor(g, factors);
            int maxLocal = -1, count = -1;
            FOR(j, fc) {
                int maxHelper, countHelper;
                findMax(factors[j], x, y, &maxHelper, &countHelper);
                if (maxHelper > maxLocal && countHelper > 0) {
                    maxLocal = maxHelper;
                    count = countHelper;
                }
            }
            printf("%d %d\n", maxLocal, count);
        }
    }
}
