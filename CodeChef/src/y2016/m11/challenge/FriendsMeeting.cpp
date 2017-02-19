// Use DFS to traverse the tree while accumulating the total distance between all pairs of selected squares
// https://www.codechef.com/NOV16/problems/FRIEMEET
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

#define MAX_N 50010
vector<pair<int, int> > neighbors[MAX_N];
bool meet[MAX_N];
LLI totalDist;

pair<LLI, int> calc(int node, int prev, int nodes, LLI curDist) {
    int nextNodes = nodes;
    pair<LLI, int> result(0, 0);
    if (meet[node]) {
        totalDist += curDist;
        nextNodes++;
        result.second = 1;
    }

    FOR(i, neighbors[node].size()) {
        pair<int, int> nn = neighbors[node][i];
        if (nn.first != prev) {
            pair<LLI, int> temp = calc(nn.first, node, nextNodes, curDist + nextNodes * (LLI)nn.second);
            curDist += temp.first + temp.second * (LLI)nn.second;
            nextNodes += temp.second;
            result.first += temp.first + temp.second * (LLI)nn.second;
            result.second += temp.second;
        }
    }
    return result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n) {
            neighbors[i].clear();
            meet[i] = false;
        }
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            int l = getInt();
            neighbors[u].push_back(make_pair(v, l));
            neighbors[v].push_back(make_pair(u, l));
        }
        FOR(i, m) meet[getInt() - 1] = true;

        totalDist = 0;
        calc(0, -1, 0, 0);
        totalDist <<= 1;
        LLI m2 = m * (LLI)m;
        LLI g = gcd(totalDist, m2);
        printf("%lld %lld\n", totalDist / g, m2 / g);
    }
}

