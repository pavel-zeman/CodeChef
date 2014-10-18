// Number of different non-empty subsequences (http://stackoverflow.com/questions/5151483/how-to-find-the-number-of-distinct-subsequences-of-a-string)
// http://www.codechef.com/AUG14/problems/MOU2H
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1000009
#define MOD 1000000009
#define MAX_V 8000010

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

void putInt(int a) {
    char buffer[20];
    int s = 0;
    if (a == 0) {
        buffer[0] = '0';
        s = 1;
    } else {
        while (a > 0) {
            buffer[s++] = '0' + a % 10;
            a /= 10;
        }
    }
    s--;
    while (s >= 0) putc_unlocked(buffer[s--], stdout);
    putc_unlocked('\n', stdout);
}

int diff[MAX_N];
int sum[MAX_N];
int last[MAX_V];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int lastIn = getInt();
        FORE(i, 1, n) {
            int temp = getInt();
            diff[i] = temp - lastIn + 4000000;
            last[diff[i]] = -1;
            lastIn = temp;
        }

        sum[0] = 1;
        FORE(i, 1, n) {
            int temp = sum[i - 1] << 1;
            if (last[diff[i]] >= 0) {
                temp -= sum[last[diff[i]] - 1];
                if (temp < 0) temp += MOD;
            }
            sum[i] = temp % MOD;
            last[diff[i]] = i;
        }
        putInt((sum[n - 1] - 1+ MOD) % MOD);
    }
}
