// Brute force approach (tries all the possible combinations) with some special cases (all zeros and N < K)
// http://www.codechef.com/DEC14/problems/SANSKAR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define MAX_N 22

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

long long int intensity[MAX_N];
bool used[MAX_N];

int n, k;
long long int avg;

char c = 0;
long long int getInt() {
    long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

bool solve(int follower, long long int remain, int first) {
    if (follower == k) return true;
    if (remain == avg) {
        FOR(i, n) if (!used[i]) {
            used[i] = true;
            bool result = solve(follower, remain - intensity[i], i + 1);
            used[i] = false;
            return result;
        }
    } else if (remain == 0) {
        return solve(follower + 1, avg, 0);
    } else {
        FORE(i, first, n) if (!used[i] && intensity[i] <= remain) {
            used[i] = true;
            bool result = solve(follower, remain - intensity[i], i + 1);
            used[i] = false;
            if (result) return true;
        }
    }
    return false;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        avg = 0;
        FOR(i, n) avg += (intensity[i] = getInt());
        FOR(i, n) used[i] = false;
        bool ok = false;
        if (avg % k == 0 && n >= k) {
            avg /= k;
            long long int max = intensity[0];
            FOR(i, n) if (intensity[i] > max) max = intensity[i];
            if (max == 0) ok = true;
            else if (max <= avg) ok = solve(0, avg, 0);
        }
        printf("%s\n", ok ? "yes" : "no");
    }
}
