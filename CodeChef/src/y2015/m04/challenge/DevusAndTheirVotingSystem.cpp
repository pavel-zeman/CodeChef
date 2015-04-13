// Just brute force approach
// http://www.codechef.com/APRIL15/problems/DEVVOTE
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

#define MAX_N 40

int vote[MAX_N];
long long int totalPresidents = 0;
long long int permutations = 0;
long long int hist[MAX_N];

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


void run(int position, int end, int last) {
    if (position == end) {
        int votes[MAX_N];
        FOR(i, end) votes[i] = 0;
        FOR(i, end) votes[vote[i]]++;
        int maxVotes = 0;
        int presidents = 0;
        FOR(i, end) {
            if (votes[i] > maxVotes) {
                maxVotes = votes[i];
                presidents = 0;
            }
            if (votes[i] == maxVotes) presidents++;
        }
        permutations++;
        totalPresidents += presidents;
        hist[presidents]++;
    } else {
        FOR(i, end)
            if (i != last) {
                vote[position] = i;
                run(position + 1, end, i);
            }
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        totalPresidents = 0;
        permutations = 0;
        FOR(i, n + 1) hist[i] = 0;

        run(0, n, -1);
        double d = totalPresidents;
        printf("%.10lf\n", d / permutations);
        //FORE(i, 1, n + 1) printf("%d = %lld\n", i, hist[i]);
    }
}
