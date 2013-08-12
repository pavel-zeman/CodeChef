// No magic - simply calculates cost per month and chooses the cheapest one
// http://www.codechef.com/AUG13/problems/HELLO
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        double defaultRate;
        int minutes;
        int n;
        scanf("%lf %d %d", &defaultRate, &minutes, &n);

        int minPlan = 0;
        double minValue = defaultRate * minutes;

        FOR(i, n) {
            int months;
            double rate;
            int cost;
            scanf("%d %lf %d", &months, &rate, &cost);
            double value = rate * minutes + (double)cost / months;
            if (value < minValue) {
                minPlan = i + 1;
                minValue = value;
            }
        }
        printf("%d\n", minPlan);
    }
}
