// Based on the initial move, the cat can end-up anywhere in 2/6 of the hexagon. So in the first move, block the cat to limit its lifespace to 1/6 of the hexagon. Then prepare a cage and catch the cat inside.
// https://www.codechef.com/MARCH17/problems/BEARTRAP
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

#define MAX_N 100
#define GRID_C 50
//bool blocked[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int cr, cc;
int n;
vector<pair<int, int> > blocked;
int rotates;
pair<int, int> rotatedCat;


int neighbors[6][2] = {{0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}, {1, 0}};

pair<int, int> rotate(int r, int c, int cc) {
    if (cc < 0) cc += 6;
    pair<int, int> temp;
    pair<int, int> result(r, c);
    FOR(i, cc) {
        temp = result;
        result.first = -temp.second;
        result.second = temp.first + temp.second;
    }
    //printf("Rotating %d: %d %d", cc, result.first, result.second);
    return result;
}

pair<int, int> rotate(pair<int, int> x, int cc) {
    return rotate(x.first, x.second, cc);
}


bool isOnEdge(int r, int c) {
    return (r >= -n && r <= n) && (r == -n || r == n ||
        (r <= 0 && c == n) || (r >= 0 && r + c == n) || (r >= 0 && c == -n) || (r <= 0 && r + c == -n));
}

bool isIn(int r, int c) {
    return (r >= -n && r <= 0 && r + c >= -n && c <= n) ||
        (r >= 0 && r <= n && c >= -n && r + c <= n);

}

int getDist(int a, int b) {
    return dist[a + GRID_C][b + GRID_C];
}

void setDist(int a, int b, int c) {
    dist[a + GRID_C][b + GRID_C] = c;
}

bool isBlocked(int a, int b) {
    FOR(i, blocked.size()) if (blocked[i].first == a && blocked[i].second == b) return true;
    return false;
}

bool isBlockedRotated(int a, int b) {
    auto res = rotate(a, b, -rotates);
    return isBlocked(res.first, res.second);
}


void addBlocked(int a, int b) {
    blocked.push_back(make_pair(a, b));
}

void updateDist() {
    queue<pair<int, int> > distQueue;
    FOR(i, MAX_N) FOR(j, MAX_N) dist[i][j] = -1;
    FORE(i, -n, n + 1)
        FORE(j, -n, n + 1) {
            if (isOnEdge(i, j)) {
                if (!isBlocked(i, j)) {
                    distQueue.push(make_pair(i, j));
                    setDist(i, j, 0);
                }
            }
        }
    while (!distQueue.empty()) {
        pair<int, int> p = distQueue.front();
        distQueue.pop();
        int r = p.first;
        int c = p.second;
        FOR(i, 6) {
            int r1 = r + neighbors[i][0];
            int c1 = c + neighbors[i][1];
            if (isIn(r1, c1) && !isBlocked(r1, c1) && getDist(r1, c1) < 0) {
                setDist(r1, c1, getDist(r, c) + 1);
                distQueue.push(make_pair(r1, c1));
            }
        }
    }
}





void printGrid() {
    FORE(i, -n, 1) {
        FOR(j, -i) printf("  ");
        FORE(j, -n - i, n + 1)
            if (cr == i && cc == j) printf("CC  ");
            else if (getDist(i, j) < 0) printf("##  "); else printf("%02d  ", getDist(i, j));
        printf("\n");
    }
    FORE(i, 1, n + 1) {
        FOR(j, i) printf("  ");
        FORE(j, -n, n - i + 1)
            if (cr == i && cc == j) printf("CC  ");
            else if (getDist(i, j) < 0) printf("##  "); else printf("%02d  ", getDist(i, j));

        printf("\n");
    }

}

void moveCat() {
    char instruct[10];
    getString(instruct);
    cr = getSignedInt();
    cc = getSignedInt();
    rotatedCat = rotate(cr, cc, rotates);
    //printf("Cat moved to %d %d\n", cr, cc);

    /*int nr = -n, nc = -n, mm = n;
    vector<pair<int, int> > poss;
    FOR(i, 6) {
        int r1 = cr + neighbors[i][0];
        int c1 = cc + neighbors[i][1];
        if (isIn(r1, c1) && !isBlocked(r1, c1) && getDist(r1, c1) <= mm) {
            if (getDist(r1, c1) < mm) {
                poss.clear();
                mm = getDist(r1, c1);
            }
            poss.push_back(make_pair(r1, c1));
        }
    }
    int pp = rand() % poss.size();
    nr = poss[pp].first;
    nc = poss[pp].second;
    printf("Moving cat to %d %d\n", nr, nc);
    cr = nr;
    cc = nc;
    rotatedCat = rotate(cr, cc, rotates);
    printGrid();*/
}


