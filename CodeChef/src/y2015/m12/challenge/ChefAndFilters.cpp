// Simple dynamic programming based on XOR features of the filters. The complexity is 2^10 * N, which could be optimized to 2^10 * 2^10 * log N by processing same filters together.
// https://www.codechef.com/DEC15/problems/CHEFFILT
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

void fail() {
    *((char *)0) = 0;
}


#define POSS 1024
#define MAX_S 20
#define MOD 1000000007


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        char s[MAX_S];
        int l = getString(s);
        int start = 0;
        FOR(i, l) if (s[i] == 'w') start |=  1 << i;

        int poss1[POSS], poss2[POSS];
        FOR(i, POSS) poss1[i] = 0;
        poss1[start] = 1;
        int *currPoss = poss2;
        int *prevPoss = poss1;

        int n = getInt();
        FOR(i, n) {
            l = getString(s);
            int v = 0;
            FOR(j, l) if (s[j] == '+') v |=  1 << j;
            memcpy(currPoss, prevPoss, sizeof(poss1));
            FOR(j, POSS)
                if (prevPoss[j] != 0)
                    currPoss[j ^ v] = (currPoss[j ^ v] + prevPoss[j]) % MOD;
            swap(currPoss, prevPoss);
        }
        print(prevPoss[0]);
    }
}

