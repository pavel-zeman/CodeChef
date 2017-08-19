// Use sqrt decomposition to compare, if sub-arrays are the same. If they are not, use brute force just for the (up to 2) blocks of the sqrt size.
// https://www.codechef.com/JUNE17/problems/CLONEME
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

#define MAX_N 100011
#define MAX_SQRT 320
#define MAX_A 100011
int aa[MAX_N];
vector<int> positions[MAX_A];
int totals[MAX_SQRT][MAX_N];
int sqrtItem, sqrts;
int pows[MAX_N];


int getTotal(int from, int to, int v) {
    auto first = lower_bound(positions[v].begin(), positions[v].end(), from);
    auto last = upper_bound(first, positions[v].end(), to);
    return distance(first, last);
}

int getModTotal(int from, int to, int v) {
    int res = totals[v][to];
    if (from > 0) {
        res -= totals[v][from - 1];
        if (res < 0) res += MOD;
    }
    return res;
}

int main(void) {
    pows[0] = 1;
    FORE(i, 1, MAX_N) pows[i] = pows[i - 1] * (LLI)MAX_N % MOD;
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int q = getInt();
        FOR(i, n) aa[i] = getInt();
        int maxv = *max_element(aa, aa + n);
        sqrtItem = sqrt(maxv);
        sqrts = maxv / sqrtItem + 1;
        FOR(i, sqrts) FOR(j, n) totals[i][j] = 0;
        FOR(i, n) {
            int j = aa[i] / sqrtItem;
            totals[j][i] = (totals[j][i] + pows[aa[i]]) % MOD;
        }
        FOR(i, sqrts) FORE(j, 1, n) totals[i][j] += totals[i][j - 1];
        FOR(j, MAX_A) positions[j].clear();
        FOR(i, n) positions[aa[i]].push_back(i);

        FOR(i, q) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            int c = getInt() - 1;
            int d = getInt() - 1;
            bool ok = true;
            int nextDiff = 0;
            int firstDiff = -1;
            int lastDiff = -1;
            FOR(j, sqrts) {
                int t1 = getModTotal(a, b, j);
                int t2 = getModTotal(c, d, j);
                if (t1 != 0 || t2 != 0) {
                    switch (nextDiff) {
                        case 0:
                            if (t1 != t2) {
                                nextDiff = 1;
                                firstDiff = j;
                            }
                            break;
                        case 1:
                            if (t1 != t2) lastDiff = j;
                            nextDiff = 2;
                            break;
                        case 2:
                            if (t1 != t2) { ok = false; goto e2;}
                            break;
                    }
                }
            }
            if (firstDiff >= 0) {
                nextDiff = 0;
                int diff = 0;
                FORE(j, firstDiff * sqrtItem, firstDiff * sqrtItem + sqrtItem) if (j <= maxv) {
                    int t1 = getTotal(a, b, j);
                    int t2 = getTotal(c, d, j);
                    if (t1 != 0 || t2 != 0) {
                        int t3 = t1 - t2;
                        if (abs(t3) > 1) { ok = false; goto e2;}
                        switch (nextDiff) {
                            case 0:
                                if (t3) { diff = t3; nextDiff = 1; }
                                break;
                            case 1:
                                if (diff + t3 != 0) { ok = false; goto e2;}
                                nextDiff = 2;
                                break;
                            case 2:
                                if (t3) { ok = false; goto e2;}
                                break;
                        }
                    }
                }
                if (lastDiff >= 0) {
                    FORE(j, lastDiff * sqrtItem, lastDiff * sqrtItem + sqrtItem) if (j <= maxv) {
                        int t1 = getTotal(a, b, j);
                        int t2 = getTotal(c, d, j);
                        if (t1 != 0 || t2 != 0) {
                            int t3 = t1 - t2;
                            if (abs(t3) > 1) { ok = false; goto e2;}
                            switch (nextDiff) {
                                case 0:
                                    if (t3) { diff = t3; nextDiff = 1; }
                                    break;
                                case 1:
                                    if (diff + t3 != 0) { ok = false; goto e2;}
                                    nextDiff = 2;
                                    break;
                                case 2:
                                    if (t3) { ok = false; goto e2;}
                                    break;
                            }
                        }
                    }
                }
                if (nextDiff == 1) ok = false;
            }

            e2:
            printString(ok ? "YES" : "NO");
        }
    }
}

