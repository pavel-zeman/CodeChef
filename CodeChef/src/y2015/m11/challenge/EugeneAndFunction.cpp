// The value of F must be an arithmetic progression (with wrap around when getting above 9) as well. So calculate its step and then the total.
// https://www.codechef.com/NOV15/problems/KFUNC
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

int getCipherSum(int x) {
    while (x >= 10) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        x = sum;
    }
    return x;
}

int perLengths[] = {1, 9, 9, 3, 9, 9, 3, 9, 9};

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int a = getInt();
        int d = getInt();
        long long int l = getLongLongInt();
        long long int r = getLongLongInt();

        int values[10];
        int step = d % 9;
        int periodLength = perLengths[step];
        int cs = getCipherSum(a);
        int periodSum = 0;
        FOR(i, periodLength) {
            periodSum += cs;
            values[i] = cs;
            cs += step;
            if (cs > 9) cs -= 9;
        }

        long long int totalPeriods = (r - l + 1) / periodLength;
        long long int result = totalPeriods * periodSum;
        l += totalPeriods * periodLength;
        int periodPos = (l - 1) % periodLength;
        while (l <= r) {
            result += values[periodPos++ % periodLength];
            l++;
        }
        print(result);
    }
}

