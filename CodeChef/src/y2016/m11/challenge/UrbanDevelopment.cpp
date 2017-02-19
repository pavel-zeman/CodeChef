// Iterate over horizontal lines ordered by their y coordinate and use Fenwick tree to calculate number of intersections. Then swap horizontal and vertical lines and repeat.
// https://www.codechef.com/NOV16/problems/URBANDEV
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

struct Line {
    int x, y;
    int e;
    int order;

    Line() {}

    Line(int x, int y, int e, int order) {
        this->x = x;
        this->y = y;
        this->e = e;
        this->order = order;
    }
};

// Fenwick tree
#define MAX_SIZE 100020

template <class type> class Fenwick {
private:
    type tree[MAX_SIZE];
    int n;

public:
    type read(int idx){
        type sum = 0;
        while (idx > 0){
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    void update(int idx , type val){
        while (idx <= n){
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    void reset(int n) {
        this->n = n;
        FOR(i, n + 1) tree[i] = 0;
    }
};

Fenwick<int> fenwick;

#define MAX_COORD 100010
#define MAX_N 100010

vector<Line> horizontal;
vector<Line> vertical;
vector<int> start[MAX_COORD];
vector<int> stop[MAX_COORD];
vector<Line> lines[MAX_COORD];
int result[MAX_N];

int main(void) {
    int n = getInt();
    FOR(i, n) {
        int x1 = getInt();
        int y1 = getInt();
        int x2 = getInt();
        int y2 = getInt();
        if (x1 == x2) { // vertical
            if (y1 > y2) swap(y1, y2);
            vertical.push_back(Line(x1, y1, y2, i));
        } else { // horizontal
            if (x1 > x2) swap(x1, x2);
            horizontal.push_back(Line(x1, y1, x2, i));
        }
    }

    FOR(xx, 2) {
        for(vector<Line>::iterator it = vertical.begin(); it != vertical.end(); it++) {
            start[it->y].push_back(it->x);
            stop[it->e].push_back(it->x);
        }
        for(vector<Line>::iterator it = horizontal.begin(); it != horizontal.end(); it++) lines[it->y].push_back(*it);
        fenwick.reset(MAX_COORD);
        set<int> ends;
        FOR(i, MAX_COORD) {
            ends.clear();
            FOR(j, start[i].size()) {
                fenwick.update(start[i][j], 1);
                ends.insert(start[i][j]);
            }
            FOR(j, stop[i].size()) ends.insert(stop[i][j]);

            for(vector<Line>::iterator it = lines[i].begin(); it != lines[i].end(); it++) {
                result[it->order] = fenwick.read(it->e) - fenwick.read(it->x - 1);
                if (ends.find(it->x) != ends.end()) result[it->order]--;
                if (ends.find(it->e) != ends.end()) result[it->order]--;
            }
            FOR(j, stop[i].size()) fenwick.update(stop[i][j], -1);
        }
        if (xx == 0) {
            vector<Line> temp;
            temp.resize(horizontal.size());
            copy(horizontal.begin(), horizontal.end(), temp.begin());
            horizontal.resize(vertical.size());
            copy(vertical.begin(), vertical.end(), horizontal.begin());
            vertical.resize(temp.size());
            copy(temp.begin(), temp.end(), vertical.begin());
            FOR(i, horizontal.size()) swap(horizontal[i].x, horizontal[i].y);
            FOR(i, vertical.size()) swap(vertical[i].x, vertical[i].y);
            FOR(i, MAX_COORD) start[i].clear(), stop[i].clear(), lines[i].clear();
        }
    }

    LLI total = 0;
    FOR(i, n) total += result[i];
    print(total >> 1);
    FOR(i, n) print(result[i]);
}

