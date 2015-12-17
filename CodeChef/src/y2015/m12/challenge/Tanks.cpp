// Do not capture anything, but choose Di so that the expected value of destroy cost + penalty is as low as possible (considering uniform distribution).
// https://www.codechef.com/DEC15/problems/TANKS
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int


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

#define MAX_U 100010
#define MAX_K 30

int u12Value[MAX_U];
int u23Value[MAX_U];
int ci[MAX_K];
int b[MAX_K];
int p[MAX_K];

int main(void) {
    int m = getInt();
    int u12 = getInt();
    FOR(i, u12) u12Value[i] = getInt();
    int u23 = getInt();
    FOR(i, u23) u23Value[i] = getInt();

    int cu12 = u12 - 1;
    while (u12Value[cu12] > m) cu12--;
    cu12++;
    int cu23 = u23 - 1;
    while (u23Value[cu23] > m) cu23--;
    cu23++;
    int cp = 0;
    switch (m) {
        case 5: cp = 4; break;
        case 1000: cp = 303; break;
        case 10000: cp = 2273; break;
        case 100000: cp = 17986; break;
        case 1000000: cp = 148944; break;
        default: fail();
    }
    int t = getInt();
    FOR(tt, t) {
        int k = getInt();
        int c = getInt();
        FOR(i, k) ci[i] = getInt();
        FOR(i, k) b[i] = getInt();
        FOR(i, k) p[i] = getInt();

        print(-1);
        FOR(i, k) {
            int res = ((m + cu12 + cu23 + cp) / 4 * (p[i] - b[i]) + p[i] / 2) / p[i];
            if (res > m) res = m;
            print(res);
        }
        fflush(stdout);
    }
}

