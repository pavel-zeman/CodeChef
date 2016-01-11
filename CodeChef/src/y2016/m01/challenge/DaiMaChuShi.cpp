// Just brute force solution, which does not pass event the small subtask
// https://www.codechef.com/JAN16/problems/DMCS
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

#define D 4
#define MAX_N 100
#define TOTAL
bool used[MAX_N * 2 * 2 * 2 * 2];
LLI total = 0;
int n;

int getNext(int pos) {
    while (used[++pos]);
    return pos;
}

void solve(int level, int maxLevel, int pos) {
    if (level == maxLevel) total++;
    else {
        pos = getNext(pos);
        FOR(i, D - 1) {
            if (((pos >> i) & 1) == 0 && !used[pos + (1 << i)]) {
                used[pos] = true;
                used[pos + (1 << i)] = true;
                solve(level + 1, maxLevel, pos);
                used[pos] = false;
                used[pos + (1 << i)] = false;
            }
        }
        if ((pos >> (D - 1)) < n - 1 && !used[pos + (1 << (D - 1))]) {
            used[pos] = true;
            used[pos + (1 << (D - 1))] = true;
            solve(level + 1, maxLevel, pos);
            used[pos] = false;
            used[pos + (1 << (D - 1))] = false;
        }
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();

        total = 0;
        solve(0, n << (D - 2), -1);

        print(total);
    }
}

