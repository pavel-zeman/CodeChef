// 7 is a prime number, which allows to calculate result starting from the least significant digits and only the first L digits are required. The complexity is O(L^2), which is further optimized by doing the calculations in blocks of 10.
// https://www.codechef.com/DEC15/problems/SEADIV
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

#define BASE 7
#define MAX_A 1000090
#define MAX_L 10090
#define BLOCK 10

int mul[BASE][BASE];
char a[MAX_A];
int aa[MAX_L / BLOCK];
int sum[MAX_L / BLOCK];

char b[MAX_L];
int bb[MAX_L / BLOCK];

char result[MAX_L];
int powers[BLOCK + 1];

void swap(char *data, int length) {
    int i = 0;
    int j = length - 1;
    while (i < j) swap(data[i++], data[j--]);
}

int convert(char *from, int *to, int length, int cp) {
    int pos = 0;
    int targetPos = 0;
    int value = 0;
    int mul = 1;
    FOR(i, cp) {
        value += (from[length - i - 1] - '0') * mul;
        mul *= BASE;
        pos++;
        if (pos == BLOCK) {
            to[targetPos++] = value;
            value = 0;
            pos = 0;
            mul = 1;
        }
    }
    if (pos > 0) to[targetPos++] = value;
    return targetPos;
}

int main(void) {
    powers[0] = 1;
    FORE(i, 1, BLOCK + 1) powers[i] = BASE * powers[i - 1];
    FOR(i, BASE) FOR(j, BASE) mul[i][i * j % BASE] = j;
    int mod = powers[BLOCK];

    int t = getInt();
    FOR(tt, t) {
        int la = getString(a);
        int lb = getString(b);
        while (b[lb - 1] == '0') lb--, la--;
        int l = getInt();
        int ca = la;
        if (ca > l + BLOCK) ca = l + BLOCK;
        int lla = convert(a, aa, la, ca);
        int llb = convert(b, bb, lb, lb);
        la = ca;
        aa[lla] = 0;
        bb[llb] = 0;
        FOR(i, l / BLOCK + 1) sum[i] = 0;

        int pos = 0;
        int firstNonZeroValue = bb[0] % BASE;
        while (pos < la && pos < l) {
            int ppos = pos / BLOCK;
            int aa1 = (aa[ppos] + mod - sum[ppos]) % mod;
            int digits = 0;
            FOR(i, BLOCK) {
                int digit = mul[firstNonZeroValue][aa1 % BASE];
                int sub = bb[0] * digit % mod;

                digits += digit * powers[i];
                result[pos++] = digit + '0';

                aa1 += mod - sub;
                aa1 /= BASE;
            }

            int mulCarry = 0;
            int e = llb;
            if (e + ppos > l / BLOCK) e = l / BLOCK - ppos;
            for(int i=0;i<=e; i++) {
                LLI mmt = mulCarry + sum[ppos + i] + bb[i] * (LLI)digits;
                sum[ppos + i] = mmt % mod;
                mulCarry = mmt / mod;
            }
        }
        if (pos > l) pos = l;
        pos--;

        while (result[pos] == '0' && pos > 0) pos--;
        swap(result, pos + 1);
        result[pos + 1] = 0;
        if (pos < 0) {
            result[0] = '0';
            result[1] = 0;
        }
        printString(result);
    }
}

