// Description
// https://www.codechef.com/SNCKEL17/problems/CHEFPRAD
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

#define MAX_N 256
pair<int, int> ints[256][256];
int c[MAX_N];
int d[MAX_N];


bool intersect(const pair<int, int> &p1, const pair<int, int> &p2) {
    return !(p1.second < p2.first || p1.first > p2.second);
}

pair<int, int> intersection(const pair<int, int> &p1, const pair<int, int> &p2) {
    return make_pair(max(p1.first, p2.first), min(p1.second, p2.second));
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        int e = getInt();
        FOR(i, n) c[i] = getInt();
        FOR(i, m) d[i] = getInt();
        sort(c, c + n);
        sort(d, d + m);
        FOR(i, n) FOR(j, m) {
            ints[i][j].first = -(c[i] - (d[j] - e));
            ints[i][j].second = (d[j] + e) - c[i];
        }
        int res = 0;
        FOR(i, m) {
            pair<int, int> ci = make_pair(-2000000000, 2000000000);
            int first = i;
            int rt = 0;
            FOR(j, n) {
                if (intersect(ci, ints[j][first])) {
                    rt++;
                    ci = intersection(ci, ints[j][first]);
                    first++;
                } else {
                    while (ints[j][first].second < ci.first && first < m) first++;
                    if (first < m && intersect(ci, ints[j][first])) {
                        rt++;
                        ci = intersection(ci, ints[j][first]);
                        first++;
                    }
                    if (first == m) break;
                }
            }
            if (rt > res) res = rt;
        }
        print(res);
    }
}

