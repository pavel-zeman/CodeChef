// Based on Trie data structure as described in http://threads-iiith.quora.com/Tutorial-on-Trie-and-example-problems
// https://www.codechef.com/SEPT15/problems/REBXOR
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


#define MAX_N 400010
#define MAX_T 6000000

int a[MAX_N];
int n;
struct Trie {
    int child[2];
} trie[MAX_T];
int tries;

int maxStart[MAX_N];
int maxEnd[MAX_N];

int createNode() {
    trie[tries].child[0] = trie[tries].child[1] = 0;
    return tries++;
}

void add(int v) {
    int node = 0;
    int bit = 29;
    while (bit >= 0) {
        int child = (v >> bit) & 1;
        if (trie[node].child[child] == 0) trie[node].child[child] = createNode();
        node = trie[node].child[child];
        bit--;
    }
}

int find(int v) {
    int node = 0;
    int value = 0;
    int bit = 29;
    while (bit >= 0) {
        int child = ((v >> bit) & 1) ^ 1;
        if (trie[node].child[child] == 0) child ^= 1;
        node = trie[node].child[child];
        value = (value << 1) | child;
        bit--;
    }
    return v ^ value;
}

int main(void) {
    n = getInt();
    FOR(i, n) a[i] = getInt();
    tries = 1;
    trie[0].child[0] = trie[0].child[1] = 0;
    add(0);

    int curXor = 0;
    int curMax = 0;
    FOR(i, n) {
        curXor ^= a[i];
        add(curXor);
        maxStart[i] = curMax = mx(curMax, find(curXor));
    }

    tries = 1;
    trie[0].child[0] = trie[0].child[1] = 0;
    add(0);
    curXor = 0;
    curMax = 0;
    for(int i=n-1;i>0;i--) {
        curXor ^= a[i];
        add(curXor);
        maxEnd[i] = curMax = mx(curMax, find(curXor));
    }
    int result = 0;
    FOR(i, n - 1) result = mx(result, maxStart[i] + maxEnd[i + 1]);
    print(result);
}