void block(int r, int c) {
    printf("Blocking %d %d\n", r, c);
    addBlocked(r, c);
    updateDist();
    printGrid();
}

void block(pair<int, int> c) {
    c = rotate(c, -rotates);
    addBlocked(c.first, c.second);
    //updateDist();
    printf("BLOCK %d %d\n", c.first, c.second);
    fflush(stdout);
    //printGrid();
}



int main(void) {
    srand(time(0));
    int t = getInt();
    getInt(); // ignore value of m
    n = 10;
    FOR(tt, t) {
        int minc, maxc;
        cr = cc = 0;
        blocked.clear();

        moveCat();
        rotates = 0;
        pair<int, int> target(0, 1);
        while (rotate(cr, cc, rotates) != target) rotates++;
        block(make_pair(0, 2));

        moveCat();
        rotates = 0;
        target = make_pair(2, -1);
        while (rotate(cr, cc, rotates) != target) rotates++;
        block(make_pair(10, minc = maxc = -5));

        moveCat();
        block(make_pair(8, -4));

        moveCat();
        int nextColumn = rotatedCat.second <= -2 ? -7 : -3;
        block(make_pair(10, nextColumn));
        minc = min(minc, nextColumn);
        maxc = max(maxc, nextColumn);

        moveCat();
        block(make_pair(8, nextColumn + 1));

        moveCat();
        if (rotatedCat.second == -5) nextColumn = -9;
        else if (rotatedCat.second == -1) nextColumn = -1;
        else nextColumn = nextColumn == -3 ? -7 : -3;
        block(make_pair(10, nextColumn));
        minc = min(minc, nextColumn);
        maxc = max(maxc, nextColumn);

        moveCat();
        block(make_pair(8, nextColumn + 1));

        moveCat();
        block(make_pair(10, rotatedCat.second - 1));

        FOR(i, 4) {
            moveCat();
            if (rotatedCat.second == minc + 1 && !isBlockedRotated(9, minc)) block(make_pair(9, minc));
            else if (rotatedCat.second == maxc && !isBlockedRotated(9, maxc + 1)) block(make_pair(9, maxc + 1));
            else if (!isBlockedRotated(10, minc + 1) && !isBlockedRotated(8, minc + 2)) block(make_pair(8, minc + 2));
            else if (!isBlockedRotated(10, maxc - 1) && !isBlockedRotated(8, maxc)) block(make_pair(8, maxc));
            else if (!isBlockedRotated(10, minc + 1)) block(make_pair(10, minc + 1));
            else if (!isBlockedRotated(10, maxc - 1)) block(make_pair(10, maxc - 1));
            else if (rotatedCat.second == minc + 2 && !isBlockedRotated(8, minc + 2)) block(make_pair(8, minc + 2));
            else if (!isBlockedRotated(8, minc + 4)) block(make_pair(8, minc + 4));
            else block(make_pair(8, minc + 2));
        }
        moveCat();
        bool ok = false;
        FORE(i, minc + 1, maxc + 2) if (!isBlockedRotated(8, i)) {
            block(make_pair(8, i));
            ok = true;
            break;
        }
        if (!ok) {
            FORE(i, minc, maxc + 1) if (!isBlockedRotated(10, i)) {
                block(make_pair(10, i));
                ok = true;
                break;
            }
            if (!ok && !isBlockedRotated(9, minc)) {
                block(make_pair(9, minc));
                ok = true;
            }
            if (!ok && !isBlockedRotated(9, maxc + 1)) {
                block(make_pair(9, maxc + 1));
                ok = true;
            }
        }


        char temp[10];
        getString(temp); // WIN
    }

    /*n = 10;
    updateDist();
    printGrid();
    int step = 0;
    while (true) {
        step++;
        moveCat();
        int r = getSignedInt();
        int c = getSignedInt();
        printf("Step: %d\n", step);
        block(r, c);
    }*/



    /*int t = getInt();
    FOR(tt, t) {
    }*/
}

