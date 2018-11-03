// Dynamic programming based on current positing and remaining number of ones
// https://www.codechef.com/SNCK1A19/problems/CHEFADD
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
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

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MAX_BITS 40
int bitsa[MAX_BITS];
int bitsb[MAX_BITS];
int bitsc[MAX_BITS];
int res[MAX_BITS][MAX_BITS][MAX_BITS][2];

int getBits(int num, int *b) {
    int l = 0;
    while (num > 0) {
        *b++ = num & 1;
        num >>= 1;
        l++;
    }
    *b++ = 0;
    return l + 1;
}

int getOnes(int *b, int l) {
    int r = 0;
    FOR(i, l) r += *b++;
    return r;
}

int solve(int pos, int ra, int rb, int c) {
    int r = res[pos][ra][rb][c];
    if (r < 0) {
        r = 0;
        int ti = ra > 0 ? 2 : 1;
        int tj = rb > 0 ? 2 : 1;
        FOR(i, ti) FOR(j, tj) {
            int d = (i + j + c);
            if ((d & 1) == bitsc[pos]) {
                r += solve(pos + 1, ra - i, rb - j, d >= 2 ? 1 : 0);
            }
        }
        res[pos][ra][rb][c] = r;
    }
    return r;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        FOR(i, MAX_BITS) bitsa[i] = bitsb[i] = bitsc[i] = 0;
        int a = getInt();
        int b = getInt();
        int c = getInt();
        getBits(a, bitsa);
        getBits(b, bitsb);
        int l = getBits(c, bitsc);
        FOR(x, l - 1) FOR(i, l) FOR(j, l) FOR(k, 2) res[x][i][j][k] = -1;
        FOR(i, l) FOR(j, l) FOR(k, 2) res[l - 1][i][j][k] = 0;
        res[l - 1][0][0][0] = 1;
        res[l - 1][0][0][1] = 0;
        print(solve(0, getOnes(bitsa, l), getOnes(bitsb, l), 0));
    }
}

