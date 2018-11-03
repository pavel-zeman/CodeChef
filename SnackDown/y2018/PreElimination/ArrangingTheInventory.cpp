// Description
// https://www.codechef.com/SNCKPE19/problems/INVENTRY
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

#define MAX_N 100010
#define FULL '#'
#define EMPTY '.'
char s[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        getInt();
        int l = getString(s);
        LLI res = 0;
        int finished = 0;
        FOR(i, l) {
            if (s[i] == FULL) {
                if (finished == i) finished++;
                else {
                    //printf("I: %d\n", i);
                    int tt = 0;
                    int j = i;
                    while (j < l && (s[j] == FULL || j < i + (tt - 1) * 2 + 1)) {
                        if (s[j] == FULL) tt++;
                        j++;
                    }
                    if (j == l) {
                        //printString("ERROR");
                        res = -1;
                        break;
                    } else {
                        //printf("J: %d %d\n", j, tt);
                        int k = j;
                        int origPos = j;
                        while (k > i) {
                            while (s[origPos] == EMPTY) origPos--;
                            res += k - 1 - origPos;
                            k -= 2;
                            origPos--;
                        }
                        //printf("Res2: %d\n", res);
                        k = i;
                        while (k < j) {
                            res += k - finished;
                            finished++;
                            k += 2;
                        }
                        i = j;
                        //printf("Res3: %d\n", res);
                    }
                }
            }
        }
        print(res);
    }
}

