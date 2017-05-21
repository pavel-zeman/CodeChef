// Find sliding window total followed by sliding window maximum
// https://www.codechef.com/MAY17/problems/CHEFSUBA
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
int a[MAX_N];
int mx1[MAX_N];
int mx2[MAX_N];
char q[MAX_N];

class dd {
    pair<LLI, int> data[MAX_N];
    int first;
    int last;
public:
    dd() {
        first = 0;
        last = -1;
    }

    void reset() {
        first = 0;
        last = -1;
    }

    bool empty() {
        return last < first;
    }

    void pop_back() {
        last--;
    }

    void push_back(pair<LLI, int> d) {
        data[++last] = d;
    }

    LLI back() {
        return data[last].first;
    }

    void pop_front() {
        first++;
    }

    LLI frontFirst() {
        return data[first].first;
    }

    int frontSecond() {
        return data[first].second;
    }
} window;


int main(void) {
    int n = getInt();
    int k = getInt();
    k = min(k, n);
    int p = getInt();
    FOR(i, n) a[i] = getInt();
    int rm = 0;
    FOR(i, k) rm += a[i];
    FOR(i, n) {
        mx1[i] = rm;
        rm += a[(i + k) % n] - a[i];
    }
    int k1 = n - k + 1;
    window.reset();
    FOR(i, k1) {
        while (!window.empty() && window.back() <= mx1[i]) window.pop_back();
        window.push_back(make_pair(mx1[i], i));
    }
    FOR(i, n) {
        mx2[i] = window.frontFirst();
        while (!window.empty() && window.back() <= mx1[(i + k1) % n]) window.pop_back();
        window.push_back(make_pair(mx1[(i + k1) % n], i + k1));
        while (window.frontSecond() <= i) window.pop_front();
    }
    getString(q);
    int start = 0;
    FOR(i, p) {
        if (q[i] == '?') print(mx2[start]);
        else start = (start + n - 1) % n;
    }
}

