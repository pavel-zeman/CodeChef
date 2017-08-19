// Based on the idea from https://math.stackexchange.com/questions/38763/how-to-find-a-polynomial-from-a-given-root
// https://www.codechef.com/JULY17?order=desc&sortBy=successful_submissions
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

#define MAX_C 1026
#define MAX_N 20

int a[MAX_N];
int mulc[MAX_N];
int n;
int n2;
int totalCalled;
int totalNotZero;

struct Coef {
    int value[1024];

    void init() {
        FOR(i, n2) value[i] = 0;
    }

    void mulAdd(Coef & result) {
        int tt = 0;
        totalCalled += n2;
        FOR(i, n2) if (value[i]) {
            tt++;
            FOR(jj, n) {
                int j = 1 << jj;
                int vv = (value[i] * mulc[jj] + MOD) % MOD;
                if ((i & j) != 0) vv = vv * (LLI)a[jj] % MOD;
                result.value[i ^ j] = (result.value[i ^ j] + vv) % MOD;
            }
        }
        totalNotZero += tt;
        //printf("TT: %d\n", tt);
    }
};

struct Poly {
    Coef coefs[MAX_C];
    int degree;

    void mul() {
        int resultDegree = degree + 1;
        coefs[degree].init();
        for(int i=resultDegree - 1; i > 0; i--) coefs[i - 1].mulAdd(coefs[i]);
        degree = resultDegree;
    }

    void init() {
        degree = 1;
        coefs[0].init();
    }

    void print() {
        FOR(i, degree) {
            printf("%d ", degree - i - 1);
            FOR(j, n2) {
                if (coefs[i].value[j] != 0) {
                    int temp = j;
                    FOR(k, n) {
                        if ((temp & 1) != 0) printf("%d,", a[k]);
                        temp >>= 1;
                    }
                    printf("=%d ", coefs[i].value[j]);
                }
            }
            printf("\n");
        }
    }

} result;

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        totalCalled = totalNotZero;
        n = getInt();
        if (n > 10) fail();
        n2 = 1 << n;
        FOR(i, n) a[i] = getInt();
        result.init();
        result.coefs[0].value[0] = 1;
        FOR(i, n2) {
            int temp = i;
            FOR(j, n) {
                mulc[j] = (temp & 1) == 0 ? 1 : -1;
                temp >>= 1;
            }
            //op.print();
            result.mul();
            //result.print();
        }
        print(result.degree - 1);
        for(int i = result.degree - 1; i >= 0; i--) print(result.coefs[i].value[0]);
        //printf("%d\n%d\n", totalCalled, totalNotZero);
    }
}

