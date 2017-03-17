// Alternate between ascending and descending rows. Sort the numbers and then try to place each number to row, which minimizes the cost.
// https://www.codechef.com/MARCH17/problems/SORTROW
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

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

int sqr(int a) {
    return a * a;
}

#define MAX_N 310
int a[MAX_N][MAX_N];
int ra[MAX_N][MAX_N];
int at[MAX_N * MAX_N];
pair<int, int> origPos[MAX_N * MAX_N];
bool moved[MAX_N][MAX_N];
int n;
int pos[MAX_N];
int totalDist[MAX_N][MAX_N];


bool asc[MAX_N];
bool used[MAX_N][MAX_N];


void generate() {
    srand(time(NULL));
    int n = 300;
    FOR(i, n * n) {
        int pos = rand() % (n * n);
        while (a[pos / n][pos % n]) pos = (pos + 1) % (n * n);
        a[pos / n][pos % n] = i + 1;
    }
    FOR(i, n) {
        FOR(j, n) printf("%d ", a[i][j]);
        printf("\n");
    }
}

void printAll() {
    /*FOR(i, n) {
        printf("=%2d ", i);
        FOR(j, n) printf("%4d ", a[i][j]);
        printf("\n");
    }*/
}
int maxd = 10;

int getSection(int r, int c, int v) {
    return asc[r] ? v / n : n - 1 - v / n;
}

int getSection(int r, int c) {
    return getSection(r, c, a[r][c]);
}

int dist(int i, int j, int s1, int k, int l, int s2) {
    return sqr(j - s1) + 2 * sqr(i - k) + sqr(l - s2);
}

int dp[4 * MAX_N][2 * MAX_N];
int dc[4 * MAX_N][2 * MAX_N];
int sr;

int findDp(int used, int pos1) {
    if (used == 4 * n) return 0;
    int res = dp[used][pos1];
    if (res < 0) {
        int pos2 = used - pos1;
        res = n * n * n * 10;
        int v = at[used];
        int cc = -1;
        pair<int, int> o = origPos[v];
        if (pos1 < 2 * n) {
            int r1 = sqr(o.first - (sr + pos1 / n)) + sqr(o.second - (pos1 % n)) + findDp(used + 1, pos1 + 1);
            if (r1 < res) {
                res = r1;
                cc = 0;
            }
        }
        if (pos2 < 2 * n) {
            int row = 3 - pos2 / n;
            int column = n - 1 - pos2 % n;
            int r1 = sqr(o.first - (sr + row)) + sqr(o.second - column) + findDp(used + 1, pos1);
            if (r1 < res) {
                res = r1;
                cc = 1;
            }
        }
        dp[used][pos1] = res;
        dc[used][pos1] = cc;
    }
    return res;
}

int getMn(int row, int column) {
    return asc[row] ? (column > 0 ? a[row][column - 1] : 0) : (column < n - 1 ? a[row][column + 1] : 0);
}

int getMx(int row, int column) {
    return asc[row] ? (column < n - 1 ? a[row][column + 1] : n * n + 10) : (column > 0 ? a[row][column - 1] : n * n + 10);
}


LLI calcCost() {
    LLI cost = 0;
    FOR(i, n) {
        FOR(j, n) {
            pair<int, int> o = origPos[a[i][j]];
            int c = sqr(i - o.first) + sqr(j - o.second);
            cost += c;
            //printf("%4d ", (int)sqrt(c));
        }
        //printf("\n");
    }
    return cost;
}

