// Dynamic programming starting from the last turn and using sliding window maximum (running maximum) as described in https://people.cs.uct.ac.za/~ksmith/articles/sliding_window_minimum.html in each turn
// https://www.codechef.com/FEB17/problems/INTERVAL
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

#define MAX_N 300010
#define MAX_M 220
int n, m;
int a[MAX_N];
LLI sa[MAX_N];
int b[MAX_M];
LLI r1[MAX_N];
LLI r2[MAX_N];

LLI getSum(int x, int y) {
    return sa[y] - sa[x];
}


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
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        LLI s = 0;
        FOR(i, n) {
            sa[i] = s;
            s += a[i] = getInt();
        }
        sa[n] = s;
        FOR(i, m) b[i] = getInt();

        int fl = b[m - 1];
        FOR(i, n - fl + 1) r1[i] = getSum(i, i + fl);

        for(int i = m - 2; i >= 0; i--) {
            int ll = b[i];
            int ll2 = b[i + 1];
            window.reset();
            FORE(j, 1, ll - ll2 - 1) {
                while (!window.empty() && window.back() <= r1[j]) window.pop_back();
                window.push_back(make_pair(r1[j], j));
            }

            FOR(j, n - ll + 1) {
                int jj = j + ll - ll2 - 1;
                while (!window.empty() && window.back() <= r1[jj]) window.pop_back();
                window.push_back(make_pair(r1[jj], jj));
                while (window.frontSecond() <= j) window.pop_front();
                r2[j] = getSum(j, j + ll) - window.frontFirst();
            }
            memcpy(r1, r2, sizeof(LLI) * (n - ll + 1));
        }

        printf("%lld\n", *max_element(r1, r1 + n - b[0] + 1));
    }
}

