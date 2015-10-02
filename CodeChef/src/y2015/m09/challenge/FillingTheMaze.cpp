// Just brute force solution
// https://www.codechef.com/SEPT15/problems/THEGAME
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


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_ROW_SIZE 60000
#define WALL '#'
#define EMPTY 'o'
#define MAX_COMPONENTS 25000

int r, c;
char row[MAX_ROW_SIZE];

char grid[MAX_ROW_SIZE];
int components[MAX_COMPONENTS];
bool used[MAX_COMPONENTS];
int totalComponents;
int pathSize;

queue<pair<int, int> > q;
int neighbors[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};


void setWall(int row, int column) {
    grid[row * c + column] = WALL;
}

char getValue(int row, int column) {
    return grid[row * c + column];
}

int getComponent(int row, int column) {
    q.push(make_pair(row, column));
    setWall(row, column);
    int s = 0;
    while (!q.empty()) {
        s++;
        pair<int, int> item = q.front();
        q.pop();
        FOR(i, 4) {
            int r1 = item.first + neighbors[i][0];
            int c1 = item.second + neighbors[i][1];
            if (r1 >= 0 && r1 < r && c1 >= 0 && c1 < c && getValue(r1, c1) == EMPTY) {
                setWall(r1, c1);
                q.push(make_pair(r1, c1));
            }
        }
    }
    return s;
}

double check(int itemsRemaining, int cellsRemaining, double mult) {
    if (itemsRemaining == 0) {
        return mult * pathSize / cellsRemaining;
    } else {
        double result = 0;
        FOR(i, totalComponents)
            if (!used[i]) {
                used[i] = true;
                result += check(itemsRemaining - 1, cellsRemaining - components[i], mult * components[i] / cellsRemaining);
                used[i] = false;
            }
        return result;
    }
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%d %d", &r, &c);
        FOR(i, r) {
            scanf("%s", row);
            FOR(j, c) grid[i * c + j] = row[j];
        }

        pathSize = getComponent(0, 0);
        int totalSize = pathSize;
        totalComponents = 0;
        FOR(i, r) FOR(j, c)
            if (getValue(i, j) == EMPTY) {
                int cs = getComponent(i, j);
                components[totalComponents++] = cs;
                totalSize += cs;
            }

        double result = ((double)pathSize) / totalSize;
        FOR(i, totalComponents) used[i] = false;
        FOR(i, totalComponents)
            result += check(i + 1, totalSize, 1) * (i + 2);
        printf("%.10lf\n", result);
    }
}

