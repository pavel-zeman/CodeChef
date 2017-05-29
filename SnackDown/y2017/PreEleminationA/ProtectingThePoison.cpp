// Greedy algorithm for interval cover for both horizontal and vertical directions
// https://www.codechef.com/SNCKPA17/problems/PROTEPOI
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


vector<pair<int, int> > hor, vert;
int n, k, m, k1, k2;

int solve(vector<pair<int, int> > & v) {
    int cv = k1;
    int res = 0;
    auto it = v.begin();
    while (it != v.end() && cv <= k2) {
        int maxEnd = -1;
        while (it != v.end() && it->first <= cv) {
            maxEnd = max(maxEnd, it->second);
            it++;
        }
        if (maxEnd == -1) return -1;
        res++;
        cv = maxEnd + 1;
    }
    return cv > k2 ? res : -1;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        hor.clear();
        vert.clear();
        n = getInt();
        k = getInt();
        m = getInt();
        k1 = (n - k) >> 1;
        k2 = k1 + k - 1;
        FOR(i, m) {
            int x1 = getInt() - 1;
            int y1 = getInt() - 1;
            int x2 = getInt() - 1;
            int y2 = getInt() - 1;
            if (!(x2 < k1 || x1 > k2)) {
                vert.push_back(make_pair(min(x1, x2), max(x1, x2)));
            } else if (!(y2 < k1 || y1 > k2)) {
                hor.push_back(make_pair(min(y1, y2), max(y1, y2)));
            }
        }
        sort(hor.begin(), hor.end());
        sort(vert.begin(), vert.end());
        int r1 = solve(vert);
        int r2 = solve(hor);
        print(r1 < 0 || r2 < 0 ? -1 : r1 + r2);
    }
}

