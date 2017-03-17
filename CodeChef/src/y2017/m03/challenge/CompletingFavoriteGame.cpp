// Calculate time to finish for each node and start hour starting from the leaves. Use cache to speedup calculation of permutations.
// https://www.codechef.com/MARCH17/problems/FAVGAME
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

#define MAX_N 1024
#define MAX_H 24
#define MAX_C 10
int n, h;
int tc[MAX_N];
vector<int> children[MAX_N];
int result[MAX_N][MAX_H];
int solveCache[MAX_N][1 << MAX_C][MAX_H];

int solve(int node, int level, int startTime, int used) {
    if (level == (int)children[node].size()) return 0;
    else {
        int hours = startTime % h;
        int res = solveCache[node][used][hours];
        if (res < 0) {
            res = MAX_N * MAX_H;
            FOR(i, children[node].size()) {
                if ((used & (1 << i)) == 0) {
                    int rl = result[children[node][i]][hours];
                    rl += solve(node, level + 1, startTime + rl, used | (1 << i));
                    if (rl < res) res = rl;
                }
            }
            solveCache[node][used][hours] = res;
        }
        return res;
    }
}

void getResult(int node, int startTime) {
    result[node][startTime] = tc[node] + solve(node, 0, startTime + tc[node], 0);
}

void solveNodeInternal(int node, int h1, int h2) {
    if (h2 - h1 > 1) {
        if (result[node][h1] + h1 == result[node][h2] + h2) {
            FORE(i, h1 + 1, h2) result[node][i] = result[node][h1] + h1 - i;
        } else {
            int mid = (h1 + h2) >> 1;
            getResult(node, mid);
            solveNodeInternal(node, h1, mid);
            solveNodeInternal(node, mid, h2);
        }
    }
}

void solveNode(int node) {
    FOR(i, children[node].size()) solveNode(children[node][i]);
    int e = h - tc[node];
    getResult(node, 0);
    getResult(node, e);
    solveNodeInternal(node, 0, e);
    FORE(i, e + 1, h) result[node][i] = result[node][0] + h - i;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        h = getInt();
        FOR(i, n) tc[i] = getInt();
        FOR(i, n) {
            int mm = getInt();
            children[i].clear();
            FOR(j, mm) children[i].push_back(getInt() - 1);
        }
        FOR(i, n) FOR(j, h) result[i][j] = -1;
        FOR(i, n) FOR(j, 1 << children[i].size()) FOR(k, h) solveCache[i][j][k] = -1;
        solveNode(0);
        print((result[0][0] - 1) / h + 1);
    }
}

