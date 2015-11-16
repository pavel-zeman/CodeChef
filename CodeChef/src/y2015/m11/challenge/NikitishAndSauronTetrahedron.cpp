// Calcuate number of ways to destroy tetrahedron for each N. Then use this number to calculate number of ways to destroy Sauron tetrahedron (brute force solution, only works for small input).
// https://www.codechef.com/NOV15/problems/REBTET
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_COMB 6030
#define MOD 100003
#define MAX_N 1004

int comb[MAX_COMB][MAX_COMB];
int poss[MAX_N];
int result[60010];

int getComb(int n, int k) {
    if (n < k || k < 0) return 0;
    return comb[n][k];
}

// F(N + 1, 1) = F(N, 1) + POSS(N + 1) * (F(N, 1) + 1)
// F(N + 1, K) = F(N, K) + POSS(N + 1) * F(N, K - 1)

int main(void) {
    comb[0][0] = 1;
    FORE(i, 1, MAX_COMB) {
        comb[i][0] = comb[i][i] = 1;
        FORE(j, 1, i) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
    }
    poss[1] = 9;
    FORE(i, 2, MAX_N) {
        long long int total = 0;
        int top = 6 * i - 12;
        FORE(j, i, 6 * i - 7) {
            total +=
                81 * getComb(top, j - 4) +
                27 * 4 * getComb(top, j - 3) +
                9 * 6 * getComb(top, j - 2) +
                3 * 4 * getComb(top, j - 1) +
                1 * 1 * getComb(top, j);
            total %= MOD;
        }
        poss[i] = total;
    }
    //FORE(i, 1, 10) printf("%d ", poss[i]);
    //printf("\n");
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        FOR(i, k + 1) result[i] = 0;
        result[0] = 1;
        FORE(i, 1, n + 1) {
            result[k] = (result[k] + result[k] * (long long int)poss[i] + result[k - 1] * (long long int)poss[i]) % MOD;
            for(int j = k - 1;j>0;j--) {
                result[j] = (result[j] + result[j - 1] * (long long int)poss[i]) % MOD;
            }
        }
        print(result[k]);
    }
}

