// Recursively divide the array into halves and calculate result for the halves. Specific handling is required for the beginning and end.
// https://www.codechef.com/SNCKPA16?utm_source=home&utm_medium=nav&utm_campaign=sd
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

#define MAX_M 32
#define MAX_N 100010
int mult[MAX_M];
int mult3[MAX_M];
int a[MAX_N];
int sum[MAX_N];

int getMult(int a, int b, int pow) {
    return (a * (LLI)mult[pow] + b * (LLI)(mult[pow] + MOD - 1)) % MOD;
}

int calc(int i1, int i2, int p1, int p2, int pow, int v1, int v2) {
    if (i2 == i1) return 0;
    if (p2 <= i1 || p1 >= i2) return 0;
    if (p1 >= i1 && p2 <= i2) return getMult(v1, v2, pow);
    return (calc(i1, i2, p1, (p1 + p2) >> 1, pow - 1, v1, (v1 + v2) % MOD) +
        calc(i1, i2, (p1 + p2) >> 1, p2, pow - 1, (v1 + v2) % MOD, v2)) % MOD;
}

int main(void) {
    mult[0] = 1;
    mult3[0] = 1;
    FORE(i, 1, MAX_M) {
        mult[i] = (3 * (LLI)mult[i - 1] - 1) % MOD;
        mult3[i] = 3 * (LLI)mult3[i - 1] % MOD;
    }

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        LLI x = getLongLongInt() - 1;
        LLI y = getLongLongInt();
        FOR(i, n) a[i] = getInt();
        sum[0] = a[0];
        FORE(i, 1, n) sum[i] = (sum[i - 1] + a[i]) % MOD;

        int xOrig = x >> m;
        int yOrig = y >> m;
        int result;
        if (xOrig == yOrig) result = calc(x % (1 << m), y % (1 << m), 0, 1 << m, m, a[xOrig], a[xOrig + 1]);
        else {
            result = calc(x % (1 << m), 1 << m, 0, 1 << m, m, a[xOrig], a[xOrig + 1]);
            xOrig++;
            if (xOrig < yOrig) {
                result = (result + a[xOrig] * (LLI)mult[m]) % MOD;
                result = (result + a[yOrig] * ((LLI)mult[m] + MOD - 1)) % MOD;
                if (yOrig - xOrig > 1) result = (result + ((LLI)sum[yOrig - 1] - sum[xOrig] + MOD) % MOD * mult3[m]) % MOD;
                if (result < 0) result += MOD;
            }
            result = (result + calc(0, y % (1 << m), 0, 1 << m, m, a[yOrig], a[yOrig + 1])) % MOD;
        }
        print(result);
    }

}

