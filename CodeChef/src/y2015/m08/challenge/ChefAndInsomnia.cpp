// Keep minimum position for each Ai from 0 to 10^5. Then go from the end of the array, for each number try all its divisors and select the one with minimum position. This is where the longest interval from current position must end.
// https://www.codechef.com/AUG15/problems/CHINSM
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_N 100010
#define MAX_A 100010
int n, k;
int a[MAX_N];
int maxAllowed[MAX_N];
int minPosition[MAX_A];

int main(void) {
    n = getInt();
    k = getInt();
    FOR(i, n) a[i] = getInt();
    FOR(i, MAX_A) minPosition[i] = n;

    maxAllowed[n - 1] = n - 1;
    minPosition[a[n - 1]] = n - 1;

    int currentMax = a[n - 1];

    for(int i=n - 2;i>=0;i--) {
        maxAllowed[i] = maxAllowed[i + 1];
        if (a[i] >= k) {
            int last = maxAllowed[i + 1] + 1;
            int v = a[i] - k;
            int j = 1;
            if (v == 0) {
                FORE(j, k + 1, currentMax + 1) last = mn(last, minPosition[j]);
            } else {
                while (j * j <= v) {
                    if (v % j == 0) {
                        if (j > k) last = mn(last, minPosition[j]);
                        int j2 = v / j;
                        if (j2 > k) last = mn(last, minPosition[j2]);
                    }
                    j++;
                }
            }
            maxAllowed[i] = last - 1;
        }
        minPosition[a[i]] = i;
        currentMax = mx(currentMax, a[i]);
    }
    long long int total = 0;
    FOR(i, n) total += maxAllowed[i] - i + 1;
    print(total);
}

