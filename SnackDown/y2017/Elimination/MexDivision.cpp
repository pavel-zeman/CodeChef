// Description
// https://www.codechef.com/SNCKEL17/problems/MEXDIV
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

#define MAX_N 500010
int a[MAX_N];
int res[MAX_N];
int used[MAX_N];
int sumRes[MAX_N];

int main(void) {
    int n = getInt();
    int k = getInt() + 1;
    if (k > n + 1) k = n + 1;
    FOR(i, n) a[i] = getInt();
    sumRes[n] = sumRes[n + 1] = 0;
    FOR(j, k) used[j] = 0;
    int totalUsed = 0;
    int lastIndex = n - 1;
    for(int i = n - 1; i >= 0; i--) {
        if (k == 1 && a[i] == 0) {
            res[0] = 0;
            break;
        }
        if (a[i] < k) {
            used[a[i]]++;
            if (used[a[i]] == 1) totalUsed++;
        }
        while (totalUsed == k) {
            if (a[lastIndex] < k) {
                used[a[lastIndex]]--;
                if (used[a[lastIndex]] == 0) totalUsed--;
            }
            lastIndex--;
        }
        res[i] = (sumRes[i + 1] - sumRes[lastIndex + 2]) % MOD;
        if (lastIndex == n - 1) res[i] = (res[i] + 1) % MOD;
        if (res[i] < 0) res[i] += MOD;
        sumRes[i] = (res[i] + sumRes[i + 1]) % MOD;
        //printf("%d = %d, %d %d\n", i, lastIndex, res[i], sumRes[i]);
    }
    print(res[0]);
}

