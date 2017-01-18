// There are 3 cases - The capital is infected, capital neighbors are infected and any other planet is infected.
// https://www.codechef.com/JAN17/problems/CAPIMOVE
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

struct ResultItem {
    int index;
    int value;

    ResultItem() {
        index = -1;
        value = 0;
    }
};

#define MAX_N 50010
int p[MAX_N];
int n;
vector<int> neighbors[MAX_N];
int r[MAX_N];
ResultItem capital;
ResultItem capitalDestroyed;
ResultItem subTreeMax[MAX_N];
ResultItem firstSubTreeMax, secondSubTreeMax;
ResultItem emptyItem;
ResultItem tempItem;

ResultItem sm;
void dfs(int node, int prev, int level) {
    if (level == 1) {
        sm.value = p[node];
        sm.index = node;
    } else if (level >= 2) {
        r[node] = capital.index;
        if (p[node] > capitalDestroyed.value) {
            capitalDestroyed.value = p[node];
            capitalDestroyed.index = node;
        }
        if (p[node] > sm.value) {
            sm.value = p[node];
            sm.index = node;
        }
    }
    FOR(i, neighbors[node].size())
        if (neighbors[node][i] != prev)
            dfs(neighbors[node][i], node, level + 1);

    if (level == 1) {
        subTreeMax[node] = sm;
        if (sm.value > firstSubTreeMax.value) {
            secondSubTreeMax = firstSubTreeMax;
            firstSubTreeMax = sm;
        } else if (sm.value > secondSubTreeMax.value) secondSubTreeMax = sm;
    }
}


void solveLevel1(int node, int prev, int level) {
    if (level == 1) {
        if (subTreeMax[node].value == firstSubTreeMax.value) tempItem = secondSubTreeMax;
        else {
            r[node] = firstSubTreeMax.index;
            return;
        }
    } else if (level >= 3) {
        if (p[node] > tempItem.value) {
            tempItem.value = p[node];
            tempItem.index = node;
        }
    }
    FOR(i, neighbors[node].size())
        if (neighbors[node][i] != prev)
            solveLevel1(neighbors[node][i], node, level + 1);
    if (level == 1) r[node] = tempItem.index;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) {
            p[i] = getInt();
            neighbors[i].clear();
        }
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
        }
        capital = emptyItem;
        FOR(i, n) if (p[i] > capital.value) {
            capital.value = p[i];
            capital.index = i;
        }
        capitalDestroyed = emptyItem;
        firstSubTreeMax = emptyItem;
        secondSubTreeMax = emptyItem;
        dfs(capital.index, -1, 0);
        r[capital.index] = capitalDestroyed.index;

        solveLevel1(capital.index, -1, 0);

        FOR(i, n) print(r[i] + 1);
    }
}

