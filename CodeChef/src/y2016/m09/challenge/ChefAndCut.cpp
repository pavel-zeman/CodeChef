// Just naive brute-force solution for the first subtask
// https://www.codechef.com/SEPT16/problems/CHEFKC
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

#define MAX_N 80
int edge[MAX_N][MAX_N];
int innerVertices[MAX_N];
bool start[MAX_N];

int main(void) {
    int n = getInt();
    if (n > 10) fail();
    int m = getInt();
    int k = getInt() - 1;
    int s = getInt() - 1;
    int t = getInt() - 1;
    FOR(i, m) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        int c = getInt();
        edge[a][b] = c;
    }
    int x = 0;
    FOR(i, n) if (i != s && i != t) innerVertices[x++] = i;
    vector<int> cuts;
    FOR(i, 1 << (n - 2)) {
        FOR(j, n) start[j] = false;
        start[s] = true;
        x = i;
        FOR(j, n - 2) {
            if ((x & 1) == 1) start[innerVertices[j]] = true;
            x >>= 1;
        }
        int cut = 0;
        FOR(j, n) FOR(k, n)
            if (edge[j][k] > 0 && start[j] && !start[k])
                cut += edge[j][k];

        cuts.push_back(cut);
    }
    sort(cuts.begin(), cuts.end());
    print(cuts[k]);
}

