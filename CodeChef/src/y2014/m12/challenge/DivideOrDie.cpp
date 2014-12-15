// Only simple partial solution for angles less than or equal to 4
// http://www.codechef.com/DEC14/problems/DIVIDEN
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define LINE 1
#define CIRCLE 2
#define MAX_OPERATIONS 20

struct Point {
    double x, y;
} v, r1, r2;

Point offset;
Point d[10];
double angle;
int operations;


struct Operation {
    int type;
    Point a, b, c;
} operation[MAX_OPERATIONS];

void readPoint(Point *point) {
    scanf("%lf %lf", &point->x, &point->y);
}

void move(Point *point, Point *offset) {
    point->x += offset->x;
    point->y += offset->y;
}

void rotate(Point *point, double angle) {
    double x = point->x * cos(angle) - point->y * sin(angle);
    double y = point->x * sin(angle) + point->y * cos(angle);
    point->x = x;
    point->y = y;
}


double dist(Point *p1, Point *p2) {
    double dx = p1->x - p2->x;
    double dy = p1->y - p2->y;
    return sqrt(dx * dx + dy * dy);
}

Point intersect(Point *a, Point *b) {
    Point result;
    double d = dist(a, b);
    double k = sqrt( ((d + d) * (d + d) - d * d) * d * d) / 4;
    int sign = b->y > a->y ? 1 : - 1;
    result.x = (b->x + a->x) / 2 + sign * 2 * (b->y - a->y) * k / d / d;
    result.y = (b->y + a->y) / 2 - sign * 2 * (b->x - a->x) * k / d / d;
    return result;
}

int main(void) {
    readPoint(&v);
    readPoint(&r1);
    readPoint(&r2);

    offset.x = -v.x;
    offset.y = -v.y;

    // move to zero
    move(&v, &offset);
    move(&r1, &offset);
    move(&r2, &offset);

    // rotate
    if (r2.x == 0) {
        angle = r2.y > 0 ? M_PI / 2 : 3 * M_PI / 2;
    } else {
        angle = atan(r2.y / r2.x);
        if (r2.x < 0) angle += M_PI;
    }
    angle = -angle;
    rotate(&r1, angle);
    rotate(&r2, angle);

    operations = 0;
    int currentAngle = floor(atan(r1.y / r1.x) / M_PI * 180 + 0.5);
    if (currentAngle == 3) {
        printf("NO\n");
    } else {
        if (currentAngle > 1) {
            operation[operations].type = LINE;
            operation[operations].a = v;
            operation[operations].b = r1;
            operations++;

            operation[operations].type = LINE;
            operation[operations].a = v;
            operation[operations].b = r2;
            operations++;

            operation[operations].type = CIRCLE;
            operation[operations].c = v;
            operation[operations].a = v;
            operation[operations].b = r1;
            operations++;

            double dd = dist(&v, &r1);
            Point c1;
            c1.x = dd;
            c1.y = 0;
            operation[operations].type = CIRCLE;
            operation[operations].c = c1;
            operation[operations].a = c1;
            operation[operations].b = r1;
            operations++;

            operation[operations].type = CIRCLE;
            operation[operations].c = r1;
            operation[operations].a = c1;
            operation[operations].b = r1;
            operations++;

            if (currentAngle == 2) {
                d[0] = intersect(&c1, &r1);
            } else {
                // angle is 4
                d[1] = intersect(&c1, &r1);
                Point c2 = c1;
                rotate(&c2, 2 * M_PI / 180);

                operation[operations].type = LINE;
                operation[operations].a = v;
                operation[operations].b = d[1];
                operations++;

                operation[operations].type = CIRCLE;
                operation[operations].c = r1;
                operation[operations].a = c2;
                operation[operations].b = r1;
                operations++;

                operation[operations].type = CIRCLE;
                operation[operations].c = c2;
                operation[operations].a = c2;
                operation[operations].b = r1;
                operations++;

                d[0] = intersect(&r1, &c2);

                operation[operations].type = CIRCLE;
                operation[operations].c = c2;
                operation[operations].a = c2;
                operation[operations].b = c1;
                operations++;

                operation[operations].type = CIRCLE;
                operation[operations].c = c1;
                operation[operations].a = c2;
                operation[operations].b = c1;
                operations++;

                d[2] = intersect(&c1, &c2);
            }
        }
        printf("YES\n");
        offset.x = -offset.x;
        offset.y = -offset.y;
        FOR(i, operations) {
            rotate(&operation[i].a, -angle);
            rotate(&operation[i].b, -angle);
            rotate(&operation[i].c, -angle);
            move(&operation[i].a, &offset);
            move(&operation[i].b, &offset);
            move(&operation[i].c, &offset);

            switch (operation[i].type) {
                case LINE:
                    printf("Line %.10lf %.10lf %.10lf %.10lf\n", operation[i].a.x, operation[i].a.y, operation[i].b.x, operation[i].b.y);
                    break;
                case CIRCLE:
                    printf("Circle %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n", operation[i].c.x, operation[i].c.y, operation[i].a.x, operation[i].a.y, operation[i].b.x, operation[i].b.y);
                    break;
            }
        }
        printf("Answer\n");
        FOR(i, currentAngle - 1) {
            rotate(&d[i], -angle);
            move(&d[i], &offset);
            printf("%.10lf %.10lf\n", d[i].x, d[i].y);
        }
    }
}
