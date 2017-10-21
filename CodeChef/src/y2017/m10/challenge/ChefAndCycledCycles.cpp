// Pre-calculate shortest paths from start of each cycle to every other vertex, do the same for paths between cycles and then use these accumulated shortest paths to get the result for each query in constant time
// https://www.codechef.com/OCT17/problems/CHEFCCYL
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
vector<int> cycle[MAX_N];
vector<int> cycleAcc[MAX_N];
struct CC {
    int v1, v2;
    int w;
} cycleConnection[MAX_N];
int cycleConnectionAcc[MAX_N];
int n;



int getCycleWeight(int c, int v1, int v2) {
    int dist = abs(cycleAcc[c][v2] - cycleAcc[c][v1]);
    return min(dist, cycleAcc[c].back() - dist);
}

int getTotalWeight(int c1, int c2) {
    int dist = abs(cycleConnectionAcc[c2] - cycleConnectionAcc[c1]);
    return min(dist, cycleConnectionAcc[n] - dist);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        int q = getInt();
        FOR(i, n) {
            int a = getInt();
            cycle[i].clear();
            cycleAcc[i].clear();
            cycleAcc[i].push_back(0);
            int total = 0;
            FOR(j, a) {
                int w = getInt();
                cycle[i].push_back(w);
                cycleAcc[i].push_back(total += w);
            }
        }
        FOR(i, n) {
            cycleConnection[i].v1 = getInt() - 1;
            cycleConnection[i].v2 = getInt() - 1;
            cycleConnection[i].w = getInt();
        }
        cycleConnectionAcc[0] = 0;
        int total = 0;
        FOR(i, n) {
            total += getCycleWeight(i, cycleConnection[(i + n - 1) % n].v2, cycleConnection[i].v1) + cycleConnection[i].w;
            cycleConnectionAcc[i + 1] = total;
        }

        FOR(i, q) {
            int v1 = getInt() - 1;
            int c1 = getInt() - 1;
            int v2 = getInt() - 1;
            int c2 = getInt() - 1;
            int w1 = getCycleWeight(c1, v1, cycleConnection[c1].v1) + cycleConnection[c1].w
                + getTotalWeight((c1 + 1) % n, c2)
                + getCycleWeight(c2, cycleConnection[(c2 + n - 1) % n].v2, v2);
            int w2 = getCycleWeight(c1, v1, cycleConnection[(c1 + n - 1) % n].v2)
                + getTotalWeight(c1, (c2 + 1) % n) + cycleConnection[c2].w
                + getCycleWeight(c2, v2, cycleConnection[c2].v1);
            print(min(w1, w2));
        }
    }
}

