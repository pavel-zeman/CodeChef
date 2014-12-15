// Dynamic programming based on the start and end of an interval in the sequence. For each interval, we consider all matching pairs of brackets and then recursively calculate the number of solutions for the intervals between the brackets and behind the brackets.
// http://www.codechef.com/DEC14/problems/CHEFBR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 102
#define MOD 1000000007
#define INVALID -1

int a[MAX_N];
int result[MAX_N][MAX_N];

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

int solve(int start, int end) {
    if (result[start][end] == INVALID) {
        long long int total = 0;
        FORE(i, start, end) if (a[i] < 0) {
            int sv = -a[i];
            FORE(j, i + 1, end + 1) {
                if (a[j] == sv) {
                    long long int temp = (1 + solve(i + 1, j - 1)) % MOD;
                    total = (total + temp * (1 + solve(j + 1, end))) % MOD;
                }
            }
        }
        result[start][end] = total;
    }
    return result[start][end];
}


int main(void) {
    int n = getInt();
    FOR(i, n) a[i] = getInt();
    FOR(i, n) FOR(j, n) result[i][j] = i < j ? INVALID : 0;
    printf("%d\n", (solve(0, n - 1) + 1) % MOD);
}
