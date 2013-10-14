// Calculating triangle area using Heron's formula
// http://www.codechef.com/OCT13/problems/HELPLIRA
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

double sqr(int a) {
    return a * a;
}

int main(void) {
    int n = getInt();
    double min = 1e30;
    double max = -1;
    int minIndex = -1;
    int maxIndex = -1;

    FOR(i, n) {
        int x1 = getInt();
        int y1 = getInt();
        int x2 = getInt();
        int y2 = getInt();
        int x3 = getInt();
        int y3 = getInt();

        double a = sqrt(sqr(x2 - x1) + sqr(y2 - y1));
        double b = sqrt(sqr(x3 - x2) + sqr(y3 - y2));
        double c = sqrt(sqr(x3 - x1) + sqr(y3 - y1));
        double s = (a + b + c) / 2;
        double area = s * (s - a) * (s - b) * (s - c);

        if (area >= max) {
            max = area;
            maxIndex = i + 1;
        }
        if (area <= min) {
            min = area;
            minIndex = i + 1;
        }
    }
    printf("%d %d\n", minIndex, maxIndex);
}
