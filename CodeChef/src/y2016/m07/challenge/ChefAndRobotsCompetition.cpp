// Simple search for both robots starting from their start positions
// https://www.codechef.com/JULY16/problems/CHEFARC
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

#define MAX_N 128
bool empty[MAX_N][MAX_N];
int robot[2][MAX_N][MAX_N];
queue<pair<int, int>> q[2];
int n, m;


bool move(int r, int k, int step) {
    while (!q[r].empty()) {
        pair<int, int> p = q[r].front();
        if (robot[r][p.first][p.second] >= step) break;
        q[r].pop();
        int i1 = max(p.first - k, 0);
        int i2 = min(p.first + k + 1, n);
        int j1 = max(p.second - k, 0);
        int j2 = min(p.second + k + 1, m);
        FORE(i, i1, i2) FORE(j, j1, j2) {
            if (abs(i - p.first) + abs(j - p.second) <= k && empty[i][j] && robot[r][i][j] < 0) {
                if (robot[r ^ 1][i][j] >= 0) return true;
                robot[r][i][j] = step;
                q[r].push(make_pair(i, j));
            }
        }

    }
    return false;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        int k1 = getInt();
        int k2 = getInt();
        FOR(i, n) FOR(j, m) empty[i][j] = getInt() == 0, robot[0][i][j] = robot[1][i][j] = -1;
        robot[0][0][0] = 0;
        robot[1][0][m - 1] = 0;
        int result = -1;
        if (m == 1) result = 0;
        else {
            FOR(i, 2) while(!q[i].empty()) q[i].pop();
            q[0].push(make_pair(0, 0));
            q[1].push(make_pair(0, m - 1));

            result = 1;
            bool found = false;
            while (!q[0].empty() || !q[1].empty()) {
                if (move(0, k1, result)) {
                    found = true;
                    break;
                }
                if (move(1, k2, result)) {
                    found = true;
                    break;
                }
                result++;
            }
            if (!found) result = -1;
        }
        print(result);
    }
}

