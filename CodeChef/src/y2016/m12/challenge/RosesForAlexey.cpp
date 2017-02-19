// Try to find maximum number of savings, i.e. roses, that need not be cut. Use dynamic programming on a histogram of roses lengths.
// https://www.codechef.com/DEC16/problems/ALEXROSE
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

#define MAX_N 100010

LLI a[MAX_N];
int counts[MAX_N];
int totalV;
map<pair<int, int>, int> cache;
int n, k;


int findMax(int pos, int remain) {
    if (pos == totalV) return 0;
    map<pair<int, int>, int>::iterator it = cache.find(make_pair(pos, remain));
    if (it != cache.end()) return it->second;
    int result = 0;
    if (counts[pos] == 1 || remain < k - counts[pos]) result = findMax(pos + 1, remain + counts[pos]);
    else {
        if (remain < 32 * k) result = findMax(pos + 1, remain + counts[pos]);
        int result2 = findMax(pos + 1, remain - (k - counts[pos])) + counts[pos] - 1;
        if (result2 > result) result = result2;
    }
    cache[make_pair(pos, remain)] = result;
    return result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        FOR(i, n) a[i] = -getLongLongInt();
        sort(a, a + n);
        LLI lastV = a[0];
        int cc = 0;
        totalV = 0;
        int totalSave = 0;
        FOR(i, n) {
            if (a[i] != lastV) {
                totalSave += cc / k * (k - 1);
                cc %= k;
                if (cc > 0) counts[totalV++] = cc;
                cc = 0;
                lastV = a[i];
            }
            cc++;
        }
        totalSave += cc / k * (k - 1);
        cc %= k;
        if (cc > 0) counts[totalV++] = cc;

        cache.clear();
        totalSave += findMax(0, 0);
        print(n / k * (k - 1) - totalSave);
    }
}

