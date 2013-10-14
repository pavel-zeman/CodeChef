// Swap cells whenever possible
// http://www.codechef.com/OCT13/problems/EDSTGRID
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_SIZE 110
#define BLACK 'B'

#define OPERATION_SWITCH 1
#define OPERATION_TO_BLACK 2
#define OPERATION_TO_WHITE 3

int n, m, c2, c3;
char board[MAX_SIZE][MAX_SIZE];

using namespace std;

struct operation {
    int type;
    int r1, c1;
    int r2, c2;
};

struct coordinate {
    int r, c;
};

vector<operation> operations;
vector<coordinate> fixedCoordinates;
vector<coordinate> black;

int abs(int a) {
    return a >= 0 ? a : -a;
}

int distance(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {

        scanf("%d%d%d%d", &n, &m, &c2, &c3);

        FOR(i, n) scanf("%s", board[i]);

        operations.clear();

        struct coordinate center;
        int cr = n / 2;
        int cc = m / 2;
        int totalBlack = 0;
        int minDist = n + m + 100;
        int minPos = 0;
        FOR(i, n) FOR(j, m)
            if (board[i][j] == BLACK) {
                coordinate coordinate;
                coordinate.r = i;
                coordinate.c = j;
                black.push_back(coordinate);

                int d = distance(i, j, cr, cc);
                if (d < minDist) {
                    minDist = d;
                    minPos = totalBlack;
                    center = coordinate;
                }
                totalBlack++;
            }

        totalBlack--;
        fixedCoordinates.clear();
        fixedCoordinates.push_back(center);
        black.erase(black.begin() + minPos);

        while (totalBlack-- > 0) {
            coordinate nearestFixed;
            minDist = n + m + 100;
            FOR(i, (int)black.size()) {
                FOR(j, (int)fixedCoordinates.size()) {
                    int d = distance(black[i].r, black[i].c, fixedCoordinates[j].r, fixedCoordinates[j].c);
                    if (d < minDist) {
                        minDist = d;
                        nearestFixed = fixedCoordinates[j];
                        center = black[i];
                        minPos = i;
                    }
                }
            }
            black.erase(black.begin() + minPos);

            //printf("Going from %d %d to %d %d\n", center.r, center.c, nearestFixed.r, nearestFixed.c);

            operation operation;
            if (minDist - 1 < c3) {
                int step = center.c > nearestFixed.c ? -1 : 1;
                while (center.c != nearestFixed.c && (center.c + step != nearestFixed.c || center.r != nearestFixed.r)) {
                    operation.type = OPERATION_SWITCH;
                    operation.r1 = center.r;
                    operation.r2 = center.r;
                    operation.c1 = center.c;
                    operation.c2 = center.c + step;
                    operations.push_back(operation);
                    center.c += step;
                }
                step = center.r > nearestFixed.r ? -1 : 1;
                while (center.r != nearestFixed.r && (center.c != nearestFixed.c || center.r  + step != nearestFixed.r)) {
                    operation.type = OPERATION_SWITCH;
                    operation.r1 = center.r;
                    operation.r2 = center.r + step;
                    operation.c1 = center.c;
                    operation.c2 = center.c;
                    operations.push_back(operation);
                    center.r += step;
                }
                fixedCoordinates.push_back(center);
            } else {
                operation.type = OPERATION_TO_WHITE;
                operation.r1 = center.r;
                operation.c1 = center.c;
                operations.push_back(operation);
            }

        }

        printf("%d\n", operations.size());
        FOR(i, (int)operations.size()) {
            printf("%d %d %d", operations[i].type, operations[i].r1 + 1, operations[i].c1 + 1);
            if (operations[i].type == OPERATION_SWITCH) printf(" %d %d", operations[i].r2 + 1, operations[i].c2 + 1);
            printf("\n");
        }
    }
}
