// Descartes' theorem - f(n+1) = a + b + f(n) +- 2 * sqrt(a*b + a*f(n) + b*f(n)). Solving the recurrence for f(n) we get f(n) = f(0) - (n - 1) * (2 * sqrt((a + b) * f(0) + a * b) - (a + b) * n + a + b).
// http://www.codechef.com/JULY15/problems/NTHCIR
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

void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}


int main(void) {
    int t;
    scanf("%d", &t);
    int n, p, m, b;
    scanf("%d %d %d %d", &n, &p, &m, &b);
    double r1, r2, r3, r4;
    scanf("%lf %lf %lf %lf", &r1, &r2, &r3, &r4);
    double invr1 = -1 / r1, invr2 = 1 / r2;
    double temp = 1 / r4;
    double r[10];
    r[1] = r1;
    r[2] = r2;
    r[3] = r3;
    r[4] = r4;


    temp = invr1 + invr2 + temp + 2 * sqrt(invr1 * invr2 + invr1 * temp + invr2 * temp);
    if (1 / temp / r[3] > 0.999999 && 1 / temp / r[3] < 1.000001) {
        temp = 1 / r4;
        temp = invr1 + invr2 + temp - 2 * sqrt(invr1 * invr2 + invr1 * temp + invr2 * temp);
    }
    r[5] = 1 / temp;

    double result = 0;
    temp = 1 / r3;
    double part = 2 * sqrt((invr1 + invr2) * temp + invr1 * invr2) + invr1 + invr2;

    FOR(tt, t) {
        n = (((long long int)p) * n) % m + b;
        if (n <= 5)
            result += r[n];
        else
            result += 1 / (temp - (n - 3) * (part - (invr1 + invr2) * (n - 2)));
    }
    printf("%.6lf\n", result);
}

