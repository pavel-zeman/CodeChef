// Test all possible a x b sub-matrices. For each of them, the result is sub-matrix sum - sub-matrix maximum * a * b. Maximum can be calculated using 2 sliding windows, which can be implemented in linear time using approach described at http://articles.leetcode.com/sliding-window-maximum/.
// https://www.codechef.com/JUNE16/problems/CHSQARR
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


#define MAX_N 1024
int n, m;
short aa[MAX_N][MAX_N];
int sum[MAX_N][MAX_N];
int a, b;


struct SlidingWindow {
    deque<int> q;
    short a[MAX_N];

    void insert(int index) {
        while (!q.empty() && a[index] >= a[q.back()]) q.pop_back();
        q.push_back(index);
    }

    void remove(int firstInvalid) {
        while (!q.empty() && q.front() <= firstInvalid) q.pop_front();
    }

    int max() {
        return a[q.front()];
    }

    void clear() {
        q.clear();
    }
} sw[MAX_N];


int getSum(int x1, int y1, int x2, int y2) {
    return sum[y2][x2] - sum[y1 - 1][x2] - sum[y2][x1 - 1] + sum[y1 - 1][x1 - 1];
}


int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, n) FOR(j, m) aa[i + 1][j + 1] = getInt();
    FORE(i, 1, n + 1) FORE(j, 1, m + 1) sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + aa[i][j];
    FOR(i, m + 1) FOR(j, n + 1) sw[i].a[j] = aa[j][i];

    int q = getInt();
    FOR(i, q) {
        a = getInt();
        b = getInt();
        int result = n * m * 1024;

        FORE(k, 1, m + 1) {
            sw[k].clear();
            FORE(l, 1, a) sw[k].insert(l);
        }

        FORE(k, 1, n - a + 2) {
            SlidingWindow sofar;
            int y1 = k, y2 = k + a - 1;

            FORE(l, 1, b) {
                sw[l].insert(y2);
                sofar.a[l] = sw[l].max();
                sofar.insert(l);
                sw[l].remove(y1);
            }

            FORE(l, 1, m - b + 2) {
                int x1 = l, x2 = l + b - 1;
                sw[x2].insert(y2);

                sofar.a[x2] = sw[x2].max();
                sofar.insert(x2);

                sw[x2].remove(y1);

                result = min(result, sofar.max() * a * b - getSum(x1, y1, x2, y2));

                sofar.remove(l);
            }
        }
        print(result);
    }


}

