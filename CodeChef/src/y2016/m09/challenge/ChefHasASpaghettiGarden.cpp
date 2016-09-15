// Scanline algorithm with pre-calculated sums of F
// https://www.codechef.com/SEPT16/problems/CHEFSPAG
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000009


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


#define MAX_X 11000
#define MAX_N 20
int f[MAX_X * 2];
int a[4];
int n;
struct Point {
    int x;
    int y;
} points[MAX_N];
int edge[MAX_N];


#define EDGE_UP 0
#define EDGE_DOWN 1
#define EDGE_HORIZONTAL 2

void calcF(int mm) {
    mm++;
    FORE(i, 4, mm) {
        LLI result = 0;
        FOR(j, 4) result += a[j] * (LLI)f[i - 4 + j];
        f[i] = result % MOD;
    }
    FORE(i, 1, mm) f[i] = (f[i] + f[i - 1]) % MOD;
}

void prepareEdges() {
    FOR(i, n) {
        int j = (i + 1) % n;
        if (points[j].y > points[i].y) edge[i] = EDGE_UP;
        else if (points[j].y < points[i].y) edge[i] = EDGE_DOWN;
        else edge[i] = EDGE_HORIZONTAL;
    }
}

int getPrevEdgeIndex(int x) {
    x = (x - 1 + n) % n;
    while (edge[x] == EDGE_HORIZONTAL) x = (x - 1 + n) % n;
    return x;
}

int getNextEdgeIndex(int x) {
    x = (x + 1 + n) % n;
    while (edge[x] == EDGE_HORIZONTAL) x = (x + 1 + n) % n;
    return x;
}

int compareX(int e1s, int e1e, int e2s, int e2e, int y) {
    //printf("Comparing at %d\n", y);
    int h1 = points[e1e].y - points[e1s].y;
    int h2 = points[e2e].y - points[e2s].y;
    int w1 = points[e1e].x - points[e1s].x;
    int w2 = points[e2e].x - points[e2s].x;
    LLI x1 = h2 * (LLI)(points[e1s].x * h1 + w1 * (y - points[e1s].y));
    LLI x2 = h1 * (LLI)(points[e2s].x * h2 + w2 * (y - points[e1s].y));
    return x1 < x2 ? -1 : 1;
}

int getF(int index) {
    return index >= 0 ? f[index] : 0;
}

int calc() {
    prepareEdges();

    int result = 0;
    FOR(i, n) {
        int prevIndex = getPrevEdgeIndex(i);
        LLI localResult = 0;
        if (edge[i] == EDGE_HORIZONTAL) {
            int nextIndex = getNextEdgeIndex(i);
            if (edge[prevIndex] == edge[nextIndex]) {
                if (edge[prevIndex] == EDGE_DOWN) {
                    if (points[i + 1].x > points[i].x) {
                        localResult += getF(points[nextIndex].y + points[nextIndex].x - 1);
                        localResult -= getF(points[prevIndex + 1].y + points[prevIndex + 1].x - 1);
                    }
                } else {
                    if (points[i + 1].x < points[i].x) {
                        localResult += getF(points[i].y + points[i].x);
                        localResult -= getF(points[i + 1].y + points[i + 1].x);
                    }
                }
            } else if (edge[nextIndex] == EDGE_DOWN) {
                if (points[i + 1].x < points[i].x) localResult += getF(points[i].y + points[i].x) - getF(points[i].y + points[i + 1].x);
            } else { // EDGE_UP
                if (points[i + 1].x > points[i].x) {
                    localResult += getF(points[i].y + points[i + 1].x - 1);
                    localResult -= getF(points[i].y + points[i].x - 1);
                }
            }
        } else {
            int x1 = points[i].x;
            int y1 = points[i].y;
            int x2 = points[i + 1].x;
            int y2 = points[i + 1].y;
            if (y2 < y1) {
                swap(x1, x2);
                swap(y1, y2);
            }
            int h = y2 - y1;
            int w = x2 - x1;
            int x = x1 * h;
            if (edge[i] == EDGE_DOWN) {
                y1++;
                y2++;
                x += w;
            }

            FORE(j, y1, y2) {
                if (edge[i] == EDGE_UP) localResult += getF(j + x / h);
                else localResult -= getF(j + (x + h - 1) / h - 1);
                x += w;
                //print(localResult);
            }
            if (edge[prevIndex] != edge[i]) {
                if (edge[i] == EDGE_UP) {
                    //printf("Edge up: %d %d\n", x1, y1);
                    if (points[i].x < points[prevIndex + 1].x || (points[i].x == points[prevIndex + 1].x && compareX(i, i + 1, prevIndex + 1, prevIndex, y2) < 0)) localResult -= getF(x1 + y1);
                    else localResult -= getF(x1 + y1 - 1);
                } else {
                    y1--;
                    y2--;
                    //printf("Edge down: %d %d %lld\n", x2, y2, localResult);
                    if (points[i].x < points[prevIndex + 1].x || (points[i].x == points[prevIndex + 1].x && compareX(i, i + 1, prevIndex + 1, prevIndex, y1) < 0))  localResult += getF(x2 + y2);
                    else localResult += getF(x2 + y2 - 1);
                }
            }
            //print(localResult);
        }
        result = (result + localResult) % MOD;
        if (result < 0) result += MOD;
        //printf("Result after edge %d: %d\n", i, result);
    }
    return result;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        a[3] = getInt();
        a[2] = getInt();
        a[1] = getInt();
        a[0] = getInt();
        f[0] = getInt();
        f[1] = getInt();
        f[2] = getInt();
        f[3] = getInt();
        int mm = 0;
        FOR(i, n) {
            points[i].x = getInt();
            points[i].y = getInt();
            mm = max(points[i].x + points[i].y, mm);
        }
        points[n] = points[0];
        calcF(mm);
        print(calc());


        /*int area = 0;
        FOR(i, n) area += points[i].x * points[i + 1].y - points[i + 1].x * points[i].y;
        area = abs(area);
        int b = 0;
        FOR(i, n) {
            if (edge[i] == EDGE_HORIZONTAL) b += abs(points[i].x - points[i + 1].x);
            else if (points[i].x == points[i + 1].x) b += abs(points[i].y - points[i + 1].y);
            else {
                int w = abs(points[i].x - points[i + 1].x);
                int h = abs(points[i].y - points[i + 1].y);
                b += gcd(w, h);
            }
        }
        int totalPoints = (area + b + 2) / 2;
        f[0] = f[1] = f[2] = f[3] = 1;
        a[3] = 1;
        a[0] = a[1] = a[2] = 0;
        calcF(mm * 2 + 10);
        int check = calc();
        if (check != totalPoints) {
            printf("%d - %d\n", check, totalPoints);
            printf("%d\n", f[2]);
            return 1;
        }*/
    }
}

