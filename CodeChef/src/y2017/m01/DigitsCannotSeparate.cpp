// Check each possible first number, calculate all its divisors and use DP to check, whether there is a placement of separators so that the divisor is the GCD.
// https://www.codechef.com/JAN17/problems/DIGITSEP
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

#define MAX_N 310
#define MAX_P 100010
int n;
char s[MAX_N];
int m, x, y;
char prime[MAX_P];
int primes[10000];
int primeCount;
int leadingZeros;
LLI result;
char isPossible[MAX_N][MAX_N];

int inputPrimesCount;
struct Prime {
    LLI value;
    int count;
} inputPrimes[20];


LLI getNumber(int pos, int length) {
    LLI result = 0;
    FOR(i, length) result = result * 10 + s[i + pos];
    return result;
}

void calcPrimes(LLI v) {
    inputPrimesCount = 0;
    FOR(i, primeCount) {
        if (v % primes[i] == 0) {
            int cc = 0;
            while (v % primes[i] == 0) {
                v /= primes[i];
                cc++;
            }
            inputPrimes[inputPrimesCount].value = primes[i];
            inputPrimes[inputPrimesCount++].count = cc;
        }
        if (primes[i] * (LLI)primes[i] > v) break;
    }
    if (v > 1) {
        inputPrimes[inputPrimesCount].value = v;
        inputPrimes[inputPrimesCount++].count = 1;
    }
}

LLI testDivisor;

char check(int startPos, int remainingSeparators) {
    char res = isPossible[startPos][remainingSeparators];
    if (res < 0) {
        if (remainingSeparators == 0) res = startPos < n && n - startPos <= m && getNumber(startPos, n - startPos) % testDivisor == 0;
        else if (startPos == n) res = false;
        else {
            LLI num = 0;
            res = false;
            FOR(i, m) {
                if (startPos + i <= n) {
                    num = num * 10 + s[i + startPos];
                    if (num % testDivisor == 0 && check(startPos + i + 1, remainingSeparators - 1)) {
                        res = true;
                        break;
                    }
                }
            }
        }
        isPossible[startPos][remainingSeparators] = res;
    }
    return res;
}


void generateDivisors(int level, LLI mult, int initialDigits) {
    if (level == inputPrimesCount) {
        if (mult > result) {
            int start = max(x - leadingZeros - 1, 0);
            int end = y - (initialDigits + leadingZeros + m - 1) / m;
            if (end >= 0) {
                testDivisor = mult;
                FOR(i, n + 1) FOR(j, n + 1) isPossible[i][j] = -1;
                FORE(i, start, end + 1) {
                    if (check(leadingZeros + initialDigits, i)) {
                        result = mult;
                        break;
                    }
                }
            }
        }
    } else {
        FOR(i, inputPrimes[level].count + 1) {
            generateDivisors(level + 1, mult, initialDigits);
            mult *= inputPrimes[level].value;
        }
    }
}

int main(void) {
    memset(prime, 1, sizeof(prime));
    prime[0] = prime[1] = false;
    FORE(i, 2, MAX_P)
        if (prime[i]) {
            primes[primeCount++] = i;
            for(int j = i + i; j < MAX_P; j += i) prime[j] = false;
        }

    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        getString(s);
        FOR(i, n) s[i] -= '0';
        m = getInt();
        x = getInt();
        y = getInt();
        leadingZeros = 0;
        while (s[leadingZeros] == 0 && leadingZeros < n) leadingZeros++;

        if (leadingZeros == n) result = 0; else {
            result = 1;
            FOR(i, m) {
                if (leadingZeros + i <= n) {
                    LLI num = getNumber(leadingZeros, i + 1);
                    calcPrimes(num);
                    if (inputPrimesCount > 0) generateDivisors(0, 1, i + 1);
                }
            }
        }
        print(result);
    }
}

