// Segment tree with lazy propagation.
// http://www.codechef.com/JULY15/problems/ADDMUL
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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

void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_N 100010
#define MOD 1000000007


int n, q;
int aa[MAX_N];

struct Node {
    int sum;
    int toSet;
    int toAdd;
    int toMul;
    bool distribute;
} nodes[MAX_N * 3];


int buildTree(int node, int a, int b) {
    nodes[node].toSet = -1;
    nodes[node].toAdd = 0;
    nodes[node].toMul = 1;
    nodes[node].distribute = false;
    if (a == b) {
        nodes[node].sum = aa[a];
    } else {
        int m = (a + b) >> 1;
        nodes[node].sum = (buildTree(node * 2 + 1, a, m) + buildTree(node * 2 + 2, m + 1, b)) % MOD;
    }
    return nodes[node].sum;
}

int mul(int a, int b) {
    return ((long long int)a) * b % MOD;
}

int add(int a, int b) {
    return (a + b) % MOD;
}

void distribute(int node, int a, int b) {
    if (nodes[node].distribute) {
        if (a != b) {
            int c1 = node * 2 + 1;
            int c2 = node * 2 + 2;
            int m = (a + b) >> 1;
            if (nodes[node].toSet >= 0) {
                nodes[c1].sum = mul(nodes[node].toSet, m - a + 1);
                nodes[c2].sum = mul(nodes[node].toSet, b - m);
                nodes[c1].toSet = nodes[node].toSet;
                nodes[c2].toSet = nodes[node].toSet;

            } else {
                nodes[c1].sum = add(mul(nodes[c1].sum, nodes[node].toMul), mul(nodes[node].toAdd, m - a + 1));
                nodes[c2].sum = add(mul(nodes[c2].sum, nodes[node].toMul), mul(nodes[node].toAdd, b - m));

                if (nodes[c1].toSet >= 0) {
                    nodes[c1].toSet = add(mul(nodes[c1].toSet, nodes[node].toMul), nodes[node].toAdd);
                } else {
                    nodes[c1].toAdd = add(mul(nodes[c1].toAdd, nodes[node].toMul), nodes[node].toAdd);
                    nodes[c1].toMul = mul(nodes[c1].toMul, nodes[node].toMul);
                }
                if (nodes[c2].toSet >= 0) {
                    nodes[c2].toSet = add(mul(nodes[c2].toSet, nodes[node].toMul), nodes[node].toAdd);
                } else {
                    nodes[c2].toAdd = add(mul(nodes[c2].toAdd, nodes[node].toMul), nodes[node].toAdd);
                    nodes[c2].toMul = mul(nodes[c2].toMul, nodes[node].toMul);
                }
            }
            nodes[c1].distribute = true;
            nodes[c2].distribute = true;
        }

        nodes[node].distribute = false;
        nodes[node].toAdd = 0;
        nodes[node].toMul = 1;
        nodes[node].toSet = -1;
   }
}

int add(int node, int da, int db, int ca, int cb, int v) {
    if (db < ca || da > cb) return nodes[node].sum;
    if (ca >= da && cb <= db) {
        if (nodes[node].toSet >= 0) {
            nodes[node].toSet = add(nodes[node].toSet, v);
        } else {
            nodes[node].toAdd = add(nodes[node].toAdd, v);
        }
        nodes[node].sum = add(nodes[node].sum, mul(v, cb - ca + 1));
        nodes[node].distribute = true;
    } else {
        distribute(node, ca, cb);
        int m = (ca + cb) >> 1;
        nodes[node].sum = (add(node * 2 + 1, da, db, ca, m, v) + add(node * 2 + 2, da, db, m + 1, cb, v)) % MOD;
    }
    return nodes[node].sum;
}

int mul(int node, int da, int db, int ca, int cb, int v) {
    if (db < ca || da > cb) return nodes[node].sum;
    if (ca >= da && cb <= db) {
        if (nodes[node].toSet >= 0) {
            nodes[node].toSet = mul(nodes[node].toSet, v);
        } else {
            nodes[node].toAdd = mul(nodes[node].toAdd, v);
            nodes[node].toMul = mul(nodes[node].toMul, v);
        }
        nodes[node].sum = mul(nodes[node].sum, v);
        nodes[node].distribute = true;
    } else {
        distribute(node, ca, cb);
        int m = (ca + cb) >> 1;
        nodes[node].sum = (mul(node * 2 + 1, da, db, ca, m, v) + mul(node * 2 + 2, da, db, m + 1, cb, v)) % MOD;
    }
    return nodes[node].sum;
}


int set(int node, int da, int db, int ca, int cb, int v) {
    if (db < ca || da > cb) return nodes[node].sum;
    if (ca >= da && cb <= db) {
        nodes[node].toSet = v;
        nodes[node].toAdd = 0;
        nodes[node].toMul = 0;
        nodes[node].sum = mul(cb - ca + 1, v);
        nodes[node].distribute = true;
    } else {
        distribute(node, ca, cb);
        int m = (ca + cb) >> 1;
        nodes[node].sum = add(set(node * 2 + 1, da, db, ca, m, v), set(node * 2 + 2, da, db, m + 1, cb, v));
    }
    return nodes[node].sum;
}

int sum(int node, int da, int db, int ca, int cb) {
    if (db < ca || da > cb) return 0;
    if (ca >= da && cb <= db) {
        return nodes[node].sum;
    } else {
        distribute(node, ca, cb);
        int m = (ca + cb) >> 1;
        return (sum(node * 2 + 1, da, db, ca, m) + sum(node * 2 + 2, da, db, m + 1, cb)) % MOD;
    }
}


int main(void) {
    n = getInt();
    q = getInt();
    FOR(i, n) aa[i] = getInt();
    buildTree(0, 0, n - 1);
    FOR(i, q) {
        int op = getInt();
        int x = getInt() - 1;
        int y = getInt() - 1;
        int v;
        switch (op) {
            case 1: // add v
                v = getInt();
                add(0, x, y, 0, n - 1, v);
                break;

            case 2: // multiply by v
                v = getInt();
                mul(0, x, y, 0, n - 1, v);
                break;

            case 3: // set v
                v = getInt();
                set(0, x, y, 0, n - 1, v);
                break;

            case 4: // query sum
                print(sum(0, x, y, 0, n - 1));
                break;

        }

    }
}

