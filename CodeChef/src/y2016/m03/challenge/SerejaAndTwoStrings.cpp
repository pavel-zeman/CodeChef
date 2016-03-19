// The result is total number of permutations of s multiplied by total number of non-similar strings (these can be calculated as total number of string minus number of similar strings)
// https://www.codechef.com/MARCH16/problems/SEATSTR2
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
#define MAX_CHARS 26
char data[MAX_N];
int c[MAX_CHARS];
int fact[MAX_N];
int l;

int main(void) {
    fact[0] = 1;
    FORE(i, 1, MAX_N) fact[i] = fact[i - 1] * (LLI)i % MOD;
    int t = getInt();
    FOR(tt, t) {
        l = getString(data);
        FOR(i, MAX_CHARS) c[i] = 0;
        FOR(i, l) c[data[i] - 'a']++;

        int total = fact[l];
        FOR(i, MAX_CHARS) total = total * (LLI)inv(fact[c[i]]) % MOD;
        int invalid = 1;
        FOR(i, MAX_CHARS) FORE(j, i + 1, MAX_CHARS) invalid = (invalid + c[i] * (LLI)c[j]) % MOD;

        FOR(i, MAX_CHARS) FORE(j, i + 1, MAX_CHARS) {
            int cij = c[i] * (LLI)c[j] % MOD;
            FORE(k, i, MAX_CHARS) FORE(l, k + 1, MAX_CHARS) {
                int temp = 0;
                if (i == k && j == l) {
                    temp = (LLI)c[i] * (c[i] - 1) / 2 % MOD;
                    temp = temp * ((LLI)c[j] * (c[j] - 1) / 2 % MOD) % MOD;
                } else if (i == k) {
                    temp = ((LLI)c[i] * (c[i] - 1) / 2) % MOD * c[j] % MOD * c[l] % MOD;
                } else if (j == l) {
                    temp = ((LLI)c[j] * (c[j] - 1)) % MOD * c[i] % MOD * c[k] % MOD;
                } else if (j == k) {
                    temp = ((LLI)c[j] * (c[j] - 1)) % MOD * c[i] % MOD * c[l] % MOD;
                } else {
                    temp = cij * (LLI)c[k] % MOD * c[l] % MOD;
                }
                invalid = (invalid + temp) % MOD;
            }
        }
        FOR(i, MAX_CHARS) FORE(j, i + 1, MAX_CHARS) {
            int sum = 0;
            FORE(k, j + 1, MAX_CHARS) sum += c[k];
            sum *= 2;
            invalid += c[i] * (LLI)c[j] % MOD * sum % MOD;
            invalid %= MOD;
        }
        invalid = (total - invalid + MOD) % MOD;
        int result = total * (LLI)invalid % MOD;
        print(result);
    }
}

