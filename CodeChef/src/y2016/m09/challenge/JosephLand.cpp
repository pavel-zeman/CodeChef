// Use DFS from the capital and use SQRT decomposition to calculate RMQ along current path
// https://www.codechef.com/SEPT16/problems/JTREE
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

#define MAX_N 100010
#define MAX_N_SQRT 1400
vector<int> neighbors[MAX_N];
vector<pair<int, int> > tickets[MAX_N];
LLI result[MAX_N];
LLI path[MAX_N];
LLI pathSqrt[MAX_N_SQRT];
int sqrtSize;
LLI inf;


LLI getMin(int start, int end) {
    start = max(start, 0);
    LLI res = inf;

    int startSegment = start / sqrtSize;
    int endSegment = end / sqrtSize;
    if (startSegment == endSegment) {
        FORE(i, start, end) res = min(res, path[i]);
    } else {
        int firstSegmentCount = sqrtSize - start % sqrtSize;
        FOR(i, firstSegmentCount) res = min(res, path[start + i]);
        startSegment++;
        while (startSegment < endSegment) res = min(res, pathSqrt[startSegment++]);
        FORE(i, endSegment * sqrtSize, end) res = min(res, path[i]);
    }
    return res;
}


void calc(int depth, int node, LLI pathSqrtMin) {
    LLI localMin = inf;
    FOR(i, tickets[node].size()) {
        pair<int, int> p = tickets[node][i];
        localMin = min(localMin, p.second + getMin(depth - p.first, depth));
    }
    result[node] = path[depth] = localMin;

    pathSqrtMin = min(pathSqrtMin, localMin);
    if ((depth + 1) % sqrtSize == 0) {
        pathSqrt[depth / sqrtSize] = pathSqrtMin;
        pathSqrtMin = inf;
    }
    FOR(i, neighbors[node].size()) calc(depth + 1, neighbors[node][i], pathSqrtMin);
}

int main(void) {
    int n = getInt();
    int m = getInt();
    FOR(i, n - 1) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        neighbors[b].push_back(a);
    }
    FOR(i, m) {
        int v = getInt() - 1;
        int k = getInt();
        int w = getInt();
        tickets[v].push_back(make_pair(k, w));
    }
    inf = (n + 1) * (LLI)1000000000;
    sqrtSize = sqrt(n) / 2;
    if (sqrtSize < 1) sqrtSize++;

    result[0] = 0;
    path[0] = 0;
    FOR(i, neighbors[0].size()) calc(1, neighbors[0][i], 0);

    int q = getInt();
    FOR(i, q) {
        int h = getInt() - 1;
        printf("%lld\n", result[h]);
    }
}

