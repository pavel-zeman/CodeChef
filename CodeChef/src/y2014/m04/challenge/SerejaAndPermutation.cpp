// There are a couple of methods to solve this problem - so try each one and choose the best solution
// http://www.codechef.com/APRIL14/problems/SEAPERM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 2002

int a[MAX_N];
int res[MAX_N];
int final[MAX_N];
int resCount;
bool used[MAX_N];
int n, k, s;

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

long long int calcF() {
    long long int total = 0;
    FOR(i, k) {
        int temp = s;
        for (int j=i;j<n && temp >= a[res[j]];j++) temp -= a[res[j]];
        total += temp;
    }
    return total;
}

void method1(void) {
    FOR(i, n) used[i] = false, res[i] = -1;
    resCount = 0;

    int p = -1;
    FOR(i, k) {
        if (i > resCount) break;
        int total = s;
        FORE(j, i, resCount) total -= a[res[j]];
        while (total > 0) {
            p = -1;
            int min = 1000000009;
            FOR(j, n) {
                if (!used[j]) {
                    if (a[j] < min && a[j] <= total) {
                        p = j;
                        min = a[j];
                    }
                    if (a[j] == total && i + 20 >= resCount) {
                        p = j;
                        break;
                    }
                }
            }
            if (p == -1) break;
            used[p] = true;
            res[resCount++] = p;
            total -= a[p];
        }
    }

    p = 0;
    FORE(i, resCount, n) {
        while (used[p]) p++;
        res[i] = p++;
    }
}

void method2(void) {
    FOR(i, n) used[i] = false, res[i] = -1;
    resCount = 0;

    int p = -1;
    FOR(i, k) {
        if (i > resCount) break;
        int total = s;
        FORE(j, i, resCount) total -= a[res[j]];
        while (total > 0) {
            p = -1;
            int min = 1000000009;
            FOR(j, n) {
                if (!used[j]) {
                    if (a[j] < min && a[j] <= total) {
                        p = j;
                        min = a[j];
                    }
                    if (a[j] == total && i >= resCount) {
                        p = j;
                        break;
                    }
                }
            }
            if (p == -1) break;
            used[p] = true;
            res[resCount++] = p;
            total -= a[p];
        }
    }

    p = 0;
    FORE(i, resCount, n) {
        while (used[p]) p++;
        res[i] = p++;
    }
}

void method3(void) {
    FOR(i, n) used[i] = false, res[i] = -1;
    resCount = 0;
    int p = -1;
    FOR(i, k) {
        if (i > resCount) break;
        int total = s;
        FORE(j, i, resCount) total -= a[res[j]];
        while (total > 0) {
            p = -1;
            int min = 1000000009;
            FOR(j, n) {
                if (!used[j]) {
                    if (a[j] < min && a[j] <= total) {
                        p = j;
                        min = a[j];
                    }
                }
            }
            if (p == -1) break;
            used[p] = true;
            res[resCount++] = p;
            total -= a[p];
        }
    }

    p = 0;
    FORE(i, resCount, n) {
        while (used[p]) p++;
        res[i] = p++;
    }
}

void method4(void) {
    FOR(i, n) used[i] = false, res[i] = -1;
    resCount = 0;
    FOR(i, n) res[i] = i;
}


void method5(void) {
    FOR(i, n) used[i] = false, res[i] = -1;
    resCount = 0;
    int p = -1;
    FOR(i, k) {
        if (i > resCount) break;
        int total = s;
        FORE(j, i, resCount) total -= a[res[j]];
        while (total > 0) {
            p = -1;
            int max = 0;
            FOR(j, n) {
                if (!used[j]) {
                    if (a[j] > max && a[j] <= total) {
                        p = j;
                        max = a[j];
                    }
                }
            }
            if (p == -1) break;
            used[p] = true;
            res[resCount++] = p;
            total -= a[p];
        }
    }

    p = 0;
    FORE(i, resCount, n) {
        while (used[p]) p++;
        res[i] = p++;
    }
}



int main(void) {
    int t = getInt();
    long long int totalF = 0;
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        s = getInt();
        FOR(i, n) a[i] = getInt();


        method1();
        long long minF = calcF();
        FOR(i, n) final[i] = res[i];
        FOR(i, 4) {
            switch (i) {
                case 0: method2(); break;
                case 1: method3(); break;
                case 2: method4(); break;
                case 3: method5(); break;
            }
            long long int f = calcF();
            if (f < minF) {
                minF = f;
                FOR(i, n) final[i] = res[i];
            }
        }
        totalF += minF / k;

        FOR(i, n) printf("%d ", final[i] + 1);
        printf("\n");
    }
    //printf("%lld\n", totalF);
}
