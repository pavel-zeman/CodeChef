// Just almost brute force solution
// https://www.codechef.com/FEB16/problems/WRDSUM
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

LLI power2(int a, int b) {
    LLI sq = a;
    LLI result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * sq;
        sq = sq * sq;
        b >>= 1;
    }
    return result;
}


void fail() {
    *((char *)0) = 0;
}


#define MOD2 998244353
#define MAX_N 100000
int f[MAX_N];
bool isPower[MAX_N];


int main(void) {
    FORE(i, 2, MAX_N) {
        if (!isPower[i]) {
            LLI j = i;
            j *= i;
            while (j < MAX_N) {
                isPower[j] = true;
                j *= i;
            }
        }
    }
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        //printf("Processing %d\n", n);
        if (n < 10) {
            //puts("End");
            break;
        }
        LLI total = (n + 2) * (LLI)(n - 1) / 2 % MOD2;
        int p = 2;
        while (true) {
            int e = pow(n, 1.0 / p);
            e++;
            while (power2(e, p) > n) e--;
            if (e == 1) break;
            e++;
            FORE(i, 2, e) {
                if (!isPower[i]) {
                    total = (total - power2(i, p) + i) % MOD2;
                }
            }
            p++;
        }
        if (total < 0) total += MOD2;
        print((int)total);
    }



    /*FORE(i, 2, MAX_N) {
        if (f[i] == 0) {
            f[i] = i;
            LLI j = i;
            j *= i;
            while (j < MAX_N) {
                if (f[j] == 0) f[j] = i;
                j *= i;
            }
        }
    }
    FORE(i, 2, MAX_N) f[i] = (f[i] + f[i - 1]) % MOD2;


    int t = getInt();
    FOR(tt, t) {
        print(f[getInt()]);
    }*/
}

