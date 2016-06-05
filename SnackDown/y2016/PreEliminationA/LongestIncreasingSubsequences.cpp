// This is just a test, no real implementation
// https://www.codechef.com/SNCKPA16/problems/MAKELIS
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

#define N 6
//int values[N] = {6, 2, 10, 5, 30, 20};
int values[N] = {6, 3, 5, 2, 1, 4};
bool used[N];
int num[N][N + 1];
int hist[1000000][N + 1];
int histTotal[1000000];

int calcLis() {
    FOR(i, N) FOR(j, N + 1) num[i][j] = 0;
    FOR(i, N) num[i][1] = 1;
    FORE(i, 1, N) {
        FOR(j, i) {
            if (values[j] < values[i]) {
                FOR(k, N) num[i][k + 1] += num[j][k];
            }
        }
    }
    int mx = 0;
    FOR(i, N) FOR(j, N + 1) if (num[i][j] > 0 && j > mx) mx = j;
    int cc = 0;
    FOR(i, N) cc += num[i][mx];
    hist[cc][mx]++;
    histTotal[cc]++;
    if (cc == 31) {
        printf("Length: %d: ", mx);
        FOR(i, N) printf("%d ", values[i]);
        printf("\n");
    }
    return cc;
}

void gen(int level) {
    if (level < N) {
        FOR(i, N) if (!used[i]) {
            values[level] = i;
            used[i] = true;
            gen(level + 1);
            used[i] = false;
        }
    } else {
        calcLis();
    }
}

int main(void) {
    printf("%d\n", calcLis());
    gen(0);
    FOR(i, 1000000) {
        if (histTotal[i] > 0) {
            printf("%d has %d seq: ", i, histTotal[i]);
            FOR(j, N + 1) printf("%d=%d ", j, hist[i][j]);
            printf("\n");
        }
    }
/*    int t = getInt();
    FOR(tt, t) {
    }*/
}
