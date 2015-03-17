// Calculate the end of maximum substring with at most k same digits for each possible start of the string. Then use binary search to find the first start position with end after r.
// http://www.codechef.com/MARCH15/problems/STRSUB
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

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

int s[MAX_N];
int n, k, q;

int end[MAX_N];
long long int totals[MAX_N];

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

void getString() {
    int pos = 0;
    while (!(c >= '0' && c <= '1')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '1') {
        s[pos++] = c - '0';
        c = getc_unlocked(stdin);
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        q = getInt();
        getString();

        int currentEnd = 0;
        int numDigits[2];
        numDigits[0] = numDigits[1] = 0;
        long long int total = 0;
        FOR(i, n) {
            while (currentEnd < n && numDigits[s[currentEnd]] + 1 <= k) {
                numDigits[s[currentEnd]]++;
                currentEnd++;
            }
            end[i] = currentEnd;
            numDigits[s[i]]--;

            total += currentEnd - i;
            totals[i] = total;
        }


        FOR(i, q) {
            int l = getInt() - 1;
            int r = getInt();

            // use binary search to find first position with end after r
            int ll = l;
            int rr = r - 1;
            while (ll < rr) {
                int mid = (ll + rr) >> 1;
                if (end[mid] < r) ll = mid + 1; else rr = mid - 1;
            }
            int firstAfterR = ll;
            while (firstAfterR < r && end[firstAfterR] < r) firstAfterR++;

            // calculate the total as sum of subtotals + all substrings starting at firstAfterR
            total = totals[firstAfterR - 1];
            if (l > 0) total -= totals[l - 1];
            long long int temp = r - firstAfterR;
            total += temp * (temp + 1) >> 1;

            printf("%lld\n", total);
        }
    }
}
