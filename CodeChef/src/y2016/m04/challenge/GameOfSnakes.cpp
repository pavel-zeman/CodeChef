// Just simple naive algorithm
// https://www.codechef.com/APRIL16/problems/SNAKGAME
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

#define MAX_N 650
bool full[MAX_N][MAX_N];
int moves[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int sx = 1, sy = 1;
int hx, hy, tx, ty;
int dir = 0;
int n, m;

void createNewSnake() {
    while (full[sx][sy]) {
        if (++sx > n) {
            sx = 1;
            sy++;
        }
        if (sy > m) {
            puts("EXIT");
            exit(0);
        }
    }
    hx = tx = sx;
    hy = ty = sy;
    dir = 0;
    printf("NEW %d %d\n", sx, sy);
    full[sx][sy] = true;
}

bool moveSnake(int &x, int &y, int initTurn) {
    int nextTurn = 4 - initTurn;
    dir = (dir + initTurn) & 3;
    FOR(i, 4) {
        int nx = x + moves[dir][0];
        int ny = y + moves[dir][1];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !full[nx][ny]) {
            full[nx][ny] = true;
            printf("MOVE %d %d %d %d\n", x, y, nx, ny);
            x = nx;
            y = ny;
            return true;
        }
        dir = (dir + nextTurn) & 3;
    }
    return false;
}

int main(void) {
    int blocked;
    scanf("%d %d %d", &n, &m, &blocked);
    FOR(i, blocked) {
        int x, y;
        scanf("%d %d", &x, &y);
        full[x][y] = true;
    }
    bool createNew = true;
    while (true) {
        if (createNew) {
            createNewSnake();
            createNew = false;
        } else {
            if (!moveSnake(hx, hy, 3)) {
                if (!moveSnake(tx, ty, 1)) {
                    createNewSnake();
                }
            }
        }
        fflush(stdout);

        char command[10];
        scanf("%s", command);
        if (!strcmp(command, "EXIT")) return 0;
        else if (!strcmp(command, "FREEZE")) {
            int temp;
            scanf("%d", &temp);
        } else if (!strcmp(command, "MOVE")) {
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            full[c][d] = true;
        } else if (!strcmp(command, "NEW")) {
            int a, b;
            scanf("%d %d", &a, &b);
            full[a][b] = true;
        }
    }

}

