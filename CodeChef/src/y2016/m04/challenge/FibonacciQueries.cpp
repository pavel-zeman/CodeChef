// Segment tree with segments A and B aggregated using A * (1 + F * B) + B, where A and B are matrices and F is "unit" Fibonacci matrix ((1, 1), (1, 0)).
// https://www.codechef.com/APRIL16/problems/FIBQ
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
    while (!(ccc > 'A' && ccc <= 'Z')) ccc = getc_unlocked(stdin);
    while (ccc > 'A' && ccc <= 'Z') {
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

#define MAX_N 270000
int a[MAX_N];

struct Matrix {
    int v[2][2];

    void mul(Matrix &other) {
        Matrix temp;
        FOR(i, 2) FOR(j, 2) temp.v[i][j] = (v[i][0] * (LLI)other.v[0][j] + v[i][1] * (LLI)other.v[1][j]) % MOD;
        memcpy(v, temp.v, sizeof(v));
    }

    void mulAddFib() {
        Matrix temp;
        temp.v[0][0] = (v[0][0] + v[0][1] + 1) % MOD;
        temp.v[0][1] = v[0][0];
        temp.v[1][0] = (v[1][0] + v[1][1]) % MOD;
        temp.v[1][1] = (v[1][0] + 1) % MOD;
        memcpy(v, temp.v, sizeof(v));
    }

    void add(Matrix &other) {
        FOR(i, 2) FOR(j, 2) v[i][j] = (v[i][j] + other.v[i][j]) % MOD;
    }

};


Matrix unitMatrix;
Matrix zeroMatrix;
Matrix fibUnitMatrix;
Matrix tree[MAX_N];
int n;

Matrix power(Matrix a, int b) {
    Matrix sq = a;
    Matrix result = unitMatrix;
    while (b > 0) {
        if ((b & 1) == 1) result.mul(sq);
        sq.mul(sq);
        b >>= 1;
    }
    return result;
}

void buildTree(int node, int l, int r) {
    if (l == r) {
        tree[node] = power(fibUnitMatrix, a[l] - 1);
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        buildTree(childNode, l, middle);
        buildTree(childNode + 1, middle + 1, r);
        Matrix temp = tree[childNode + 1];
        temp.mulAddFib();
        tree[node] = tree[childNode];
        tree[node].mul(temp);
        tree[node].add(tree[childNode + 1]);
    }
}

Matrix gatherResult(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return zeroMatrix;
    else {
        if (l >= start && r <= end) return tree[node];
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        if (start > middle) return gatherResult(childNode + 1, middle + 1, r, start, end);
        if (end <= middle) return gatherResult(childNode, l, middle, start, end);
        Matrix a = gatherResult(childNode, l, middle, start, end);
        Matrix b = gatherResult(childNode + 1, middle + 1, r, start, end);
        Matrix temp = b;
        temp.mulAddFib();
        a.mul(temp);
        a.add(b);
        return a;
    }
}

void updateTree(int node, int l, int r, int pos) {
    if (pos < l || pos > r) return;
    if (l == r) {
        tree[node] = power(fibUnitMatrix, a[l] - 1);
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        updateTree(childNode, l, middle, pos);
        updateTree(childNode + 1, middle + 1, r, pos);
        Matrix temp = tree[childNode + 1];
        temp.mulAddFib();
        tree[node] = tree[childNode];
        tree[node].mul(temp);
        tree[node].add(tree[childNode + 1]);
    }
}

int calc(int l, int r) {
    return gatherResult(0, 0, n - 1, l, r).v[0][0];
}



int main(void) {
    unitMatrix.v[0][0] = unitMatrix.v[1][1] = 1;
    fibUnitMatrix.v[0][0] = fibUnitMatrix.v[0][1] = fibUnitMatrix.v[1][0] = 1;
    n = getInt();
    int m = getInt();
    FOR(i, n) a[i] = getInt();
    buildTree(0, 0, n - 1);

    FOR(i, m) {
        char type[10];
        getString(type);
        int l = getInt();
        int r = getInt();
        switch (type[0]) {
        case 'Q':
            print(calc(l - 1, r - 1));
            break;
        case 'C':
            a[l - 1] = r;
            updateTree(0, 0, n - 1, l - 1);
            break;
        }
    }
}

