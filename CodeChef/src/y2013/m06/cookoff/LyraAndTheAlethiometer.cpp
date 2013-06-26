#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXINPUT 2000

char input[MAXINPUT];
int inputLength;

char maxString[MAXINPUT];
int maxLength = 0;

bool isAlpha(int pos) {
    return input[pos] >= 'A' && input[pos] <= 'Z';
}

void checkString() {
    int lastStart = 0;

    while (true) {
        while ((isAlpha(lastStart) || input[lastStart] == '0') && lastStart < inputLength) lastStart++;
        if (lastStart >= inputLength) return;
        int lastEnd = lastStart + 1;
        while (!isAlpha(lastEnd) && lastEnd < inputLength) lastEnd++;
        if (lastEnd - lastStart > maxLength || (lastEnd - lastStart == maxLength && strncmp(maxString, input + lastStart, maxLength) < 0)) {
            maxLength = lastEnd - lastStart;
            strncpy(maxString, input + lastStart, maxLength);
            maxString[maxLength] = 0;
        }
        lastStart = lastEnd + 1;
    }
}

int main(void) {
    scanf("%s", input);
    inputLength = strlen(input);

    checkString();
    FOR(i, inputLength) {
        if (isAlpha(i)) {
            input[i] = '9';
            checkString();
            input[i] = 'A';
        }
    }
    if (maxLength == 0) maxString[0] = '0',maxString[1] = 0;
    printf("%s", maxString);
}
