// Precalculate diagonal sums, use them to calculate result in O(n * n * n)
// https://www.codechef.com/SNCK1A19/problems/AVGMAT
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
    putc_unlocked(' ', stdout);
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

#define MAX_N 310
bool grid[MAX_N][MAX_N];
bool grid2[MAX_N][MAX_N];
int m, n;
char row[MAX_N];
int res[MAX_N * 2];
int cache[MAX_N * 2][MAX_N];

int getValue(int row, int column) {
    return row >= 0 && row < n && column >= 0 && column < m ? grid[row][column] : 0;
}

int getTotal(int p, int r1, int r2) {
    if (r1 < 0) return 0;
    if (r2 >= n) return 0;
    if (r1 >= n) r1 = n - 1;
    if (r2 < 0) r2 = 0;
    return cache[p][r1] - (r2 == 0 ? 0 : cache[p][r2 - 1]);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        FOR(i, n) {
            getString(row);
            FOR(j, m) grid[i][j] = row[j] - '0';
        }
        FOR(i, n + m) res[i] = 0;
        FOR(xx, 2) {
            FOR(i, n + m) {
                cache[i][0] = getValue(0, i);
                FORE(j, 1, n) cache[i][j] = cache[i][j - 1] + getValue(j, i - j);
            }

            FOR(i, n) FOR(j, m) if (grid[i][j]) {
                int mm = i + j + 1;
                FORE(k, 1, mm) res[k] += getTotal(i + j - k, i, i - k + 1);
                mm = m + n - 2 - i - j + 1;
                FORE(k, 1, mm) res[k] += getTotal(i + j + k, i + k - 1, i);
            }

            FOR(i, n) FOR(j, m) grid2[j][n - 1 - i] = grid[i][j];
            swap(m, n);
            FOR(i, n) FOR(j, m) grid[i][j] = grid2[i][j];
        }
        FORE(i, 1, n + m - 1) print(res[i] >> 1);
        printf("\n");
    }
}

