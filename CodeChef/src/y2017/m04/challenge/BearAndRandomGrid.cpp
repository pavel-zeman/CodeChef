// If there are many blocked cells, use brute-force, i.e. follow the path until a blocked cell is found, because the blocked cell is found quickly. Otherwise, go through all the blocked cells and calculate the first step in path, when the blocked cell is visited.
// https://www.codechef.com/APRIL17/problems/RNDGRID
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

#define MAX_L 5010
#define MAX_N 1024
#define MAX_B 300
pair<int, int> path[MAX_L];
pair<int, int> blocked[MAX_B];
bool grid[MAX_N][MAX_N];
int firstRow[2 * MAX_N], firstColumn[2 * MAX_N];
int first[2 * MAX_N][2 * MAX_N];
char s[MAX_L];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int l = getInt();
        int n = getInt();
        getString(s);
        int x = 0;
        int y = 0;
        int totalBlocked = 0;
        FOR(i, 2 * n + 3) firstRow[i] = firstColumn[i] = l;
        FOR(i, 2 * n + 3) FOR(j, 2 * n + 3) first[i][j] = l;
        FOR(i, l) {
            switch (s[i]) {
                case 'R': x++; break;
                case 'L': x--; break;
                case 'U': y--; break;
                case 'D': y++; break;
            }
            if (x >= -n && x <= n && i < firstColumn[x + n]) firstColumn[x + n] = i;
            if (y >= -n && y <= n && i < firstRow[y + n]) firstRow[y + n] = i;
            if (x >= -n && x <= n && y >= -n && y <= n && i < first[y + n][x + n]) first[y + n][x + n] = i;
            path[i] = make_pair(x, y);
        }
        FOR(i, n) {
            getString(s);
            FOR(j, n) {
                grid[i][j] = s[j] == '#';
                totalBlocked += grid[i][j] ? 1 : 0;
            }
        }
        if (totalBlocked < MAX_B) {
            int bb = 0;
            FOR(i, n) FOR(j, n) if (grid[i][j]) blocked[bb++] = make_pair(i, j);
        }
        int result = 0;
        FOR(i, n) FOR(j, n) if (!grid[i][j]) {
            int maxSteps = min(
                min(firstRow[n - i - 1], firstRow[n + n - i]),
                min(firstColumn[n - j - 1], firstColumn[n + n - j]));
            int res = maxSteps;
            if (totalBlocked < MAX_B) {
                FOR(k, totalBlocked) res = min(res, first[blocked[k].first - i + n][blocked[k].second - j + n]);
            } else {
                FOR(k, maxSteps) if (grid[i + path[k].second][j + path[k].first]) {
                    res = k;
                    break;
                }
            }
            result ^= res;
        }
        print(result);
    }
}

