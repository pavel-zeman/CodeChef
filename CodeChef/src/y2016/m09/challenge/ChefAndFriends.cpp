// Assign group to each friend by using "missing" pairs
// https://www.codechef.com/SEPT16/problems/CHFNFRN
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


#define NOT_PROCESSED 0
#define TO_PROCESS 1

#define MAX_N 1024
bool pp[MAX_N][MAX_N];
int status[MAX_N];
int group[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n) FOR(j, n) pp[i][j] = false;
        FOR(i, n) status[i] = NOT_PROCESSED;
        FOR(i, m) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            pp[a][b] = pp[b][a] = true;
        }
        bool ok = true;
        queue<int> toProcess;
        toProcess.push(0);
        group[0] = 0;
        status[0] = TO_PROCESS;
        while (!toProcess.empty()) {
            while (!toProcess.empty()) {
                int a = toProcess.front();
                toProcess.pop();
                FOR(i, n) {
                    if (i != a && !pp[a][i]) {
                        if (status[i] == NOT_PROCESSED) {
                            status[i] = TO_PROCESS;
                            group[i] = ~group[a];
                            toProcess.push(i);
                        } else if (group[i] != ~group[a]) {
                            ok = false;
                            goto end;
                        }
                    }
                }
            }
            FOR(i, n) {
                if (status[i] == NOT_PROCESSED) {
                    group[i] = 0;
                    status[i] = TO_PROCESS;
                    toProcess.push(i);
                    break;
                }
            }
        }
        end:
        printString(ok ? "YES" : "NO");
    }
}

