#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_LENGTH 1000100
#define HOLE '.'

int t;

int main(void) {
    scanf("%d", &t);
    FOR(tt, t) {
        char input[MAX_LENGTH];
        scanf("%s", input);
        int lastHoleStart = 0;
        int l = 0;
        int days = 0;
        while (true) {
            while (input[lastHoleStart] != HOLE && input[lastHoleStart]) lastHoleStart++;
            if (!input[lastHoleStart]) break;
            int lastHoleEnd = lastHoleStart + 1;
            while (input[lastHoleEnd] == HOLE) lastHoleEnd++;

            //printf("Checkign hole: %d\n", lastHoleEnd - lastHoleStart);
            if (lastHoleEnd - lastHoleStart > l) {
                //printf("Checkign hole: %d\n", lastHoleEnd - lastHoleStart);
                l = lastHoleEnd - lastHoleStart;
                days++;
            }
            lastHoleStart = lastHoleEnd + 1;
        }
        printf("%d\n", days);
    }
}
