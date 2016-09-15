// Function area calculates intersection of a circle and a rectangle (both with interger coordinates)

#define IN 1
#define OUT 0
#define CIRCLE 2

struct PathElement {
    double x;
    double y;
    bool startsStraightLine;
} elements[10];
int elementCount;

int sqr(int a) {
    return a * a;
}

int isIn(int r, int px, int py) {
    if (abs(px) > r || abs(py) > r) return OUT;
    int sqr1 = sqr(px) + sqr(py);
    int sqrr = sqr(r);
    if (sqr1 < sqrr) return IN;
    if (sqr1 == sqrr) return CIRCLE;
    return OUT;
}

double getVerticalLineIntersections(int r, int x) {
    return sqrt(sqr(r) - sqr(x));
}

void addPoint(double x, double y, bool startsStraightLine) {
    elements[elementCount].x = x;
    elements[elementCount].y = y;
    elements[elementCount].startsStraightLine = startsStraightLine;
    elementCount++;
}

int addIntersection(int r, int x, int y1, int y2, int in1, int in2) {
    int originalCount = elementCount;
    if (in1 == IN) {
        addPoint(x, y1, true);
        if (in2 == OUT) addPoint(x, getVerticalLineIntersections(r, x), false);
    } else if (in1 == CIRCLE) {
        if (in2 == OUT) {
            if (y1 < 0) {
                addPoint(x, y1, true);
                addPoint(x, -y1, false);
            } else addPoint(x, y1, false);
        } else addPoint(x, y1, true);
    } else {
        if (in2 == IN) addPoint(x, -getVerticalLineIntersections(r, x), true);
        else if (in2 == CIRCLE) {
            if (y2 > 0) addPoint(x, -y2, true);
        } else if (in2 == OUT) {
            if (x > -r && x < r && y1 < 0 && y2 > 0) {
                double intersect = getVerticalLineIntersections(r, x);
                addPoint(x, -intersect, true);
                addPoint(x, intersect, false);
            }
        }
    }
    return elementCount - originalCount;
}

double getAngle(double x, double y) {
    return atan2(y, x);
}

double area(int x, int y, int r, int x1, int y1, int x2, int y2) {
    x1 -= x;
    x2 -= x;
    y1 -= y;
    y2 -= y;

    if (x1 <= -r && x2 >= r && y1 <= -r && y2 >= r) return M_PI * sqr(r);
    if (x2 <= -r || x1 >= r || y2 <= -r || y1 >= r) return 0;

    int in[4];
    in[0] = isIn(r, x2, y1);
    in[1] = isIn(r, x2, y2);
    in[2] = isIn(r, x1, y2);
    in[3] = isIn(r, x1, y1);

    if (in[0] != OUT && in[1] != OUT && in[2] != OUT && in[3] != OUT) return (x2 - x1) * (y2 - y1);
    if (in[0] != IN && in[1] != IN && in[2] != IN && in[3] != IN) {
        if ((x1 > 0 && y1 > 0) || (x2 < 0 && y1 > 0) || (x2 < 0 && y2 < 0) || (x1 > 0 && y2 < 0)) {
            return 0;
        }
    }

    elementCount = 0;
    int c = addIntersection(r, x2, y1, y2, in[0], in[1]);
    c = addIntersection(r, y2, -x2, -x1, in[1], in[2]);
    FOR(i, c) {
        swap(elements[elementCount - c + i].x, elements[elementCount - c + i].y);
        elements[elementCount - c + i].x = -elements[elementCount - c + i].x;
    }
    c = addIntersection(r, x1, -y2, -y1, in[2], in[3]);
    FOR(i, c) elements[elementCount - c + i].y = -elements[elementCount - c + i].y;

    c = addIntersection(r, -y1, x1, x2, in[3], in[0]);
    FOR(i, c) {
        swap(elements[elementCount - c + i].x, elements[elementCount - c + i].y);
        elements[elementCount - c + i].y = -elements[elementCount - c + i].y;
    }

    if (elementCount < 2) return 0;

    elements[elementCount] = elements[0];
    double totalArea = 0;
    FOR(i, elementCount) totalArea += elements[i].x * elements[i + 1].y - elements[i].y * elements[i + 1].x;
    totalArea = abs(totalArea) / 2;
    FOR(i, elementCount) {
        if (!elements[i].startsStraightLine) {
            double a1 = getAngle(elements[i].x, elements[i].y);
            double a2 = getAngle(elements[i + 1].x, elements[i + 1].y);
            if (a2 < a1) a2 += 2 * M_PI;
            totalArea += sqr(r) * (a2 - a1) / 2;
            double triangleArea = abs(elements[i].x * elements[i + 1].y - elements[i].y * elements[i + 1].x) / 2;
            if (a2 - a1 < M_PI) totalArea -= triangleArea; else totalArea += triangleArea;
        }
    }
    return totalArea;
}
