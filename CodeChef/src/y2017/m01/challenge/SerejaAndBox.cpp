// Calculate all possible results (min and max) for each sub-cube. Then use dynamic programming to distribute the K cells between all the sub-cubes.
// https://www.codechef.com/JAN17/problems/SEABOX
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
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


#define MAX_N 32
#define PARTS 8
char a[MAX_N][MAX_N][MAX_N];
int cx[PARTS][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

vector<pair<int, int>> minCache[6][32 * 32 * 32];
int tempRes[1 << 15];
int cachePos[PARTS];
int tempRes2[PARTS][1 << 16];
int ones, zeros;

void calcCachePos(int x, int y, int z, int s, int cubes) {
    FOR(i, PARTS) {
        int xx = x * 2 + cx[i][0];
        int yy = y * 2 + cx[i][1];
        int zz = z * 2 + cx[i][2];
        cachePos[i] = (xx * cubes * 2 + yy) * cubes * 2 + zz;
    }

    ones = 0;
    int xx = x * s;
    int yy = y * s;
    int zz = z * s;
    FOR(i, s) FOR(j, s) FOR(k, s) ones += a[xx + i][yy + j][zz + k];
    zeros = s * s * s - ones;
}

int getMin2(int level, int level2, int remain) {
    if (level2 == PARTS) return 0;
    else {
        int res = tempRes2[level2][remain];
        if (res < 0) {
            res = 1 << 20;
            FOR(i, minCache[level][cachePos[level2]].size()) {
                int s = minCache[level][cachePos[level2]][i].first;
                if (s > remain) break;
                int s2 = minCache[level][cachePos[level2]][i].second + getMin2(level, level2 + 1, remain - s);
                if (s2 < res) res = s2;
            }
            tempRes2[level2][remain] = res;
        }
        return res;
    }
}

int getMin(int x, int y, int z, int s, int cubes, int level, int k) {
    if (s == 1) return 1;
    if (k >= ((s * s * s) >> 1)) return 1;
    if (k >= min(ones, zeros)) return 1;
    return getMin2(level - 1, 0, k);
}

vector<pair<int, int>> maxCache[6][32 * 32 * 32];

int getMax2(int level, int level2, int remain) {
    if (level2 == PARTS) return 0;
    else {
        int res = tempRes2[level2][remain];
        if (res < 0) {
            res = 0;
            FOR(i, maxCache[level][cachePos[level2]].size()) {
                int s = maxCache[level][cachePos[level2]][i].first;
                if (s > remain) break;
                int s2 = maxCache[level][cachePos[level2]][i].second + getMax2(level, level2 + 1, remain - s);
                if (s2 > res) res = s2;
            }
            tempRes2[level2][remain] = res;
        }
        return res;
    }
}


int getMax(int x, int y, int z, int s, int cubes, int level, int k) {
    if (s == 1) return 1;
    if (s == 2) return k + min(ones, zeros) > 0 ? PARTS : 1;
    if (k + min(ones, zeros) == 0) return 1;
    return getMax2(level - 1, 0, k);
}


void solveMin(int x, int y, int z, int level, int cubes, int from, int to) {
    if (from >= to - 1) return;
    if (tempRes[from] == tempRes[to]) {
        FORE(i, from + 1, to) tempRes[i] = tempRes[from];
    } else {
        int mid = (from + to) >> 1;
        tempRes[mid] = getMin(x, y, z, 1 << level, cubes, level, mid);
        solveMin(x, y, z, level, cubes, from, mid);
        solveMin(x, y, z, level, cubes, mid, to);
    }
}

void solveMax(int x, int y, int z, int level, int cubes, int from, int to) {
    if (from >= to - 1) return;
    if (tempRes[from] == tempRes[to]) {
        FORE(i, from + 1, to) tempRes[i] = tempRes[from];
    } else {
        int mid = (from + to) >> 1;
        tempRes[mid] = getMax(x, y, z, 1 << level, cubes, level, mid);
        solveMax(x, y, z, level, cubes, from, mid);
        solveMax(x, y, z, level, cubes, mid, to);
    }
}


int main(void) {
    int n = getInt();
    int k = getInt();
    int l = 0;
    int tn = n;
    while (tn > 1) tn >>= 1, l++;
    FOR(i, n) FOR(j, n) FOR(k, n) a[i][j][k] = getInt();

    FOR(x, 1 << l) FOR(y, 1 << l) FOR(z, 1 << l) minCache[0][(x * n + y) * n + z].push_back(make_pair(0, 1));
    FOR(x, 1 << l) FOR(y, 1 << l) FOR(z, 1 << l) maxCache[0][(x * n + y) * n + z].push_back(make_pair(0, 1));

    FORE(i, 1, l) {
        int k2 = min(k, (1 << (3 * i - 1)));
        int cubes = 1 << (l - i);
        FOR(x, 1 << (l - i)) FOR(y, 1 << (l - i)) FOR(z, 1 << (l - i)) {
            calcCachePos(x, y, z, 1 << i, cubes);
            FOR(j, PARTS) FOR(kk, k2 + 1) tempRes2[j][kk] = -1;
            FOR(j, k2 + 1) tempRes[j] = 0;
            tempRes[0] = getMin(x, y, z, 1 << i, cubes, i, 0);
            tempRes[k2] = getMin(x, y, z, 1 << i, cubes, i, k2);
            solveMin(x, y, z, i, cubes, 0, k2);
            int pos = (x * cubes + y) * cubes + z;
            int lastValue = tempRes[0];
            minCache[i][pos].push_back(make_pair(0, tempRes[0]));
            FORE(j, 1, k2 + 1) if (tempRes[j] != lastValue) {
                lastValue = tempRes[j];
                minCache[i][pos].push_back(make_pair(j, tempRes[j]));
            }
        }
    }

    FOR(j, PARTS) FOR(kk, k + 1) tempRes2[j][kk] = -1;
    calcCachePos(0, 0, 0, 1 << l, 1);
    print(getMin(0, 0, 0, 1 << l, 1, l, k));

    FORE(i, 1, l) {
        int k2 = min(k, (1 << (3 * i - 3)));
        int cubes = 1 << (l - i);
        FOR(x, 1 << (l - i)) FOR(y, 1 << (l - i)) FOR(z, 1 << (l - i)) {
            calcCachePos(x, y, z, 1 << i, cubes);
            FOR(j, PARTS) FOR(kk, k2 + 1) tempRes2[j][kk] = -1;
            FOR(j, k2 + 1) tempRes[j] = 0;
            tempRes[0] = getMax(x, y, z, 1 << i, cubes, i, 0);
            tempRes[k2] = getMax(x, y, z, 1 << i, cubes, i, k2);
            solveMax(x, y, z, i, cubes, 0, k2);
            int pos = (x * cubes + y) * cubes + z;
            int lastValue = tempRes[0];
            maxCache[i][pos].push_back(make_pair(0, tempRes[0]));
            FORE(j, 1, k2 + 1) if (tempRes[j] != lastValue) {
                lastValue = tempRes[j];
                maxCache[i][pos].push_back(make_pair(j, tempRes[j]));
            }
        }
    }

    FOR(j, PARTS) FOR(kk, k + 1) tempRes2[j][kk] = -1;
    calcCachePos(0, 0, 0, 1 << l, 1);
    print(getMax(0, 0, 0, 1 << l, 1, l, k));
}

