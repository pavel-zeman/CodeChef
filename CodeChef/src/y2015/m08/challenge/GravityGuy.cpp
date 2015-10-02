// We never need to jump to the same block of the other lane. Then go character by character and try both remaining moves.
// https://www.codechef.com/AUG15/problems/GRGUY
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

int getString(char *result) {
    int l = 0;
    while (ccc != '.' && ccc != '#') ccc = getc_unlocked(stdin);
    while (ccc == '.' || ccc == '#') {
        *result++ = ccc;
        l++;
        ccc = getc_unlocked(stdin);
    }
    *result = 0;
    return l;
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

#define MAX_L 200010
#define INF 10000000

char s[2][MAX_L];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int l = getString(s[0]);
        getString(s[1]);

        int curr[2];
        int next[2];
        FOR(i, 2) curr[i] = (s[i][0] == '.') ? 0 : INF;
        FOR(i, l - 1) {
            FOR(j, 2) next[j] = INF;
            FOR(j, 2) {
                if (curr[j] != INF) {
                    if (s[j][i + 1] == '.') next[j] = mn(next[j], curr[j]);
                    if (s[j ^ 1][i + 1] == '.') next[j ^ 1] = mn(next[j ^ 1], curr[j] + 1);
                }
            }
            FOR(j, 2) curr[j] = next[j];
        }
        int res = mn(curr[0], curr[1]);

        if (res == INF) printString("No"); else {
            printString("Yes");
            print(res);
        }
    }
}

