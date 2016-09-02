// Solves just the simple version using formulas found at OEIS
// https://www.codechef.com/JULY16/problems/CHEFPOL
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

LLI power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

LLI inv(int a) {
    return power(a, MOD - 2);
}

void fail() {
    *((char *)0) = 0;
}


int main(void) {
    int nn = getInt();
    int c = getInt();
    LLI result = 0;
    switch (nn) {
    case 4: // tetrahedron
        c += 3;
        result = ((LLI)c) * (c - 1) % MOD * (c - 2) % MOD * (c - 3) % MOD * inv(24) % MOD;
        break;
    case 6: // cube
        result = (power(c, 2) * inv(3) % MOD + power(c, 3) * inv(2) % MOD + power(c, 4) * inv(8) % MOD + power(c, 6) * inv(24) % MOD) % MOD;
        break;
    case 8: // octahedron
        result = (power(c, 2) * 20 % MOD + power(c, 4) * 21 % MOD + power(c, 6) * 6 % MOD + power(c, 8)) % MOD * inv(48) % MOD;
        break;
    case 12: // dodecahedron
        result = power(c, 2) * (power(c, 2) + 1) % MOD * ((power(c, 8) - power(c, 6) + power(c, 4) * 16 % MOD + 44) % MOD) % MOD * inv(120) % MOD;
        break;
    case 20: // icosahedron
        result = power(c, 2) * (power(c, 18) + power(c, 10) * 15 % MOD + power(c, 8) * 16 % MOD + power(c, 6) * 20 % MOD + power(c, 2) * 44 % MOD + 24) % MOD * inv(120) % MOD;
        break;
    default:
        return 1;
    }
    print(result);
    return 0;
}

