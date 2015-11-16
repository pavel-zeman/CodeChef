// Based on sieve of Eratosthenes and OIES sequence A057660 (F(p * q) = F(p) * F(q))
// https://www.codechef.com/NOV15/problems/SMPLSUM
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

void print(long long int a) {
    char result[20];
    int resSize = 0;
    while (a > 0) {
        int b = a % 1000000000;
        a /= 1000000000;
        int c =  0;
        while (b > 0) {
            result[resSize++] = '0' + b % 10;
            b /= 10;
            c++;
        }
        if (a > 0) {
            c = 9 - c;
            FOR(i, c) result[resSize++] = '0';
        }
    }
    while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    putc_unlocked('\n', stdout);
}


#define MAX_N 10000001

long long int result[MAX_N];

int main(void) {
    FOR(i, MAX_N) result[i] = 1;
    FORE(i, 2, MAX_N) {
        if (result[i] == 1) {
            int index = i;
            int order = 1;
            long long int power = i;
            while (true) {
                long long int value = 1;
                power *= i;
                power *= i;
                if (order == 1) value = 1 + ((long long int)i) * (i - 1);
                else value = (power + 1) / (i + 1);

                int j = index;
                int pos = 1;

                for(;j<MAX_N;j+=index, pos++)
                    if (pos < i) result[j] *= value; else pos = 0;

                if ((long long int)index * i >= MAX_N) break;
                index *= i;
                order++;
            }
        }
    }

    int t = getInt();
    FOR(tt, t) print(result[getInt()]);
}

