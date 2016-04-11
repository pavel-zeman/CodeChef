// Brute force algorithm for the smallest input.
// https://www.codechef.com/APRIL16/problems/FURGRAPH
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

#define MAX_N 12
#define MAX_M 200
#define EMPTY -1
#define NOT_DONE LLONG_MIN

int n, m;
struct Edge {
    int u, v, c;
} edges[MAX_M];

int used[MAX_N];
LLI cost[MAX_N][MAX_N];
int path[2][MAX_N];
LLI state[100000];
int pow3[MAX_N];

LLI calcCost(int node, int color, int pathLength) {
    LLI result = cost[node][node];
    FOR(i, pathLength) result += cost[node][path[color][i]];
    return result;
}

LLI findMax(int level, int currentState);

LLI findMin(int level, int currentState) {
    if (level == n) return 0;
    else {
        LLI mn = state[currentState];
        if (mn == NOT_DONE) {
            mn = LLONG_MAX;
            FOR(i, n) if (used[i] == EMPTY) {
                used[i] = 1;
                path[1][level >> 1] = i;
                LLI temp = findMax(level + 1, currentState + pow3[i] * 2);
                temp -= calcCost(i, 1, level >> 1);
                if (temp < mn) {
                    mn = temp;
                }
                used[i] = EMPTY;
            }
            state[currentState] = mn;
        }
        return mn;
    }
}


LLI findMax(int level, int currentState) {
    if (level == n) return 0;
    else {
        LLI mx = state[currentState];
        if (mx == NOT_DONE) {
            mx = LLONG_MIN;
            FOR(i, n) if (used[i] == EMPTY) {
                used[i] = 0;
                path[0][level >> 1] = i;
                LLI temp = findMin(level + 1, currentState + pow3[i]);
                temp += calcCost(i, 0, level >> 1);
                if (temp > mx) {
                    mx = temp;
                }
                used[i] = EMPTY;
            }
            state[currentState] = mx;
        }
        return mx;
    }
}

int main(void) {
    pow3[0] = 1;
    FORE(i, 1, MAX_N) pow3[i] = pow3[i - 1] * 3;
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        if (n > 10) fail();
        FOR(i, m) {
            edges[i].u = getInt() - 1;
            edges[i].v = getInt() - 1;
            edges[i].c = getInt();
        }

        FOR(i, n) FOR(j, n) cost[i][j] = 0;
        FOR(i, n) used[i] = EMPTY;
        FOR(i, m) {
            FOR(j, pow3[n]) state[j] = NOT_DONE;
            cost[edges[i].u][edges[i].v] += edges[i].c;
            if (edges[i].u != edges[i].v) cost[edges[i].v][edges[i].u] += edges[i].c;
            LLI result = findMax(0, 0);
            print(result);
        }
    }
}

