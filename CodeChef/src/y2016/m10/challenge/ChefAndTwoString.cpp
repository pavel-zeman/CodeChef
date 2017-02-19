// Simple dynamic programming (if the string starts with 1, then it's good, if the string without the first character is good, if it starts with 221, it is good, if the string after 221 is good, in all other cases the string is not good)
// https://www.codechef.com/OCT16/problems/CHEFTWOS
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

#define MAX_N 100010
char a[MAX_N];
char b[MAX_N];
int nn[3][2] = {{0, 1}, {3, 2}, {0, 3}};
bool valid[3][2] = {{true, true}, {false, true}, {true, false}};

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int l = getString(a);
        getString(b);
        FOR(i, l) a[i] -= '1';
        FOR(i, l) b[i] -= '1';

        int prev[4][4];
        l--;
        FOR(i, 4) FOR(j, 4) prev[i][j] = i == 0 && j == 0 ? 2 : 0;
        int curr[3][3];
        while (--l >= 0) {
            FOR(i, 3) FOR(j, 3) {
                int r = prev[nn[i][a[l]]][nn[j][b[l]]] + prev[nn[i][b[l]]][nn[j][a[l]]];
                if (r >= MOD) r-= MOD;
                curr[i][j] = r;
            }
            FOR(i, 3) FOR(j, 3) prev[i][j] = curr[i][j];
        }
        print(prev[0][0]);
    }
}

