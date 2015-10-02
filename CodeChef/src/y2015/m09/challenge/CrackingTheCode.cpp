// The key idea is that the square of the multiplication matrix is 16 (2^4). Then it's enough to calculate the first element and its exponent of 2.
// https://www.codechef.com/SEPT15/problems/CODECRCK
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

long long int getSignedLongLongInt() {
    long long int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
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

#define S6 sqrt(6)
#define S3 sqrt(3)
#define S2 sqrt(2)

int main(void) {
    int i = getInt();
    int k = getInt();
    long long int s = getSignedLongLongInt();
    int ai = getInt();
    int bi = getInt();

    double a0, b0;
    if ((i & 1) == 0) {
        a0 = ai;
        b0 = bi;
    } else {
        a0 = (-(S6 - S2) * ai - (-S2 - S6) * bi) / 16;
        b0 = (2 + S3) * ai / 4 / S2 / (1 + S3) - (S2 - S6) * bi / 16;
    }
    int e0 = -((i >> 1) << 2);
    double ak = a0, bk = b0;
    if ((k & 1) == 1) {
        ak = (S2 - S6) * a0 + (S2 + S6) * b0;
        bk = (S2 + S6) * a0 + (S6 - S2) * b0;
    }
    int ek = e0 + ((k >> 1) << 2);
    int sk = ek - s;
    double result = (ak + bk) * pow(2, sk);
    printf("%lf\n", result);
}

