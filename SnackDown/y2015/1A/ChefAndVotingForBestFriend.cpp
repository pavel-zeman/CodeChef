// For the votes to be valid, the sum must be equal to N and all votes must be less than N.
// http://www.codechef.com/SNCK151A/problems/CHEFVOTE
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

#define MAX_N 100

int n;
int votes[MAX_N];

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


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        int sum = 0;
        bool possible = true;
        FOR(i, n) {
            votes[i] = getInt();
            sum += votes[i];
            if (votes[i] >= n) possible = false;
        }
        if (sum != n) possible = false;

        if (!possible) printf("-1\n");
        else {
            FOR(i, n) {
                int mx = -1;
                int pos = -1;
                for(int j=n-1;j>=0;j--) if (j != i && votes[j] > mx) {
                    mx = votes[j];
                    pos = j;
                }
                votes[pos]--;
                printf("%d ", pos + 1);
            }
            printf("\n");
        }

    }
}
