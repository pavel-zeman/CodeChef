// Pre-calculate all primes up to 1 million, use the to factorize all the numbers between A and B and then use the factorization to calculate the total score.
// https://www.codechef.com/APRIL17/problems/CHEFDIV
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

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MAX_P 1000010
#define MAX_D 100010
#define MAX_SD 40
bool prime[MAX_P];
vector<LLI> divisors[MAX_D];
int cd[MAX_SD];

int calc(int s) {
    int result = 0;
    while (true) {
        int rr = 1;
        FOR(i, s) rr *= cd[i] + 1;
        result += rr;
        int pos = max_element(cd, cd + s) - cd;
        if (cd[pos] == 0) break;
        cd[pos]--;
    }
    return result - 1;
}

int main(void) {
    FOR(i, MAX_P) prime[i] = true;
    FORE(i, 2, MAX_P)
        if (prime[i])
            for(int j = i + i; j < MAX_P; j += i) prime[j] = false;
    LLI a = getLongLongInt();
    LLI b = getLongLongInt();
    int d = b - a;
    for(int i = 2; i * (LLI)i <= b; i++) if (prime[i]) {
        int m = a % i;
        LLI s = m == 0 ? a : a + (i - m);
        for(int j = s - a; j <= d; j += i) divisors[j].push_back(i);
    }

    int result = 0;
    FOR(i, d + 1) {
        LLI x = a + i;
        int cdc = 0;
        FOR(j, divisors[i].size()) {
            int c = 0;
            while (x % divisors[i][j] == 0) { x /= divisors[i][j]; c++; }
            cd[cdc++] = c;
        }
        if (x > 1) cd[cdc++] = 1;
        result += calc(cdc);
    }
    print(result);
}

