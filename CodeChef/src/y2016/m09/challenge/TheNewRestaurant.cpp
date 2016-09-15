// Cache all possible intersection areas (using sum matrix), then use sqrt decomposition to calculate the results.
// https://www.codechef.com/SEPT16/problems/CIRCLEQ
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000007


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
}


int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 50010

#define IN 1
#define OUT 0
#define CIRCLE 2
#define MAX_C_SIZE 52

struct Circle {
    int x;
    int y;
    int r;
} circles[MAX_N];

int sqr(int a) {
    return a * a;
}

double interCache[MAX_C_SIZE][MAX_C_SIZE * 2 + 1][MAX_C_SIZE * 2 + 1];

struct PathElement {
    double x;
    double y;
    bool startsStraightLine;
} elements[10];
int elementCount;

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

double areaCached(int x, int y, int r, int x1, int y1, int x2, int y2) {
    x1 -= x;
    x2 -= x;
    y1 -= y;
    y2 -= y;

    if (x2 <= -r || x1 >= r || y2 <= -r || y1 >= r) return 0;

    if (x1 < -r) x1 = -r;
    if (y1 < -r) y1 = -r;
    if (x2 > r) x2 = r;
    if (y2 > r) y2 = r;

    double result = interCache[r][x2 + r - 1][y2 + r - 1];
    if (x1 > -r) result -= interCache[r][x1 + r - 1][y2 + r - 1];
    if (y1 > -r) result -= interCache[r][x2 + r - 1][y1 + r - 1];
    if (x1 > -r && y1 > -r) result += interCache[r][x1 + r - 1][y1 + r - 1];
    return result;
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


int isIn2(int x, int y, int r, int px, int py) {
    return isIn(r, px - x, py - y) == IN;
}


#define PIECE 224
double localSum[PIECE][PIECE];
vector<int> circleIndices[PIECE][PIECE];
double verticalSum[PIECE][PIECE][PIECE];
double horizontalSum[PIECE][PIECE][PIECE];

#define SPECIAL 50
#define SPECIAL_MIN 1000
double specialSum[SPECIAL][PIECE][PIECE];
double localSpecialSum[PIECE][PIECE];
int specialCount;
int specialIndex[PIECE][PIECE];

void add(int xPiece, int yPiece, int index) {
    if (xPiece >= 0 && xPiece < PIECE && yPiece >= 0 && yPiece < PIECE)
        circleIndices[xPiece][yPiece].push_back(index);
}


double sum(int x1, int y1, int x2, int y2, int xPiece, int yPiece) {
    if (x1 == x2 || y1 == y2) return 0;
    double result = 0;
    if (circleIndices[xPiece][yPiece].size() >= SPECIAL_MIN) {
        int ind = specialIndex[xPiece][yPiece];
        int xp1 = xPiece * PIECE;
        int yp1 = yPiece * PIECE;
        if (ind < 0) {
            FOR(i, PIECE) FOR(j, PIECE) localSpecialSum[i][j] = 0;
            int xp2 = xp1 + PIECE;
            int yp2 = yp1 + PIECE;

            for(vector<int>::iterator it = circleIndices[xPiece][yPiece].begin(); it != circleIndices[xPiece][yPiece].end(); it++) {
                int xs = circles[*it].x;
                int ys = circles[*it].y;
                int rs = circles[*it].r;
                int xt1 = xs - rs;
                int xt2 = xs + rs;
                int yt1 = ys - rs;
                int yt2 = ys + rs;
                if (xt1 < xp1) xt1 = xp1;
                if (xt2 > xp2) xt2 = xp2;
                if (yt1 < yp1) yt1 = yp1;
                if (yt2 > yp2) yt2 = yp2;
                FORE(i, xt1, xt2) FORE(j, yt1, yt2)
                    localSpecialSum[i - xp1][j - yp1] += areaCached(xs, ys, rs, i, j, i + 1, j + 1);
            }
            FORE(i, 1, PIECE) localSpecialSum[i][0] += localSpecialSum[i - 1][0];
            FORE(i, 1, PIECE) localSpecialSum[0][i] += localSpecialSum[0][i - 1];
            FORE(i, 1, PIECE) FORE(j, 1, PIECE)
                localSpecialSum[i][j] += localSpecialSum[i - 1][j] + localSpecialSum[i][j - 1] - localSpecialSum[i - 1][j - 1];
            memcpy(specialSum + specialCount, localSpecialSum, sizeof(localSpecialSum));
            ind = specialIndex[xPiece][yPiece] = specialCount++;
        }
        x1 -= xp1;
        x2 -= xp1;
        y1 -= yp1;
        y2 -= yp1;
        result = specialSum[ind][x2 - 1][y2 - 1];
        if (x1 > 0) result -= specialSum[ind][x1 - 1][y2 - 1];
        if (y1 > 0) result -= specialSum[ind][x2 - 1][y1 - 1];
        if (x1 > 0 && y1 > 0) result += specialSum[ind][x1 - 1][y1 - 1];
    } else {
        for(vector<int>::iterator it = circleIndices[xPiece][yPiece].begin(); it != circleIndices[xPiece][yPiece].end(); it++) {
            result += areaCached(circles[*it].x, circles[*it].y, circles[*it].r, x1, y1, x2, y2);
        }
    }
    return result;
}

void prepareVerticalSum() {
    FOR(i, PIECE) {
        int x = i * PIECE;
        FOR(j, PIECE) {
            double localResult[PIECE];
            FOR(k, PIECE) localResult[k] = 0;
            int y = j * PIECE;
            for(vector<int>::iterator it = circleIndices[i][j].begin(); it != circleIndices[i][j].end(); it++) {
                int xs = circles[*it].x;
                int ys = circles[*it].y;
                int rs = circles[*it].r;
                int x1 = xs - rs;
                int x2 = xs + rs;
                if (x1 < x) x1 = x;
                if (x2 > x + PIECE) x2 = x + PIECE;
                FORE(k, x1, x2) localResult[k - x] += areaCached(xs, ys, rs, k, y, k + 1, y + PIECE);
            }
            verticalSum[i][j][0] = localResult[0];
            FORE(k, 1, PIECE) verticalSum[i][j][k] = verticalSum[i][j][k - 1] + localResult[k];
        }
    }
}

void prepareHorizontalSum() {
    FOR(i, PIECE) {
        int x = i * PIECE;
        FOR(j, PIECE) {
            double localResult[PIECE];
            FOR(k, PIECE) localResult[k] = 0;
            int y = j * PIECE;
            for(vector<int>::iterator it = circleIndices[i][j].begin(); it != circleIndices[i][j].end(); it++) {
                int xs = circles[*it].x;
                int ys = circles[*it].y;
                int rs = circles[*it].r;
                int y1 = ys - rs;
                int y2 = ys + rs;
                if (y1 < y) y1 = y;
                if (y2 > y + PIECE) y2 = y + PIECE;
                FORE(k, y1, y2) localResult[k - y] += areaCached(xs, ys, rs, x, k, x + PIECE, k + 1);
            }
            horizontalSum[i][j][0] = localResult[0];
            FORE(k, 1, PIECE) horizontalSum[i][j][k] = horizontalSum[i][j][k - 1] + localResult[k];
        }
    }
}


void prepareIntersectCache() {
    FORE(x, 1, MAX_C_SIZE) {
        int s1 = x * 2 + 1;
        FOR(i, s1) FOR(j, s1) interCache[x][i][j] = area(0, 0, x, -x, -x, i - x + 1, j - x + 1);
    }
}


int main(void) {
    FOR(i, PIECE) FOR(j, PIECE) specialIndex[i][j] = -1;
    prepareIntersectCache();

    int n = getInt();
    int q = getInt();
    FOR(i, n) {
        int x = circles[i].x = getInt();
        int y = circles[i].y = getInt();
        int r = circles[i].r = getInt();
        int xPiece = x / PIECE;
        int yPiece = y / PIECE;
        int x1 = xPiece * PIECE;
        int y1 = yPiece * PIECE;
        int x2 = x1 + PIECE;
        int y2 = y1 + PIECE;
        circleIndices[xPiece][yPiece].push_back(i);
        bool added = false;
        if (isIn2(x, y, r, x2, y1)) {
            add(xPiece + 1, yPiece, i);
            add(xPiece + 1, yPiece - 1, i);
            add(xPiece, yPiece - 1, i);
            added = true;
        }
        if (isIn2(x, y, r, x2, y2)) {
            add(xPiece + 1, yPiece, i);
            add(xPiece + 1, yPiece + 1, i);
            add(xPiece, yPiece + 1, i);
            added = true;
        }
        if (isIn2(x, y, r, x1, y2)) {
            add(xPiece - 1, yPiece, i);
            add(xPiece - 1, yPiece + 1, i);
            add(xPiece, yPiece + 1, i);
            added = true;
        }
        if (isIn2(x, y, r, x1, y1)) {
            add(xPiece - 1, yPiece, i);
            add(xPiece - 1, yPiece - 1, i);
            add(xPiece, yPiece - 1, i);
            added = true;
        }
        if (!added) {
            if (x + r > x2) add(xPiece + 1, yPiece, i);
            if (x - r < x1) add(xPiece - 1, yPiece, i);
            if (y + r > y2) add(xPiece, yPiece + 1, i);
            if (y - r < y1) add(xPiece, yPiece - 1, i);
        }
    }
    FOR(i, PIECE) {
        int xPiece = i * PIECE;
        FOR(j, PIECE) {
            int yPiece = j * PIECE;
            localSum[i][j] = sum(xPiece, yPiece, xPiece + PIECE, yPiece + PIECE, i, j);
        }
    }
    FORE(i, 1, PIECE) localSum[i][0] += localSum[i - 1][0];
    FORE(i, 1, PIECE) localSum[0][i] += localSum[0][i - 1];
    FORE(i, 1, PIECE) FORE(j, 1, PIECE)
        localSum[i][j] += localSum[i - 1][j] + localSum[i][j - 1] - localSum[i - 1][j - 1];

    prepareVerticalSum();
    prepareHorizontalSum();

    FOR(i, q) {
        int x1 = getInt();
        int y1 = getInt();
        int x2 = getInt();
        int y2 = getInt();
        int x1Piece = x1 / PIECE;
        int y1Piece = y1 / PIECE;
        int x2Piece = x2 / PIECE;
        int y2Piece = y2 / PIECE;
        int x1Mod = x1 % PIECE;
        int x2Mod = x2 % PIECE;
        int y1Mod = y1 % PIECE;
        int y2Mod = y2 % PIECE;
        double result = 0;
        if (x1Piece == x2Piece) {
            if (y1Piece == y2Piece) result = sum(x1, y1, x2, y2, x1Piece, y1Piece);
            else {
                int y = y1Piece * PIECE + PIECE;
                result = sum(x1, y1, x2, y, x1Piece, y1Piece++);
                while (y + PIECE < y2) {
                    result += verticalSum[x1Piece][y1Piece][x2Mod - 1];
                    if (x1Mod > 0) result -= verticalSum[x1Piece][y1Piece][x1Mod - 1];
                    y1Piece++;
                    y += PIECE;
                }
                result += sum(x1, y, x2, y2, x1Piece, y1Piece);
            }
        } else if (y1Piece == y2Piece) {
            int x = x1Piece * PIECE + PIECE;
            result = sum(x1, y1, x, y2, x1Piece++, y1Piece);


            while (x + PIECE < x2) {
                result += horizontalSum[x1Piece][y1Piece][y2Mod - 1];
                if (y1Mod > 0) result -= horizontalSum[x1Piece][y1Piece][y1Mod - 1];
                x1Piece++;
                x += PIECE;
            }
            result += sum(x, y1, x2, y2, x1Piece, y1Piece);
        } else {
            result = localSum[x2Piece - 1][y2Piece - 1] -
                localSum[x1Piece][y2Piece - 1] -
                localSum[x2Piece - 1][y1Piece] +
                localSum[x1Piece][y1Piece];
            result += sum(x1, y1, x1Piece * PIECE + PIECE, y1Piece * PIECE + PIECE, x1Piece, y1Piece);
            result += sum(x2Piece * PIECE, y1, x2, y1Piece * PIECE + PIECE, x2Piece, y1Piece);
            result += sum(x1, y2Piece * PIECE, x1Piece * PIECE + PIECE, y2, x1Piece, y2Piece);
            result += sum(x2Piece * PIECE, y2Piece * PIECE, x2, y2, x2Piece, y2Piece);

            FORE(i, y1Piece + 1, y2Piece) {
                result += verticalSum[x1Piece][i][PIECE - 1];
                if (x1Mod > 0) result -= verticalSum[x1Piece][i][x1Mod - 1];
                if (x2Mod > 0) result += verticalSum[x2Piece][i][x2Mod - 1];
            }

            FORE(i, x1Piece + 1, x2Piece) {
                result += horizontalSum[i][y1Piece][PIECE - 1];
                if (y1Mod > 0) result -= horizontalSum[i][y1Piece][y1Mod - 1];
                if (y2Mod > 0) result += horizontalSum[i][y2Piece][y2Mod - 1];
            }
        }
        printf("%.6lf\n", result);
    }
}

