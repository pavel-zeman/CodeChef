// Just an attempt to solve first 2 subtasks
// https://www.codechef.com/SEPT17/problems/WEASELSC
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
#define MAX_K 64
int hist[MAX_N];
int n;
int nextSmaller[MAX_N];
LLI res[MAX_N][MAX_K];


void buildNextSmaller() {
    FOR(i, n) nextSmaller[i] = n;
    vector<int> q;
    FOR(i, n) {
        while (!q.empty() && hist[q.back()] > hist[i]) {
            nextSmaller[q.back()] = i;
            q.pop_back();
        }
        q.push_back(i);
    }
}

LLI solveZeroK() {
    buildNextSmaller();
    LLI res = 0;
    FOR(i, n) {
        int h = hist[i];
        int j = nextSmaller[i];
        LLI res1 = h * (LLI)(j - i);
        if (res1 > res) res = res1;
        while (j < n) {
            h = hist[j];
            j = nextSmaller[j];
            res1 = h * (LLI)(j - i);
            if (res1 > res) res = res1;
        }
    }
    return res;
}

void reorder() {
    int i = 0;
    int j = n - 1;
    while (i < j) {
        swap(hist[i], hist[j]);
        i++, j--;
    }
}

map<int, LLI> cache[MAX_N];

LLI get(int pos, int remainK, int minValue) {
    //printf("Get: Pos:%d K:%d Min:%d\n", pos, remainK, minValue);
    if (nextSmaller[pos] == n) minValue = 0;
    auto cacheValue = cache[pos].insert(make_pair((remainK << 20) | minValue, 0));
    if (cacheValue.second) {
        LLI res = 0;
        int h = hist[pos];
        int j = nextSmaller[pos];
        LLI res1 = h * (LLI)(j - pos);
        if (res1 > res) res = res1;
        while (j < n) {
            h = hist[j];
            j = nextSmaller[j];
            if (h < minValue) break;
            res1 = h * (LLI)(j - pos);
            if (res1 > res) res = res1;
        }
        if (remainK > 0) {
            h = hist[pos];
            FORE(i, pos, n - 1) {
                if (hist[i] < h) {
                    h = hist[i];
                    if (h < minValue) break;
                }
                if (hist[i + 1] > hist[i]) {
                    LLI res1 = h * (LLI)(i + 1 - pos) + get(i + 1, remainK - 1, h + 1);
                    if (res1 > res) res = res1;
                }
            }
        }
        cacheValue.first->second = res;
    }
    return cacheValue.first->second;
}

LLI solveSmall(int k) {
    buildNextSmaller();
    FOR(i, n) cache[i].clear();
    LLI res = 0;
    FOR(i, n) {
        if (hist[i] > 0) {
            LLI res1 = get(i, k, 1);
            if (res1 > res) res = res1;
        }
    }

    /*int total = 0;
    FOR(i, n) {
        printf("Pos: %d, size: %d = ", i, cache[i].size());
        total += cache[i].size();
        int kk = -1;
        int cc = 0;
        set<LLI> uniq;
        for(auto it = cache[i].begin(); it != cache[i].end(); it++) {
            if ((it->first >> 20) != kk) {
                if (kk >= 0) printf("k:%d = %d,%d ", kk, cc, uniq.size());
                cc = 0;
                kk = it->first >> 20;
                uniq.clear();
            }
            cc++;
            uniq.insert(it->second);
        }
        printf("k:%d = %d,%d\n", kk, cc, uniq.size());

    }
    printf("Total: %d\n", total);*/

    return res;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        int k = getInt();
        FOR(i, n) hist[i] = getInt();
        if (n <= 150000 || k == 0) {
            LLI res1 = solveSmall(k);
            reorder();
            LLI res2 = solveSmall(k);
            print(max(res1, res2));
        }
    }
}

