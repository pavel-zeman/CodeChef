// Generate list of depths for given time and precalculate all XORs up to certain size
// https://www.codechef.com/SEPT17/problems/WEASELTX
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

#define MAX_N 300010
#define CS 512
vector<int> neighbors[MAX_N];
LLI x[MAX_N];
LLI xd[MAX_N];
int depth;
int nums[MAX_N];
int numCount;
LLI cache[CS][MAX_N / CS];


void build(int node, int prev, int d) {
    xd[d] ^= x[node];
    if (d > depth) depth = d;
    FOR(i, neighbors[node].size()) {
        int n = neighbors[node][i];
        if (n != prev) build(n, node, d + 1);
    }
}


void genNums(int pow, int v) {
    numCount = 0;
    nums[numCount++] = 0;
    if ((v & 1) == 1) nums[numCount++] = 1;
    int i = 2;
    while (i <= pow) {
        if ((v & i) == i) {
            int x = numCount;
            if (i + i > depth)
                FOR(j, x) {
                    nums[numCount++] = nums[j] + i;
                    if (nums[j] + i > depth) break;
                }
            else FOR(j, x) nums[numCount++] = nums[j] + i;
        }
        i <<= 1;
    }
}

int main(void) {
    int n = getInt();
    int q = getInt();
    FOR(i, n - 1) {
        int u = getInt();
        int v = getInt();
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
    }
    FOR(i, n) x[i] = getLongLongInt();
    build(0, -1, 0);
    depth++;
    int nn = 1;
    while (nn < depth) nn <<= 1;

    FOR(i, CS) {
        genNums(CS >> 1, i);
        FOR(j, depth / CS + 1) {
            LLI res = 0;
            FOR(k, numCount) res ^= xd[nums[k] + j * CS];
            cache[i][j] = res;
        }
    }
    int nn2 = nn / CS;

    FOR(i, q) {
        LLI t = getLongLongInt();
        if (t == 0) printf("%lld\n", xd[0]);
        else {
            t--;
            LLI res = 0;
            int nnt = nn - 1 - (t & (nn - 1));
            genNums(nn2 >> 1, nnt / CS);
            FOR(i, numCount) res ^= cache[nnt & (CS - 1)][nums[i]];
            printf("%lld\n", res);
        }
    }
}

