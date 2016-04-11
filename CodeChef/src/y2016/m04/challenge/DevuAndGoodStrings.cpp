// Use brute force to pre-generate all good strings of all lengths and alphabet sizes. Then compare them one by one with input string to calculate Hamming distance.
// https://www.codechef.com/APRIL16/problems/DEVGOSTR
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

#define MAX_K 52
#define MAX_ALL 4000000
char data[MAX_K];
int totalStrings;
int alpha;
int lastUsed;

char allData[MAX_ALL];

int start[4][MAX_K];
int total[4][MAX_K];

void gen(int pos, int total) {
    if (pos == total) {
        memcpy(allData + lastUsed, data, total);
        lastUsed += total;
        totalStrings++;
    } else {
        FOR(i, alpha) {
            data[pos] = i;
            bool ok = true;
            for(int j=1;pos - j * 2 >= 0; j++) {
                if (data[pos - j] == data[pos] && data[pos - 2 * j] == data[pos]) {
                    ok = false;
                    break;
                }
            }
            if (ok) gen(pos + 1, total);
        }
    }
}

int main(void) {
    FORE(i, 1, 4) {
        alpha = i;
        FORE(j, 1, 100) {
            totalStrings = 0;
            start[i][j] = lastUsed;
            data[0] = 0;
            gen(1, j);
            total[i][j] = totalStrings;
            if (totalStrings == 0) break;
        }

    }
    int t = getInt();
    FOR(tt, t) {
        int a = getInt();
        int k = getInt();
        char stringData[MAX_K];
        char stringData2[4][MAX_K];
        int l = getString(stringData);
        FOR(i, l) stringData[i] -= 'a';
        FOR(i, a) FOR(j, l) stringData2[i][j] = (stringData[j] + i) % a;
        int pos = start[a][l];
        int result = 0;
        FOR(i, total[a][l]) {
            FOR(x, a) {
                int diff = 0;
                FOR(j, l) if (stringData2[x][j] != allData[pos + j]) diff++;
                if (diff <= k) result++;
            }
            pos += l;
        }

        print(result);
    }
}

