// Just brute force solution
// https://www.codechef.com/SEPT15/problems/MGCH3D
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


#define MAX_N 777787
int n;
int x[MAX_N], y[MAX_N], z[MAX_N];

int sqr4(int a) {
    int b = a * a;
    return b * b;
}

int main(void) {
    n = getInt();
    int q = getInt();
    FOR(i, n) {
        x[i] = getInt();
        y[i] = getInt();
        z[i] = getInt();
    }
    FOR(i, q) {
        int a = getInt();
        int b = getInt();
        int c = getInt();
        int d = getInt();
        double result = 0;
        FOR(j, n) FORE(k, j + 1, n) {
            int t = a * (x[j] - x[k]) + b * (y[j] - y[k]) + c * (z[j] - z[k]);
            result += (abs(t + d) + abs(-t + d)) /
                sqrt(sqr4(x[j] - x[k]) + sqr4(y[j] - y[k]) + sqr4(z[j] - z[k]));
        }
        result /= n;
        result /= n - 1;
        printf("%.10lf\n", result);
    }
}

