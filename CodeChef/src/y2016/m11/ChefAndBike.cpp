// Just "brute-force" solution with "squaring" exponentiation
// https://www.codechef.com/NOV16/problems/BIKE
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI unsigned long long int
#define MOD 1163962801


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

#define MAX_M 10010
#define MAX_N 22


unsigned int pow1[MAX_N][MAX_N][MAX_N][MAX_N - 1];
unsigned int pow2[MAX_N][MAX_N][MAX_N][MAX_N - 1];


unsigned int ways[MAX_N][MAX_N][MAX_N][MAX_N - 1];
unsigned int ways2[MAX_N][MAX_N][MAX_N][MAX_N - 1];

int main(void) {
    int n = getInt();
    int m = getInt();
    int t = getInt();
    FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) pow1[i][j][k][l] = 0;
    FOR(i, m) {
        int s = getInt() - 1;
        int e = getInt() - 1;
        int f = getInt() % n;
        int r = getInt() % (n - 1);
        pow1[s][e][f][r]++;
    }

    FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) ways[i][j][k][l] = 0;
    FOR(i, n) ways[i][i][0][0] = 1;
    while (t > 0) {
        if ((t & 1) == 1) {
            FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) ways2[i][j][k][l] = 0;
            FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) {
                LLI r = 0;
                FOR(x, n) FOR(y, n) {
                    int ii = (k - y + n) % n;
                    FOR(z, n - 1)  {
                        r += ways[i][x][y][z] * (LLI) pow1[x][j][ii][(l - z + n - 1) % (n - 1)];
                        if ((z & 7) == 7) r %= MOD;
                    }
                    r %= MOD;
                }
                ways2[i][j][k][l] = r % MOD;
            }
            FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) ways[i][j][k][l] = ways2[i][j][k][l];
        }

        FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) pow2[i][j][k][l] = 0;
        FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) {
            LLI r = 0;
            FOR(x, n) FOR(y, n) {
                int ii = (k - y + n) % n;
                FOR(z, n - 1)  {
                    r += pow1[i][x][y][z] * (LLI) pow1[x][j][ii][(l - z + n - 1) % (n - 1)];
                    if ((z & 7) == 7) r %= MOD;
                }
                r %= MOD;
            }
            pow2[i][j][k][l] = r % MOD;
        }

        /*FOR(i, n) FOR(k, n) FOR(l, n - 1) FOR(x, n) FOR(y, n) FOR(z, n - 1) {
            unsigned int r = 0;
            FOR(j, n) r = (r + pow1[i][j][k][l] * (LLI)pow1[j][x][y][z]) % MOD;
            pow2[i][x][(k + y) % n][(l + z) % (n - 1)] =
            (pow2[i][x][(k + y) % n][(l + z) % (n - 1)] + r) % MOD;
        }*/
        FOR(i, n) FOR(j, n) FOR(k, n) FOR(l, n - 1) pow1[i][j][k][l] = pow2[i][j][k][l];
        t >>= 1;
    }

    /*FOR(i, n) {
        FOR(k, n) {
            FOR(l, n - 1) printf("%d ", ways[i][i][k][l]);
            printf("\n");
        }
    }*/
    FOR(i, n) FOR(j, n){
        FOR(k, n) {
            FOR(l, n - 1) printf("%d ", ways[i][j][k][l]);
            printf("\n");
        }
    }
}

