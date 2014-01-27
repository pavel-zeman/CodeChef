// No magic - simply read the input and use strstr to find the requested string
// http://www.codechef.com/JAN14/problems/ERROR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100100

char string[MAX_N];

int main(void) {
    int t;
    gets(string);
    t = atoi(string);
    FOR(tt, t) {
        gets(string);
        printf("%s\n", strstr(string, "010") != NULL || strstr(string, "101") != NULL ? "Good" : "Bad");
    }
}

