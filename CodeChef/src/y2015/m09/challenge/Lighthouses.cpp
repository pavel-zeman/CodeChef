// 1 or 2 lighthouses are always sufficient. In the worst case, find 2 eastest islands and place lighthouses on them (SW on the northern one and NW on the southern one)
// https://www.codechef.com/SEPT15/problems/LIGHTHSE
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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


template <class type> void print(type a, bool newLine) {
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
    if (newLine) putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

void printOne(int pos, const char *dir) {
    print(1, true);
    print(pos + 1, false);
    printString(dir);
}

#define MAX_N 100010
int x[MAX_N], y[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        x[0] = getSignedInt();
        y[0] = getSignedInt();
        int minX = x[0];
        int maxX = x[0];
        int minY = y[0];
        int maxY = y[0];
        int x1 = x[0];
        int p1 = 0;
        int x2 = -1000000010;
        int p2 = 0;

        FORE(i, 1, n) {
            x[i] = getSignedInt(), y[i] = getSignedInt();
            minX = mn(minX, x[i]);
            minY = mn(minY, y[i]);
            maxX = mx(maxX, x[i]);
            maxY = mx(maxY, y[i]);
            if (x[i] > x1) {
                p2 = p1;
                x2 = x1;
                x1 = x[i];
                p1 = i;
            } else if (x[i] > x2) {
                x2 = x[i];
                p2 = i;
            }
        }
        bool found = false;
        FOR(i, n) {
            if (x[i] == minX) {
                if (y[i] == minY) {
                    printOne(i, " NE");
                    found = true;
                    break;
                } else if (y[i] == maxY) {
                    printOne(i, " SE");
                    found = true;
                    break;
                }
            } else if (x[i] == maxX) {
                if (y[i] == maxY) {
                    printOne(i, " SW");
                    found = true;
                    break;
                } else if (y[i] == minY) {
                    printOne(i, " NW");
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            // there are 2 lighthouses
            print(2, true);
            if (y[p2] > y[p1]) swap(p1, p2);
            print(p1 + 1, false);
            printString(" SW");
            print(p2 + 1, false);
            printString(" NW");
        }
    }
}

