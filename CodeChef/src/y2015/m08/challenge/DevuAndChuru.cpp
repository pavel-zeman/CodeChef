// Recursively find maximum element, then calculate number of intervals and their sums from the lowest and highest ones (we need just the last bit of the sum). It would be much easier to use map, but it is too slow.
// https://www.codechef.com/AUG15/problems/DCGAME
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

char getChar() {
    while (ccc != '<' && ccc != '>' && ccc != 'C' && ccc != 'D' && ccc != '=') ccc = getc_unlocked(stdin);
    char result = ccc;
    ccc = getc_unlocked(stdin);
    return result;
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

#define MAX_N 1000010
#define MAX_LOG_N 21
int a[MAX_N], b[MAX_N];
int rmq[MAX_LOG_N][MAX_N];
int n, m;
int numDif;
char logs[MAX_N];

int keys[MAX_N];
int counts[MAX_N];

void preProcess() {
    FOR(i, n) rmq[0][i] = i;

    for (int j = 1; 1 << j <= n; j++) {
        int end = n - (1 << j) + 1;
        int step = 1 << (j - 1);
        FOR(i, end) {
            rmq[j][i] = a[rmq[j - 1][i]] > a[rmq[j - 1][i + step]] ? rmq[j - 1][i] : rmq[j - 1][i + step];
        }
    }
}

int query(int l, int r) {
    int level = logs[r - l + 1];
    return a[rmq[level][l]] > a[rmq[level][r - (1 << level) + 1]] ? rmq[level][l] : rmq[level][r - (1 << level) + 1];
}

void addIntervalCount(int value, int count) {
    int *elem = lower_bound(keys, keys + numDif, value);
    counts[elem - keys] ^= count;
}

void processInterval(int l, int r) {
    queue<pair<int, int> > q;
    q.push(make_pair(0, n - 1));
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int l = p.first;
        int r = p.second;
        int mx = query(l, r);
        int res = ((mx - l + 1) & 1) & ((r - mx + 1) & 1);
        addIntervalCount(a[mx], res);
        if (l <= mx - 1) q.push(make_pair(l, mx - 1));
        if (mx + 1 <= r) q.push(make_pair(mx + 1, r));
    }
}

void initRunningSums() {
    int runningSum = 0;
    FOR(i, numDif) {
        runningSum ^= counts[i] & 1;
        counts[i] |= runningSum << 1;
    }

    runningSum = 0;
    for(int i=numDif - 1;i>=0;i--) {
        runningSum ^= counts[i] & 1;
        counts[i] |= runningSum << 2;
    }
}

int main(void) {
    n = getInt();
    m = getInt();
    logs[0] = -1;
    FORE(i, 1, n + 1) logs[i] = logs[i - 1] + ((i & (i - 1)) == 0 ? 1 : 0);
    FOR(i, n) a[i] = b[i] = getInt();
    sort(b, b + n);
    numDif = 0;
    int last = 0;
    FOR(i, n) if (b[i] != last) {
        last = b[i];
        keys[numDif++] = last;
    }
    keys[numDif] = 0;

    preProcess();
    processInterval(0, n - 1);
    initRunningSums();
    FOR(i, m) {
        char sign;
        int k;
        char x;
        sign = getChar();
        k = getInt();
        x = getChar();
        int count = 0;
        int *it;
        switch (sign) {
            case '=':
                it = lower_bound(keys, keys + numDif, k);
                count = *it == k ? counts[it - keys] : 0;
                break;

            case '>':
                it = upper_bound(keys, keys + numDif, k);
                count = it == keys + numDif ? 0 : counts[it - keys] >> 2;
                break;

            case '<':
                it = lower_bound(keys, keys + numDif, k);
                count = it == keys ? 0 : counts[it - keys - 1] >> 1;
                break;
        }
        count &= 1;
        putc_unlocked(count == 1 ? x : (x == 'C' ? 'D' : 'C'), stdout);
    }
}

