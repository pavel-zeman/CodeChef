// Calculate the "center of gravity" and move all the individuals around this center.
// https://www.codechef.com/AUG15/problems/SCLUSTER
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

int abs(int a) {
    return a >= 0 ? a : -a;
}

#define MAX_K 2010
#define MAX_N 64

int neighbors[][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};

int n, k;

class Individual {
public:
    int row;
    int column;
    int l;
    int index;

    bool operator<(const Individual &other) const {
        return this->l < other.l || this->l == other.l && this->row < other.row;
    }

} individuals[MAX_K];

int grid[MAX_N][MAX_N];

bool full[MAX_N][MAX_N];
bool possible[MAX_N][MAX_N];

void addPossible(int x, int y) {
    FOR(i, sizeof(neighbors) / sizeof(neighbors[0])) {
        int x1 = x + neighbors[i][0];
        int y1 = y + neighbors[i][1];
        if (x1 >= 0 && y1 >= 0 && x1 < n && y1 < n) possible[x1][y1] = true;
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        FOR(i, n) FOR(j, n) {
            int index = getInt();
            if (index > 0) {
                individuals[index - 1].row = i;
                individuals[index - 1].column = j;
                individuals[index - 1].index = index;
            }
        }
        FOR(i, k) individuals[i].l = getInt();
        sort(individuals, individuals + k);
        FOR(i, n) FOR(j, n) full[i][j] = possible[i][j] = false;

        float fx = 0, fy = 0, fw = 0;
        FOR(i, k) {
            fx += individuals[i].row * 1.0 / individuals[i].l;
            fy += individuals[i].column * 1.0 / individuals[i].l;
            fw += 1.0 / individuals[i].l;
        }
        int x = fx / fw;
        int y = fy / fw;
        //printf("Found: %f %f\n", fx / fw, fy / fw);
        individuals[k - 1].row = x;
        individuals[k - 1].column = y;
        full[x][y] = true;
        addPossible(x, y);

        for(int i = k - 2;i>=0;i--) {
            x = individuals[i].row;
            y = individuals[i].column;
            if (!possible[x][y] || full[x][y]) {
                int minDist = n * n;
                int tx = -1, ty = -1;
                FOR(j, n) FOR(k, n) if (!full[j][k] && possible[j][k]) {
                    int dist = abs(j - x) + abs(k - y);
                    if (dist < minDist) {
                        minDist = dist;
                        tx = j;
                        ty = k;
                    }
                }
                full[tx][ty] = true;
                addPossible(tx, ty);
                individuals[i].row = tx;
                individuals[i].column = ty;
            } else {
                full[x][y] = true;
                addPossible(x, y);
            }
        }

        FOR(i, n) FOR(j, n) grid[i][j] = 0;
        FOR(i, k) grid[individuals[i].row][individuals[i].column] = individuals[i].index;

        FOR(i, n) {
            FOR(j, n) printf("%d ", grid[i][j]);
            printf("\n");
        }
    }
}

