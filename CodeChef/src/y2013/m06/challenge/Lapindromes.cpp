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
    char string[10000];
    scanf("%d", &t);
    FOR(i, t) {
        char freq1[26], freq2[26];
        scanf("%s", string);

        int l = strlen(string);
        int half = l / 2;

        calcFreqs(string, half, freq1);
        calcFreqs(string + l - half, half, freq2);

        bool same = true;
        FOR(i, 26) if (freq1[i] != freq2[i]) { same = false; break;}
        printf("%s\n", same ? "YES" : "NO");
    }
}
