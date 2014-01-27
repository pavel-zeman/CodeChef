// Just simple algorithm  
// http://www.codechef.com/JAN14/problems/TOURBUS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 52

int x[MAX_N], y[MAX_N];
int n;
bool neighbor[MAX_N][MAX_N];
bool backupNeighbor[MAX_N][MAX_N];

int tours;
int tour[MAX_N * MAX_N * 10];

int tempTours;
int tempTourLocations;
int tempTour[MAX_N * MAX_N * 10];



void addTour(int length, int *data) {
    tempTours++;
    tempTour[tempTourLocations++] = length;
    FOR(i, length) tempTour[tempTourLocations++] = data[i];
}

int getNeighbor(int a) {
    FOR(i, n) if (neighbor[a][i]) return i;
    return -1;
}


int orientation(int p, int q, int r) {
    int val = (y[q] - y[p]) * (x[r] - x[q]) -
              (x[q] - x[p]) * (y[r] - y[q]);
    if (val == 0) printf("Error %d %d %d\n", p, q, r);
    if (val == 0) *((char *)0) = 0;
    return val > 0 ? 0 : 1;
}

bool doIntersect(int p1, int q1, int p2, int q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    return (o1 != o2 && o3 != o4);
}

bool isOK(int a, int b, int length, int *data, int start) {
    FORE(i, start, length) if (data[i] == b) return false;
    FORE(i, start, length - 1) if (doIntersect(a, b, data[i], data[i + 1])) return false;
    return true;
}


int main(void) {
    scanf("%d", &n);
    FOR(i, n) scanf("%d %d", &x[i], &y[i]);
    FOR(i, n) {
        char row[MAX_N];
        scanf("%s", row);
        FOR(j, n) backupNeighbor[i][j] = row[j] == 'Y';
    }

    tours = n * n + 1;
    int maxL = n;
    if (maxL > 20) maxL = 20;

    FOR(k, n) FOR(l, maxL) {
        tempTours = 0;
        tempTourLocations = 0;
        FOR(i, n) FOR(j, n) neighbor[i][j] = backupNeighbor[i][j];

        FOR(i, n) FOR(j, n) {
            int ii = (i + k) % n;
            int jj = (j + l) % n;
            if (neighbor[ii][jj]) {
                int data[MAX_N];
                int c = 2;
                data[0] = ii;
                data[1] = jj;
                neighbor[ii][jj] = neighbor[jj][ii] = false;
                int foundCount = 1;
                while (foundCount > 0) {
                    foundCount = 0;
                    //int items[MAX_N];
                    int last = data[c - 1];
                    FOR(i, n)
                        if (neighbor[last][i] && isOK(last, i, c - 1, data, 0)) {
                            foundCount = 1;
                            neighbor[last][i] = neighbor[i][last] = false;
                            data[c++] = i;
                            break;
                        }
                }
                if (c > 2 && neighbor[data[c - 1]][ii]) {
                    int last = data[c - 1];
                    if (isOK(last, ii, c - 1, data, 1)) {
                        neighbor[last][ii] = neighbor[ii][last] = false;
                        data[c++] = ii;
                    }
                }
                addTour(c, data);
            }
        }

        if (tempTours < tours) {
            tours = tempTours;
            FOR(i, tempTourLocations) tour[i] = tempTour[i];
        }
    }

    printf("%d\n", tours);
    int k = 0;
    FOR(i, tours) {
        int length = tour[k++];
        printf("%d", length - 1);
        FOR(j, length) printf(" %d", tour[k++]);
        printf("\n");
    }
}