int main(void) {
    n = getInt();
    FOR(i, n) FOR(j, n) {
        a[i][j] = getInt();
        origPos[a[i][j]] = make_pair(i, j);
        at[i * n + j] = a[i][j];
    }
    sort(at, at + n * n);
    printAll();
    LLI targetCost = 1000000000;
    int resAsc = 0;
    int at2[MAX_N];
    FOR(i, n) {
        FOR(j, n) at2[j] = a[i][j];
        sort(at2, at2 + n);
        int cost1 = 0;
        FOR(j, n) cost1 += sqr(origPos[at2[j]].second - j);
        int cost2 = 0;
        FOR(j, n) cost2 += sqr(origPos[at2[j]].second - (n - j - 1));
        asc[i] = cost1 < cost2;
    }
    FOR(i, n) pos[i] = 0;
    FOR(i, n * n) {
        int v = at[i];
        auto op = origPos[v];
        int minDist = n * n * n;
        int row = 0, column = 0;
        FOR(j, n) {
            if (pos[j] < n) {
                int cc = asc[j] ? pos[j] : n - 1 - pos[j];
                int d = sqr(j - op.first) + sqr(cc - op.second);
                if (d < minDist) {
                    row = j;
                    column = cc;
                    minDist = d;
                }
            }
        }
        a[row][column] = v;
        totalDist[row][column] = minDist;
        pos[row]++;
    }
    LLI cost = calcCost();
    if (cost < targetCost) {
        targetCost = cost;
        FOR(i, n) FOR(j, n) ra[i][j] = a[i][j];
    }


    FOR(x, 2) {
        FOR(i, n) asc[i] = (i & 1) == x;
        FOR(i, n) pos[i] = 0;
        FOR(i, n * n) {
            int v = at[i];
            auto op = origPos[v];
            int minDist = n * n * n;
            int row = 0, column = 0;
            FOR(j, n) {
                if (pos[j] < n) {
                    int cc = asc[j] ? pos[j] : n - 1 - pos[j];
                    int d = sqr(j - op.first) + sqr(cc - op.second);
                    if (d < minDist) {
                        row = j;
                        column = cc;
                        minDist = d;
                    }
                }
            }
            a[row][column] = v;
            totalDist[row][column] = minDist;
            pos[row]++;
        }
        LLI cost = calcCost();
        if (cost < targetCost) {
            targetCost = cost;
            FOR(i, n) FOR(j, n) ra[i][j] = a[i][j];
        }
    }
    /*FOR(x, 3000) {
        int row = 0, column = 0;
        int maxD = 0;
        FOR(i, n) FOR(j, n) if (!used[i][j] && totalDist[i][j] > maxD) {
            maxD = totalDist[i][j];
            row = i;
            column = j;
        }
        int mn1 = getMn(row, column);
        int mx1 = getMx(row, column);
        int v1 = a[row][column];
        int d1 = totalDist[row][column];
        auto op1 = origPos[a[row][column]];
        int minD = n * n * n;
        int r2 = -1, c2 = -1;
        FOR(i, n) FOR(j, n) if (i != row || j != column) {
            int v = a[i][j];
            int mn2 = getMn(i, j);
            int mx2 = getMx(i, j);
            if (v > mn1 && v < mx1 && v1 > mn2 && v1 < mx2) {
                int origDist = d1 + totalDist[i][j];
                auto op2 = origPos[v];
                int newDist = sqr(op2.first - row) + sqr(op2.second - column) + sqr(op1.first - i) + sqr(op1.second - j);
                if (newDist < origDist && newDist < minD) {
                    minD = newDist;
                    r2 = i;
                    c2 = j;
                }
            }
        }
        if (r2 >= 0) {
            //printf("Found\n");
            auto op2 = origPos[a[r2][c2]];;
            swap(a[row][column], a[r2][c2]);
            totalDist[row][column] = sqr(op2.first - row) + sqr(op2.second - column);
            totalDist[r2][c2] = sqr(op1.first - r2) + sqr(op1.second - c2);
        } else used[row][column] = true;
    }*/
    //sort(totalDist, totalDist + n * n);
    //for(int i = n * n - 1; i >= 0; i--) printf("%d = %d\n", i, (int)sqrt(totalDist[i]));
    //printAll();

    FOR(i, n) FOR(j, n) a[i][j] = ra[i][j];
    LLI totalCost = calcCost();

    /*printAll();
    FOR(i, n) {
        if (asc[i]) sort(a[i], a[i] + n); else sort(a[i], a[i] + n, greater<int>());
    }*/
    printAll();
    FOR(i, n) FOR(j, n) print(ra[i][j]);
    fprintf(stderr, "%lld %d %lf\n", totalCost, (int)sqrt(totalCost / (n * n)), totalCost / (double)(n * n * n));
}

