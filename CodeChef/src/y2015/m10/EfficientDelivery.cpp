// Implemented only for graphs of 1000 or less nodes. Calculates shortest distances between all pairs of nodes and then tries to process orders starting from the ones with highest reward.
// https://www.codechef.com/OCT15/problems/EFFDELIV
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

#define MAX_ALL 1020
#define INF 10000000
#define MAX_K 100010

#define MOVE 0
#define PICK 1
#define DELIVER 2

int n, m, k;
int s, d, w;
int dist[MAX_ALL][MAX_ALL];
int totalDist[MAX_ALL][MAX_ALL];

struct Order {
    int a, b, v, c;
    int num;

    bool operator<(const Order & other) const {
        return c > other.c;
    }
} orders[MAX_K];

struct Operation {
    int type;
    int parameter;

    Operation(int type, int parameter) {
        this->type = type;
        this->parameter = parameter;
    }
};

vector<Operation> operations;


void calcTotalDist() {
    FOR(i, n) FOR(j, n) totalDist[i][j] = dist[i][j];
    FOR(k, n) FOR(i, n) FOR(j, n)
        if (totalDist[i][j] > totalDist[i][k] + totalDist[k][j])
            totalDist[i][j] = totalDist[i][k] + totalDist[k][j];
}

void go(int destination) {
    int t = totalDist[s][destination];
    d -= t;
    while (s != destination) {
        FOR(i, n) if (i != s && dist[s][i] + totalDist[i][destination] == t) {
            operations.push_back(Operation(MOVE, i + 1));
            t -= dist[s][i];
            s = i;
            break;
        }
    }
}

void pick(int what) {
    operations.push_back(Operation(PICK, what));
}

void deliver(int what) {
    operations.push_back(Operation(DELIVER, what));
}


int main(void) {
    clock_t startTime = clock();

    n = getInt();
    m = getInt();
    if (n > MAX_ALL) {
        print(0);
        return 0;
    }
    FOR(i, n) FOR(j, n) dist[i][j] = INF;
    FOR(i, n) dist[i][i] = 0;
    FOR(i, m) {
        int x = getInt() - 1;
        int y = getInt() - 1;
        int z = getInt();
        dist[x][y] = dist[y][x] = z;
    }
    calcTotalDist();
    k = getInt();
    FOR(i, k) {
        orders[i].a = getInt() - 1;
        orders[i].b = getInt() - 1;
        orders[i].v = getInt();
        orders[i].c = getInt();
        orders[i].num = i + 1;
    }
    sort(orders, orders + k);
    s = getInt() - 1;
    d = getInt();
    w = getInt();


    for(int i=0;i<k && clock() - startTime < 4.0 * CLOCKS_PER_SEC;i++) {
        if (totalDist[s][orders[i].a] + totalDist[orders[i].a][orders[i].b] <= d) {
            go(orders[i].a);
            pick(orders[i].num);
            go(orders[i].b);
            deliver(orders[i].num);
        }
    }
    print(operations.size());
    FOR(i, operations.size())
        printf("%d %d\n", operations[i].type, operations[i].parameter);
}

