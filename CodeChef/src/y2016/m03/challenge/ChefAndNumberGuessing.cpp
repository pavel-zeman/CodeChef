// Use as much queries of all types as possible
// https://www.codechef.com/MARCH16/problems/CHNGSS
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000007


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

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
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

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

void fail() {
    *((char *)0) = 0;
}

#define MAX_DATA 250010
#define MAX_QUESTIONS 500000
int data[MAX_DATA];


int main(void) {
    int n, m, c;
    scanf("%d %d %d", &n, &m, &c);
    FOR(i, n * m) data[i] = 25;
    FOR(i, c) {
        int x = i / m + 1;
        int y = i % m + 1;
        printf("2 %d %d %d %d\n", x, x, y, y);
        fflush(stdout);
        scanf("%d", &data[i]);
    }
    int totalQuestions = c;
    FORE(i, c, n * m) {
        int x = i / m + 1;
        int y = i % m + 1;
        int a = 1;
        int b = 50;
        FOR(j, 2) {
            if (++totalQuestions > MAX_QUESTIONS) goto end;
            int c = (a + b) >> 1;
            printf("1 %d %d %d %d %d %d\n", x, x, y, y, a, c);
            fflush(stdout);
            int result;
            scanf("%d", &result);
            if (result == 1) b = c; else a = c + 1;
        }
        data[i] = (a + b) >> 1;
    }
    end:
    printf("%d ", 3);
    FOR(i, n * m) printf("%d ", data[i]);
}

