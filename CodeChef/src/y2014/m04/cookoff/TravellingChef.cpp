// First we need to get the A, B, C and D by solving 4 equations for 4 variables. Then we need to find roots of the velocity function and calculate the distance between each consecutive roots pair (if the velocity function is a cubic function, this formula is used to solve it: http://www.1728.org/cubic2.htm)
// http://www.codechef.com/COOK45/problems/TCP
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


double matrix[4][5];
double roots[4];
int rootCount = 0;

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

void swap(int a, int b) {
    FOR(i, 5) {
        double temp = matrix[a][i];
        matrix[a][i] = matrix[b][i];
        matrix[b][i] = temp;
    }
}

void print() {
    return;
    FOR(i, 4) {
        FOR(j, 5) printf("%lf ", matrix[i][j]);
        printf("\n");
    }
}

double velocity(double t) {
    double a = matrix[0][4];
    double b = matrix[1][4];
    double c = matrix[2][4];
    double d = matrix[3][4];
    return a * t * t * t + b * t * t + c * t + d;
}

double distance(double t) {
    double a = matrix[0][4];
    double b = matrix[1][4];
    double c = matrix[2][4];
    double d = matrix[3][4];
    double result = a * t * t * t * t / 4 + b * t * t * t / 3 + c * t * t / 2 + d * t;
    return result;
}

int cmp(const void *p1, const void *p2) {
    double x1 = (*(double *)p1);
    double x2 = (*(double *)p2);
    if (x1 < x2) return -1;
    if (x1 == x2) return 0;
    return 1;
}


void findRoots() {
    double a = matrix[0][4];
    double b = matrix[1][4];
    double c = matrix[2][4];
    double d = matrix[3][4];

    if (a == 0 && b == 0 && c == 0) {
        rootCount = 0;
    } else if (a == 0 && b == 0) {
        rootCount = 1;
        roots[0] = -d / c;
    } else if (a == 0) {
        double det = c * c - 4 * b * d;
        if (det < 0) rootCount = 0; else
        if (det == 0) {
            rootCount = 1;
            roots[0] = -c / 2 / b;
        } else {
            rootCount = 2;
            roots[0] = (-c - sqrt(det)) / 2 / b;
            roots[1] = (-c + sqrt(det)) / 2 / b;
        }
    } else {
        double f = ((3 * c / a) - (b * b / a / a)) / 3;
        double g = ((2 * b * b * b / a / a / a) - (9 * b * c / a / a) + (27 * d / a)) / 27;
        double h = (g * g / 4) + (f * f * f / 27);
        //printf("H: %lf ", h);
        if (h > 0) {
            double r = -g / 2 + sqrt(h);
            double s = cbrt(r);
            double t = -g/2 - sqrt(h);
            double u = cbrt(t);
            rootCount = 1;
            roots[0] = (s + u) - (b / 3 / a);
        } else if (f == 0 && g == 0 && h == 0) {
            rootCount = 1;
            roots[0] = -cbrt(d / a);
        } else {
            double i = sqrt(g * g / 4 - h);
            double j = cbrt(i);
            double k = acos(-g / 2 / i);
            double l = -j;
            double m = cos(k / 3);
            double n = sqrt(3) * sin(k / 3);
            double p = -b / 3 / a;
            roots[0] = 2 * j * cos(k / 3) - b / 3 / a;
            roots[1] = l * (m + n) + p;
            roots[2] = l * (m - n) + p;
            rootCount = 3;
        }
    }

    qsort(roots, rootCount, sizeof(roots[0]), cmp);
}

double abs(double a) {
    return a < 0 ? -a : a;
}

int main(void) {
    int n = getInt();
    FOR(tt, n) {
        double t = getInt();
        FOR(i, 4) {
            double ct = getInt();
            int cv = getInt();

            matrix[i][0] = ct * ct * ct;
            matrix[i][1] = ct * ct;
            matrix[i][2] = ct;
            matrix[i][3] = 1;
            matrix[i][4] = cv;
        }
        print();
        FOR(i, 4) {
            if (matrix[i][i] == 0) {
                int row = -1;
                FORE(j, i + 1 , 4) if (matrix[j][i] != 0) {
                    row = j;
                    break;
                }
                swap(i, row);
            }
            double q = matrix[i][i];
            FORE(j, i, 5) matrix[i][j] /= q;
            FORE(j, i + 1, 4) {
                q = matrix[j][i];
                FORE(k, i, 5) matrix[j][k] -= q * matrix[i][k];
            }
        }
        for(int i=3;i>=0;i--) {
            FOR(j, i) {
                double q = matrix[j][i];
                FORE(k, i, 5) matrix[j][k] -= q * matrix[i][k];
            }
        }
        print();
        findRoots();

        double roots2[4];
        int root2Count = 0;
        FOR(i, rootCount) {
            if (roots[i] > 0 && roots[i] < t) {
                roots2[root2Count++] = roots[i];
            }
        }


        double total = 0;
        if (root2Count == 0) {
            total = abs(distance(t) - distance(0));
        } else {
            double last = distance(0);
            FOR(i, root2Count) {
                double temp = distance(roots2[i]);
                total += abs(temp - last);
                last = temp;
            }
            total += abs(distance(t) - last);
        }

        printf("%lf\n", total);
    }
}
