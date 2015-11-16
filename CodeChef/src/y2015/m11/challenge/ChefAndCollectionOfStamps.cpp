// Go from the highest time to the beginning and maintain a maximum reachable value for each value
// https://www.codechef.com/NOV15/problems/CHSTAMP
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

#define MAX_M 50002
#define MAX_T 50002

int total[MAX_M];
int n, m;
vector<pair<int, int> > exchange[MAX_T];
int currentMax[MAX_M];
int used[MAX_M];
int maxValue[MAX_M];
int ds[MAX_M];
int depth[MAX_M];
vector<int> usedList;

void add(int x, int round) {
    if (used[x] != round) {
        used[x] = round;
        usedList.push_back(x);
        ds[x] = x;
        maxValue[x] = currentMax[x];
        depth[x] = 1;
    }
}

int root(int x) {
    while(ds[x] != x) x = ds[x];
    return x;
}

void merge(int a, int b) {
    int ra = root(a);
    int rb = root(b);
    if (ra != rb) {
        if (depth[ra] > depth[rb]) {
            ds[rb] = ra;
            maxValue[ra] = mx(maxValue[ra], maxValue[rb]);
        } else {
            ds[ra] = rb;
            if (depth[ra] == depth[rb]) depth[rb]++;
            maxValue[rb] = mx(maxValue[ra], maxValue[rb]);
        }
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        FOR(i, MAX_M) total[i] = 0, used[i] = 0;
        FOR(i, MAX_T) exchange[i].clear();
        FOR(i, MAX_M) currentMax[i] = i;

        n = getInt();
        m = getInt();
        FOR(i, n) total[getInt()]++;
        FOR(i, m) {
            int t = getInt();
            int a = getInt();
            int b = getInt();
            exchange[t].push_back(make_pair(a, b));
        }

        for(int i=MAX_T-1;i>0;i--) {
            usedList.clear();
            for(vector<pair<int, int> >::iterator it = exchange[i].begin(); it != exchange[i].end(); it++) {
                add(it->first, i);
                add(it->second, i);
                merge(it->first, it->second);
            }
            for (vector<int>::iterator it = usedList.begin(); it != usedList.end(); it++) {
                int v = *it;
                currentMax[v] = mx(currentMax[v], maxValue[root(v)]);
            }
        }
        long long int result = 0;
        FOR(i, MAX_M) result += currentMax[i] * (long long int)total[i];
        print(result);
    }
}

