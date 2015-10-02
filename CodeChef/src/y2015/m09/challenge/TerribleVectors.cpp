// Simple solution for N <= 8
// https://www.codechef.com/SEPT15/problems/TERVEC
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

#define MAX_N 100

int data[MAX_N][MAX_N];
int data2[MAX_N][MAX_N];

void copy(int x, int y, int s, int mul) {
    FOR(i, s) FOR(j, s) data2[x + i][y + j] = data[i][j] * mul;
}

void dup(int s) {
    copy(0, 0, s, 1);
    copy(0, s, s, 1);
    copy(s, 0, s, 1);
    copy(s, s, s, -1);
    FOR(i, 2 * s) FOR(j, 2 * s) data[i][j] = data2[i][j];
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        if (n == 1) printf("YES\n1\n");
        else if ((n & (n - 1)) == 0) {
            data[0][0] = 1;
            data[0][1] = 1;
            data[1][0] = 1;
            data[1][1] = -1;
            n >>= 2;
            int s = 2;
            while (n > 0) {
                dup(s);
                s <<= 1;
                n >>= 1;
            }
            printf("YES\n");
            FOR(i, s) FOR(j, s) printf("%d ", data[i][j]);
            printf("\n");
        } else printf("NO\n");
    }
}

