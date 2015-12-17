// Use brute force to calculate minimum cost for each combination of a "branch" and an interval and then calculate minimums for each interval. Then use dynamic programming to assemble the intervals.
// https://www.codechef.com/DEC15/problems/CHEFGIRL
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

int getString(char *start) {
    char *data = start;
    while (!(ccc >= 'a' && ccc <= 'z')) ccc = getc_unlocked(stdin);
    while (ccc >= 'a' && ccc <= 'z') {
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

void fail() {
    *((char *)0) = 0;
}


#define MAX_SEGMENT 32
#define MAX_N 100010

int minSegment[MAX_SEGMENT][MAX_SEGMENT];
int result[MAX_SEGMENT][MAX_SEGMENT];

int next[MAX_N];
pair<int, int> interval[MAX_N];
vector<int> first;


int solve(int from, int to) {
    if (result[from][to] < 0) {
        int tmp = minSegment[from][to];
        FORE(i, from, to) tmp = min(tmp, minSegment[from][i] + solve(i + 1, to));
        result[from][to] = tmp;
    }
    return result[from][to];
}

int main(void) {
    FOR(i, MAX_SEGMENT) FOR(j, MAX_SEGMENT) minSegment[i][j] = 1000000000;
    FOR(i, MAX_SEGMENT) FOR(j, MAX_SEGMENT) result[i][j] = -1;
    getInt();
    int m = getInt();
    FOR(i, m) {
        int from = getInt() - 1;
        int to = getInt() - 1;
        next[from] = to;
        interval[to].first = getInt() - 1;
        interval[to].second = getInt() - 1;
        if (from == 0) first.push_back(to);
    }

    FOR(i, first.size()) {
        FOR(j, MAX_SEGMENT) {
            FORE(k, j, MAX_SEGMENT) {
                int pos = first[i];
                int total = 0;
                while (pos != 0) {
                    if (interval[pos].first > j) total += interval[pos].first - j;
                    if (interval[pos].second < k) total += k - interval[pos].second;
                    pos = next[pos];
                }
                if (total < minSegment[j][k]) minSegment[j][k] = total;
            }
        }
    }
    print(solve(0, MAX_SEGMENT - 1));
}

