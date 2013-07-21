// Brute force for small arrays, search for all possible sums using O(N) algorithm for large arrays
// http://www.codechef.com/JULY13/problems/FARASA
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <set>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 200100
#define MAX_LOG_N 19
#define MIN_VALUE -1
#define MAX_USED 40000010


int n;
long long int data[MAX_N];


char used[MAX_USED];
long long int steps;


char c = 0;
long long int getInt() {
    long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


int main(void) {
    n = getInt();
    FOR(i, n) data[i] = getInt();

    int total = 0;
    if (n <= 1000) {
        std::set<long long int> usedSet;
        FOR(i, n) {
            long long int sum = 0;
            FORE(j, i, n) {
                sum += data[j];
                if (usedSet.find(sum) == usedSet.end()) {
                    usedSet.insert(sum);
                    total++;
                }
            }
        }
        total--;
    } else if (n <= 5000) {
        int totalSum = 0;
        FOR(i, n) totalSum += data[i];

        FOR(i, totalSum) used[i] = 0;

        FOR(i, n) {
            int sum = 0;
            FORE(j, i, n) {
                used[sum += data[j]] = 1;
            }
        }
        FOR(i, totalSum) if (used[i]) total++;

    } else {
        int totalSum = 0;
        FOR(i, n) totalSum += data[i];

        // find concrete value
        int sum = data[0];
        int bStart = 0;
        FORE(i, 1, totalSum) {
            if (sum < i) {
                sum += data[++bStart];
            }
            int a = 0;
            int b = bStart;
            int sum2 = sum;
            while (b < n) {
                if (sum2 == i) { total++; break;}
                if (sum2 < i) {
                    sum2 += data[++b];
                } else {
                    sum2 -= data[a++];
                }
            }
        }
    }
    printf("%d", total);
}
