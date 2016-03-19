// Based on the idea from https://discuss.codechef.com/questions/27355/pptree-editorial - each assignment of weights to edges corresponds to an assignment of binary numbers to nodes and we calculate number of valid assignments to nodes.
// https://www.codechef.com/MARCH16/problems/PARITREE
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 100010
int root[MAX_N];
int depth[MAX_N];
int bit[MAX_N];
int opposite[MAX_N];


int findRoot(int a) {
    while (root[a] != a) a = root[a];
    return a;
}

int join(int a, int b) {
    if (bit[a] >= 0 && bit[b] < 0) bit[b] = bit[a];
    else if (bit[b] >= 0 && bit[a] < 0) bit[a] = bit[b];
    if (depth[a] < depth[b]) root[a] = b;
    else if (depth[b] < depth[a]) root[b] = a;
    else {
        root[a] = b;
        depth[b]++;
    }
    return root[a];
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int q = getInt();
        FOR(i, n) {
            root[i] = i;
            bit[i] = -1;
            depth[i] = 1;
        }
        FOR(i, n - 1) {
            getInt();
            getInt();
        }
        bool ok = true;
        FOR(i, q) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            int b = getInt();
            int ru = findRoot(u);
            int rv = findRoot(v);
            if (b == 0) {
                if (ru != rv) {
                    if (bit[ru] < 0) {
                        ru = join(ru, rv);
                        if (bit[rv] < 0) {
                            // nothing
                        } else {
                            int origOpposite = opposite[rv];
                            opposite[ru] = origOpposite;
                            opposite[origOpposite] = ru;
                        }
                    } else {
                        int origOppositeU = opposite[ru];
                        if (bit[rv] < 0) {
                            ru = join(ru, rv);
                        } else {
                            if (opposite[ru] == rv) ok = false;
                            else {
                                ru = join(ru, rv);
                                origOppositeU = join(origOppositeU, opposite[rv]);
                                bit[ru] = 0;
                                bit[origOppositeU] = 1;
                            }
                        }
                        opposite[ru] = origOppositeU;
                        opposite[origOppositeU] = ru;
                    }
                }
            } else {
                if (ru == rv) ok = false;
                else {
                    if (bit[ru] < 0) {
                        if (bit[rv] < 0) {
                            bit[ru] = 0;
                            bit[rv] = 1;
                        } else {
                            ru = join(ru, opposite[rv]);
                        }
                    } else {
                        if (bit[rv] >= 0) {
                            if (opposite[ru] == rv) {
                                // nothing
                            } else {
                                int origOppositeU = opposite[ru];
                                int origOppositev = opposite[rv];
                                ru = join(ru, origOppositev);
                                rv = join(rv, origOppositeU);
                                bit[ru] = 0;
                                bit[rv] = 1;
                            }
                        } else {
                            rv = join(rv, opposite[ru]);
                        }
                    }
                    opposite[ru] = rv;
                    opposite[rv] = ru;
                }
            }
        }
        if (!ok) {
            puts("0\n");
        } else {
            int result = 500000004; // 1/2 mod MOD
            FOR(i, n) {
                int r = findRoot(i);
                if (r == i && bit[r] <= 0) result = result * 2 % MOD;
            }
            print(result);
        }
    }
}

