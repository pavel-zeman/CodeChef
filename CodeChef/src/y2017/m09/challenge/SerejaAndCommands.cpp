// Use segment tree to calculate total number of each operation of type 1 and then apply these operations using another segment tree
// https://www.codechef.com/SEPT17/problems/SEACO
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

#define INC 1
#define MAX_N 100010

struct Operation {
    int t;
    int l, r;
} operations[MAX_N];

int opTree[4 * MAX_N];
int aTree[4 * MAX_N];


int getOpCount(int node, int l, int r, int pos) {
    int res = 0;
    while (l != r) {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        res += opTree[node];
        if (res >= MOD) res -= MOD;
        if (pos <= middle) {
            node = childNode;
            r = middle;
        } else {
            node = childNode + 1;
            l = middle + 1;
        }
    }
    res += opTree[node];
    if (res >= MOD) res -= MOD;
    return res;
}

int getACount(int node, int l, int r, int pos) {
    int res = 0;
    while (l != r) {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        res += aTree[node];
        if (res >= MOD) res -= MOD;
        if (pos <= middle) {
            node = childNode;
            r = middle;
        } else {
            node = childNode + 1;
            l = middle + 1;
        }
    }
    res += aTree[node];
    if (res >= MOD) res -= MOD;
    return res;
}


void incrementA(int node, int l, int r, int tl, int tr, int c) {
    int middle = (l + r) >> 1;
    int childNode = node * 2 + 1;
    if (l >= tl && r <= tr) {
        aTree[node] += c;
        if (aTree[node] >= MOD) aTree[node] -= MOD;
    } else if (tr < l || tl > r) {
        // do nothing
    } else {
        incrementA(childNode, l, middle, tl, tr, c);
        incrementA(childNode + 1, middle + 1, r, tl, tr, c);
    }
}

void incrementOp(int node, int l, int r, int tl, int tr, int c) {
    int middle = (l + r) >> 1;
    int childNode = node * 2 + 1;
    if (l >= tl && r <= tr) {
        opTree[node] += c;
        if (opTree[node] >= MOD) opTree[node] -= MOD;
    } else if (tr < l || tl > r) {
        // do nothing
    } else {
        incrementOp(childNode, l, middle, tl, tr, c);
        incrementOp(childNode + 1, middle + 1, r, tl, tr, c);
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, 4 * m) opTree[i] = 0;
        FOR(i, 4 * n) aTree[i] = 0;
        FOR(i, m) {
            operations[i].t = getInt();
            operations[i].l = getInt() - 1;
            operations[i].r = getInt() - 1;
        }
        for(int i = m - 1; i >= 0; i--) {
            int c = getOpCount(0, 0, m - 1, i) + 1;
            if (operations[i].t == INC)
                incrementA(0, 0, n - 1, operations[i].l, operations[i].r, c);
            else
                incrementOp(0, 0, m - 1, operations[i].l, operations[i].r, c);
        }
        FOR(i, n) print(getACount(0, 0, n - 1, i));
    }
}

