// At any time, we should exchange all the money we have. When we are at kiosk K at time T, we have following options: do nothing, go to a neighboring kiosk or exchange all the money we have. This leads to dynamic programming with arrays for local and foreign currency.
// https://www.codechef.com/JAN16/problems/CHINFL
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 1024
#define MAX_M 1042

int buy[MAX_M][MAX_N];
int sell[MAX_M][MAX_N];
double foreign[MAX_M][MAX_N];
double local[MAX_M][MAX_N];
double quint = 1e18;


int main(void) {
    int n = getInt();
    int m = getInt();
    LLI d = getLongLongInt();
    FOR(i, n)
        FOR(j, m) {
            sell[j][i] = getInt();
            buy[j][i] = getInt();
        }

    FOR(i, m + 1) FOR(j, n) foreign[i][j] = local[i][j] = 0;
    FOR(i, n) local[0][i] = d;
    bool isQuint = false;
    FORE(i, 1, m + 1) {
        FOR(j, n) {
            double prevDay = local[i - 1][j];
            double prevDayConverted = prevDay / sell[i - 1][j];
            if (prevDay > local[i][j]) local[i][j] = prevDay;
            if (prevDayConverted > foreign[i][j]) foreign[i][j] = prevDayConverted;
            if (j > 1 && prevDay > local[i][j - 1]) local[i][j - 1] = prevDay;
            if (j < n - 1 && prevDay > local[i][j + 1]) local[i][j + 1] = prevDay;
        }

        FOR(j, n) {
            double prevDay = foreign[i - 1][j];
            double prevDayConverted = prevDay * buy[i - 1][j];
            if (prevDayConverted > quint) {
                isQuint = true;
                goto finish;
            }
            if (prevDay > foreign[i][j]) foreign[i][j] = prevDay;
            if (prevDayConverted > local[i][j]) local[i][j] = prevDayConverted;
            if (j > 1 && prevDay > foreign[i][j - 1]) foreign[i][j - 1] = prevDay;
            if (j < n - 1 && prevDay > foreign[i][j + 1]) foreign[i][j + 1] = prevDay;
        }
    }
    finish:
    if (isQuint) {
        puts("Quintillionnaire");
    } else {
        double result = 0;
        FOR(i, n) result = max(result, local[m][i]);
        printf("%.10lf\n", result);
    }
}
