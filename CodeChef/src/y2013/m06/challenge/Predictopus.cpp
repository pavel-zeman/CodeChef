#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


void calcFreqs(char *data, int length, char *freq) {
    FOR(i, 26) freq[i] = 0;
    FOR(i, length) {
        freq[data[i] - 'a']++;
    }
}


int main(void) {
    int t;
    scanf("%d", &t);
    FOR(i, t) {
        double prob;
        scanf("%lf", &prob);
        if (prob < 0.5) prob = 1 - prob;
        printf("%lf\n",  (1 - prob) * 10000 * (2 * prob + 1) + 10000 * (2 * prob - 1));
    }
}
