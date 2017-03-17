// Use Sprague-Grundy theorem to transform the game to Nim and then use segment tree for queries and updates.
// https://www.codechef.com/MARCH17/problems/PSHTBRTH
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

#define MAX_N 100010
int grundy[1 << 16];
int maxg;
int a[MAX_N];

int calcGrundy(int a) {
    int result = grundy[a];
    if (result < 0) {
        bool used[16];
        FOR(i, 16) used[i] = false;
        FOR(i, 4) FOR(j, 4) if ((a & (1 << (i * 4 + j))) != 0) {
            FOR(k, 4 - j) {
                int line = 0;
                FOR(l, k + 1) {
                    line <<= 1;
                    line = line | 1;
                }
                line <<= j;
                int rect = 0;
                FOR(l, 4 - i) {
                    rect |= line << ((i + l) * 4);
                    if ((a & rect) == rect)
                        used[calcGrundy(a & ~rect)] = true;
                    else break;
                }
            }
        }
        int i = 0;
        while (used[i] && i < 16) i++;
        result = grundy[a] = i;
        if (result > maxg) maxg = result;
    }
    return result;
}


int readMatrix() {
    char line[5];
    int aa = 0;
    int ii = 0;
    FOR(j, 4) {
        getString(line);
        FOR(k, 4) {
            aa |= (line[k] - '0') << ii;
            ii++;
        }
    }
    return grundy[aa];
}


int tree[3 * MAX_N];
int buildTree(int node, int l, int r) {
    if (l == r) {
        tree[node] = a[l];
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        int res1 = buildTree(childNode, l, middle);
        int res2 = buildTree(childNode + 1, middle + 1, r);
        tree[node] = res1 ^ res2;
    }
    return tree[node];
}

int gatherResult(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return 0;
    else {
        if (l >= start && r <= end) return tree[node];
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        int res1 = gatherResult(childNode, l, middle, start, end);
        int res2 = gatherResult(childNode + 1, middle + 1, r, start, end);
        return res1 ^ res2;
    }
}

int updateTree(int node, int l, int r, int pos) {
    if (pos < l || pos > r) return tree[node];
    if (l == r) {
        tree[node] = a[pos];
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        int res1 = updateTree(childNode, l, middle, pos);
        int res2 = updateTree(childNode + 1, middle + 1, r, pos);
        tree[node] = res1 ^ res2;
    }
    return tree[node];
}




int main(void) {
    FOR(i, 1 << 16) grundy[i] = -1;
    grundy[0] = 0;
    FOR(i, 1 << 16) calcGrundy(i);

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n) a[i] = readMatrix();
        buildTree(0, 0, n - 1);
        FOR(i, m) {
            int op = getInt();
            int l = getInt() - 1;
            if (op == 1) {
                // find winner
                int r = getInt() - 1;
                int res = gatherResult(0, 0, n - 1, l, r);
                printString(res == 0 ? "Lotsy" : "Pishty");
            } else {
                // update
                a[l] = readMatrix();
                updateTree(0, 0, n - 1, l);
            }
        }
    }
}

