// Recursively memoize the results for each node and its 2 parents. Special attention must be paid to a case, when a coin is move from grand-child (not child).
// https://www.codechef.com/JULY17/problems/TWOCOINS
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define FOREACH(i, v) for(auto i=(v).begin(); i != (v).end(); i++)
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
#define INF 1000000
int n;
vector<int> children[MAX_N];
// parent-parent, parent, this node
int result[MAX_N][2][2][2];
int atLeastOne[MAX_N];

void calcZeroCoins(int node) {
    if (children[node].empty()) {
        FOR(i, 2) FOR(j, 2) result[node][i][j][0] = INF;
    } else {
        FOR(parent, 2) {
            int total = 0;
            FOREACH(it, children[node]) {
                int c = *it;
                int v = min(result[c][parent][0][0], result[c][parent][0][1]);
                if (v == INF) {
                    total = INF;
                    break;
                }
                total += v;
            }
            if (total != INF) {
                int v1 = INF; // v1 < v2
                int v2 = INF;
                FOREACH(it, children[node]) {
                    int c = *it;
                    if (result[c][parent][0][1] != INF) {
                        int v = min(result[c][parent][0][0], result[c][parent][0][1]);
                        int add = result[c][parent][0][1] - v;
                        if (add < v1) {
                            v2 = v1;
                            v1 = add;
                        } else if (add < v2) v2 = add;
                    }
                }
                if (parent == 0) {
                    if (v2 == INF) total = INF; else total += v1 + v2;
                } else {
                    if (v1 == INF) total = INF; else total += v1;
                }
            }
            result[node][0][parent][0] = result[node][1][parent][0] = total;
        }
    }
}

void calcSingleCoin(int node) {
    if (children[node].empty()) {
        FOR(i, 2) FOR(j, 2) result[node][i][j][1] = i > 0 || j > 0 ? 1 : INF;
    } else {
        FOR(parent, 2) {
            int total = 0;
            FOREACH(it, children[node]) {
                int c = *it;
                int v = min(result[c][parent][1][0], result[c][parent][1][1]);
                if (v == INF) {
                    total = INF;
                    break;
                }
                total += v;
            }
            if (total != INF) total++;
            if (parent) result[node][0][1][1] = result[node][1][1][1] = total;
            else result[node][1][0][1] = total;
        }

        // single coin with no parent coins
        int total = 0;
        FOREACH(it, children[node]) {
            int c = *it;
            int v = min(result[c][0][1][0], result[c][0][1][1]);
            if (v == INF) {
                total = INF;
                break;
            }
            total += v;
        }
        if (total != INF) {
            int v1 = INF;
            FOREACH(it, children[node]) {
                int c = *it;
                if (result[c][0][1][1] != INF || atLeastOne[c] != INF) {
                    int v = min(result[c][0][1][0], result[c][0][1][1]);
                    int add = min(result[c][0][1][1], atLeastOne[c]) - v;
                    if (add < v1) v1 = add;
                }
            }
            if (v1 == INF) total = INF; else total += v1;
        }
        if (total != INF) total++;
        result[node][0][0][1] = total;
    }
}

void calcAtLeastOne(int node) {
    if (children[node].empty()) {
        atLeastOne[node] = INF;
    } else {
        int total = 0;
        FOREACH(it, children[node]) {
            int c = *it;
            int v = min(result[c][1][0][0], result[c][1][0][1]);
            if (v == INF) {
                total = INF;
                break;
            }
            total += v;
        }
        if (total != INF) {
            int v1 = INF;
            FOREACH(it, children[node]) {
                int c = *it;
                if (result[c][1][0][1] != INF) {
                    int v = min(result[c][1][0][0], result[c][1][0][1]);
                    int add = result[c][1][0][1] - v;
                    if (add < v1) v1 = add;
                }
            }
            if (v1 == INF) total = INF; else total += v1;
        }
        atLeastOne[node] = total;
    }
}


void dfs(int node, int prevNode) {
    FOR(i, children[node].size()) if (children[node][i] == prevNode) {
        children[node].erase(children[node].begin() + i);
        break;
    }
    FOREACH(it, children[node]) dfs(*it, node);

    calcZeroCoins(node);
    calcSingleCoin(node);
    calcAtLeastOne(node);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) children[i].clear();
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            children[u].push_back(v);
            children[v].push_back(u);
        }
        dfs(0, -1);
        int out = min(result[0][0][0][0], result[0][0][0][1]);
        print(out == INF ? -1 : out);
    }
}

