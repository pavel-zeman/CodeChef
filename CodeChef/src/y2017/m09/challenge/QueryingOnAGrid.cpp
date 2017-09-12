// Brute force approach for small data, segment tree for M=1
// https://www.codechef.com/SEPT17/problems/QGRID
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

#define MAX_M 3
#define MAX_N 100010
#define INF (1LL << 62)
LLI down[MAX_M][MAX_N];
LLI rr[MAX_M][MAX_N];
LLI weight[4 * MAX_N];
int n, m;
struct PathItem {
    int prevI, prevJ;
    LLI l;
    bool finished;
} path[MAX_M][MAX_N];


void incW(int node, int l, int r, int tl, int tr, LLI c) {
    int middle = (l + r) >> 1;
    int childNode = node * 2 + 1;
    if (l >= tl && r <= tr) {
        weight[node] += c;
    } else if (tr < l || tl > r) {
        // do nothing
    } else {
        incW(childNode, l, middle, tl, tr, c);
        incW(childNode + 1, middle + 1, r, tl, tr, c);
    }
}

LLI getW(int node, int l, int r, int pos) {
    LLI res = 0;
    while (l != r) {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        res += weight[node];
        if (pos <= middle) {
            node = childNode;
            r = middle;
        } else {
            node = childNode + 1;
            l = middle + 1;
        }
    }
    res += weight[node];
    return res;
}

void check(int i, int j, int pi, int pj, LLI l, set<pair<LLI, int> > & toVisit) {
    if (!path[i][j].finished) {
        if (path[i][j].l == INF) {
            path[i][j].l = l;
            path[i][j].prevI = pi;
            path[i][j].prevJ = pj;
            toVisit.insert(make_pair(l, i * n + j));
        } else if (path[i][j].l > l) {
            toVisit.erase(make_pair(path[i][j].l, i * n + j));
            path[i][j].l = l;
            path[i][j].prevI = pi;
            path[i][j].prevJ = pj;
            toVisit.insert(make_pair(l, i * n + j));
        }
    }
}

void incPath(int i1, int j1, int i2, int j2, LLI c) {
    set<pair<LLI, int> > toVisit;
    FOR(i, m) FOR(j, n) {
        path[i][j].finished = false;
        path[i][j].l = INF;
    }
    path[i1][j1].prevI = -1;
    path[i1][j1].l = 0;
    path[i1][j1].finished = false;

    toVisit.insert(make_pair(0, i1 * n + j1));
    while (true) {
        auto mm = toVisit.begin();
        int ic = mm->second / n;
        int jc = mm->second % n;
        toVisit.erase(mm);
        path[ic][jc].finished = true;
        if (ic == i2 && jc == j2) break;

        if (ic > 0) check(ic - 1, jc, ic, jc, path[ic][jc].l + down[ic - 1][jc], toVisit);
        if (ic < m - 1) check(ic + 1, jc, ic, jc, path[ic][jc].l + down[ic][jc], toVisit);
        if (jc > 0) check(ic, jc - 1, ic, jc, path[ic][jc].l + rr[ic][jc - 1], toVisit);
        if (jc < n - 1) check(ic, jc + 1, ic, jc, path[ic][jc].l + rr[ic][jc], toVisit);
    }

    int ic = i2;
    int jc = j2;
    weight[ic * n + jc] += c;
    while (ic != i1 || jc != j1) {
        int ic2 = path[ic][jc].prevI;
        int jc2 = path[ic][jc].prevJ;
        ic = ic2;
        jc = jc2;
        weight[ic * n + jc] += c;
    }
}


int main(void) {
    m = getInt();
    n = getInt();
    int q = getInt();
    FOR(i, m - 1) FOR(j, n) down[i][j] = getLongLongInt();
    FOR(i, m) FOR(j, n - 1) rr[i][j] = getLongLongInt();
    FOR(i, 4 * n) weight[i] = 0;

    FOR(i, q) {
        int op = getInt();
        int i1 = getInt() - 1;
        int j1 = getInt() - 1;
        int i2 = -1, j2 = -1;
        LLI c = -1;
        if (op == 1) {
            i2 = getInt() - 1;
            j2 = getInt() - 1;
            c = getLongLongInt();
        }
        if (m == 1) {
            switch (op) {
            case 1:
                incW(0, 0, n - 1, min(j1, j2), max(j1, j2), c);
                break;
            case 2:
                print(getW(0, 0, n - 1, j1));
                break;
            }
        } else if (n <= 1000) {
            switch (op) {
            case 1:
                incPath(i1, j1, i2, j2, c);
                break;
            case 2:
                print(weight[i1 * n + j1]);
                break;
            }
        }
    }
}

