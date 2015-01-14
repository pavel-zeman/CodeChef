// IF we have a set of numbers, which can create any sum up to their total, and add another number less than or equal to total + 1, then we can again create any sum up to the total of the new set. The algorithm calculates the running total, checks the condition and updates the total.
// http://www.codechef.com/JAN15/problems/CLPERM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define FORI(c, t) for(vector<t>::iterator it = c.begin();it != c.end(); it++)


vector<int> missing;

char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

long long int sum(long long int start, long long int end) {
    if (end < start) return 0;
    return (end + start) * (end - start + 1) / 2;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        missing.clear();
        int n = getInt();
        int k = getInt();
        FOR(i, k) missing.push_back(getInt());
        sort(missing.begin(), missing.end());

        int lastValid = 0;
        long long int total = 0;
        bool ok = true;
        FORI(missing, int) {
            total += sum(lastValid, *it - 1);
            lastValid = *it + 1;
            if (*it > total) {
                ok = false;
                break;
            }
        }
        if (ok) total += sum(lastValid, n);
        puts((total & 1) == 0 ? "Chef" : "Mom");
    }
}
