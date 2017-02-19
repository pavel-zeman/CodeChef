// Just brute force solution for the smallest subtask
// https://www.codechef.com/OCT16/problems/TREEBAL
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

#define MAX_N 200010
struct Edge {
    int c;
    int d;
    int target;

    Edge(int c, int d, int target) {
        this->c = c;
        this->d = d;
        this->target = target;
    }
};

vector<Edge> neighbors[MAX_N];


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) neighbors[i].clear();
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            int c = getInt();
            int d = getInt();
            neighbors[u].push_back(Edge(c, d, v));
            neighbors[v].push_back(Edge(c, d, u));
        }
        if (n <= 200 && (int)neighbors[0].size() == n - 1) {
            int rc = 0;
            LLI m = (LLI)n * 1000000 * 1000000;
            FORE(i, 1, 1000000) {
                LLI lm = 0;
                FOR(j, n - 1) lm += abs(neighbors[0][j].c - i) * (LLI)neighbors[0][j].d;
                if (lm < m) {
                    m = lm;
                    rc = i;
                }
            }
            print(m);
            FOR(i, n - 1) print(rc);
        }
    }
}

