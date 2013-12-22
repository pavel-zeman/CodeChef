// Simple math
// http://www.codechef.com/COOK41/problems/GERALD04
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
        int t1, t2;
        scanf("%d:%d", &t1, &t2);
        int friendArrival = t1 * 60 + t2;
        scanf("%d:%d", &t1, &t2);
        int chefDeparture = t1 * 60 + t2;
        int dist;
        scanf("%d", &dist);

        double plan1 = friendArrival - chefDeparture + dist;
        double plan2 = 0;
        if (friendArrival - chefDeparture >= 2 * dist) {
            plan2 = friendArrival - chefDeparture;
        } else if (friendArrival - chefDeparture >= dist) {
            double friendRemain = friendArrival - chefDeparture - dist;
            double part = friendRemain / dist;
            double remain = (1 - part) * dist / 2;
            plan2 = friendArrival - chefDeparture + remain;
        } else {
            double part = ((double)(chefDeparture + dist - friendArrival)) / dist;
            double remain = (1 - part) * dist / 2;
            plan2 = dist + remain;
        }
        printf("%.1lf %.1lf\n", plan1, plan2);

    }
}

