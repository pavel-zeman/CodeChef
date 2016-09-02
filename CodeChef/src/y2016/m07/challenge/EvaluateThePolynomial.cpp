// Use NTT to calculate polynomial value for all root ^ (0 .. MOD - 2).
// https://www.codechef.com/JULY16/problems/POLYEVAL
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 786433


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

#define ROOT 10

void calc(vector<int> &a, int w) {
    int n = a.size();
    if (n == 1) {
        // do nothing
    } else if ((n & 1) == 1) {
        vector<int> res;
        res.resize(n);
        FOR(i, n) {
            LLI t = 0;
            FOR(j, n) t += a[j] * (LLI)power(w, i * j);
            res[i] = t % MOD;
        }
        FOR(i, n) a[i] = res[i];
    } else {
        int n2 = n >> 1;
        vector<int> even;
        vector<int> odd;
        even.reserve(n2);
        odd.reserve(n2);

        FOR(i, n) if ((i & 1) == 0) even.push_back(a[i]); else odd.push_back(a[i]);
        calc(even, w * (LLI)w % MOD);
        calc(odd, w * (LLI)w % MOD);
        int w1 = 1;
        int w2 = power(w, n2);
        FOR(i, n2) {
            a[i] = (even[i] + w1 * (LLI)odd[i]) % MOD;
            a[i + n2] = (even[i] + w2 * (LLI)odd[i]) % MOD;
            w1 = w1 * (LLI)w % MOD;
            w2 = w2 * (LLI)w % MOD;
        }
    }
}

int preCalc[MOD];

int main(void) {
    vector<int> a;
    int n = getInt() + 1;
    a.resize(MOD - 1);
    FOR(i, n) a[i] = getInt();
    FORE(i, n, MOD - 1) a[i] = 0;
    preCalc[0] = a[0];

    calc(a, ROOT);

    int w = 1;
    FOR(i, a.size()) {
        preCalc[w] = a[i];
        w = w * ROOT % MOD;
    }

    int q = getInt();
    FOR(i, q) print(preCalc[getInt()]);
}

