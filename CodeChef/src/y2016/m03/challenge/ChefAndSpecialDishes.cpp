// If the number of characters is even, then just check double string. Otherwise try to remove one character from the first or second half (there is a special case - string of length 1 is not double).
// https://www.codechef.com/MARCH16/problems/CHEFSPL
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_LENGTH 1000010
char s[MAX_LENGTH];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int l = getString(s);
        int l2 = l >> 1;
        bool ok = true;

        if (l == 1) ok = false;
        else if ((l & 1) == 0) {
            FOR(i, l2) if (s[i] != s[i + l2]) {
                ok = false;
                break;
            }
        } else {
            int fix = 0;
            FOR(i, l2)
                if (s[i] != s[i + l2 + fix]) {
                    if (fix == 0) {
                        fix = 1;
                        i--;
                    } else {
                        ok = false;
                        break;
                    }
                }
            if (!ok) {
                ok = true;
                fix = 0;
                FOR(i, l2)
                    if (s[i + fix] != s[i + l2 + 1]) {
                        if (fix == 0) {
                            fix = 1;
                            i--;
                        } else {
                            ok = false;
                            break;
                        }
                    }
            }
        }
        puts(ok ? "YES" : "NO");
    }
}

