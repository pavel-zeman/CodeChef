// Value of f(x) can be calculated using values of f(1), f(2) ... f(x - 1). Use optimized matrix multiplication to calculate the target value.
// https://www.codechef.com/OCT16/problems/POWSUMS
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

#define MAX_N 320
#define STEPS 32
#define MAX_Q 40
int f[20 * MAX_N];
int x[MAX_N];
int query[MAX_Q];
int queryResult[MAX_Q];


int base[MAX_N][MAX_N];


int curr[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

int mp[STEPS][MAX_N][MAX_N];



int power2(int b, int n) {
    int c = 0;
    while (b > 0) {
        if ((b & 1) == 1) {
            FOR(i, 1) FOR(j, n) {
                LLI r = 0;
                FOR(k, n) {
                    //r = (r + curr[i][k] * (LLI)mp[c][k][j]) % MOD;
                    r += curr[i][k] * (LLI)mp[c][k][j];
                    if ((k & 7) == 7) r = r % MOD;
                    //r = r % MOD;
                }
                temp[i][j] = r % MOD;
            }
            FOR(i, 1) FOR(j, n) curr[i][j] = temp[i][j];
        }

        b >>= 1;
        c++;
    }

    LLI r = 0;
    FOR(i, n) r = (r + curr[0][i] * (LLI)f[n - i]) % MOD;
    return r;
}



void calc(int ind, int n) {
    LLI r = f[1] * (LLI)f[ind - 1] % MOD;
    FORE(j, 1, n) {
        LLI b = x[j] * (LLI)f[ind - 1 - j];
        if ((j & 1) == 1) r -= b; else r += b;
        r = r % MOD;
    }
    if (r < 0) r += MOD;
    f[ind] = r;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int q = getInt();
        f[0] = n;
        FOR(i, n) f[i + 1] = getInt();
        FORE(i, 1, n) {
            LLI r = (f[1] * (LLI)f[i] - f[i + 1]) % MOD;
            for(int j = 1; j < i; j++) {
                LLI b = f[i - j] * (LLI)x[j];
                if ((j & 1) == 1) r -= b; else r += b;
                r = r % MOD;
            }
            r = r * inv((i & 1) == 1 ? i + 1 : MOD - i - 1) % MOD;
            if (r < 0) r += MOD;
            x[i] = r;
            //printf("%d = %lld\n", i, r);
        }
        if (n <= 300) {
            base[0][0] = f[1];
            FORE(i, 1, n) base[0][i] = (i & 1) == 1 ? (MOD - x[i]) % MOD : x[i];
            FORE(i, 1, n) {
                FOR(j, n) base[i][j] = 0;
                base[i][i - 1] = 1;
            }
            FOR(i, n) FOR(j, n) mp[0][i][j] = base[i][j];
            FORE(s, 1, STEPS) {
                FOR(i, n) FOR(j, n) {
                    LLI r = 0;
                    FOR(k, n) {
                        r += mp[s - 1][i][k] * (LLI)mp[s - 1][k][j];
                        if ((k & 7) == 7) r = r % MOD;
                    }
                    temp[i][j] = r % MOD;
                }
                FOR(i, n) FOR(j, n) mp[s][i][j] = temp[i][j];
            }
        }

        vector<pair<int, int> > qq;

        FOR(i, q) {
            LLI xx = getLongLongInt();
            query[i] = xx % (MOD - 1);
            qq.push_back(make_pair(query[i], i));
        }
        sort(qq.begin(), qq.end());

        int lastCalc = n;
        int lastMatrix = n;

        FOR(i, n) FOR(j, n) curr[i][j] = i == j ? 1 : 0;

        FOR(i, q) {
            int xx = qq[i].first;
            int xind = qq[i].second;
            if (xx < 5000) {
                if (xx > lastCalc) {
                    FORE(j, lastCalc + 1, xx + 1) calc(j, n);
                    lastCalc = xx;
                }
                queryResult[xind] = f[xx];
                //printf("%d ", f[xx]);
            } else {
                if (xx <= n) queryResult[xind] = f[xx];
                else {
                    queryResult[xind] = power2(xx - lastMatrix, n);
                    lastMatrix = xx;
                }
                //printf("%d ", xx <= n ? f[xx] : power2(xx - n, n));
            }
        }
        FOR(i, q) printf("%d ", queryResult[i]);
        printf("\n");
    }
}

