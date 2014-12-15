//
// http://www.codechef.com/DEC14/problems/RIN
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

using namespace std;

#define MAX_N 102
#define MAX_M 102
#define INVALID -1
#define MISSING -2

int x[MAX_N][MAX_M];
int result[MAX_N][MAX_M];

vector<int> successors[MAX_N];
bool predecessorExists[MAX_N];

int n, m;


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

int max(int a, int b) {
    return a > b ? a : b;
}

int solve(int course, int start) {
    if (start >= m) return -1;
    if (result[course][start] == MISSING) {
        int later = solve(course, start + 1);
        int now = -1;
        if (x[course][start] != INVALID) {
            now = x[course][start];
            FOR(i, (int)successors[course].size()) {
                int temp = solve(successors[course][i], start + 1);
                if (temp == INVALID) {
                    now = INVALID;
                    break;
                }
                now += temp;
            }
        }
        result[course][start] = max(later, now);
    }
    return result[course][start];
}

int main(void) {
    n = getInt();
    m = getInt();
    int k = getInt();
    FOR(i, n) FOR(j, m) x[i][j] = getInt();
    FOR(i, n) FOR(j, m) result[i][j] = MISSING;

    FOR(i, n) predecessorExists[i] = false;
    FOR(i, k) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        successors[a].push_back(b);
        predecessorExists[b] = true;
    }

    int total = 0;
    FOR(i, n) if (!predecessorExists[i]) total += solve(i, 0);
    printf("%.2f\n", total / (float)n);
}
