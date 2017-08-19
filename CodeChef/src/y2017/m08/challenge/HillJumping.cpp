// Use sqrt decomposition and pre-calculate values for each block
// https://www.codechef.com/AUG17/problems/HILLJUMP
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

#define MAX_N 100010
#define MAX_SQRT_N 400
LLI a[MAX_N];
int sqSize, sqTotal;
int n;
struct Item {
    int next;
    int last;
    int jumps;
} items[MAX_N];

struct Block {
    LLI correction;
    vector<pair<LLI, int> > first;
} blocks[MAX_SQRT_N];


void recalculateBlock(int b) {
    blocks[b].first.clear();

    int first = b * sqSize;
    for(int i = min((b + 1) * sqSize, n) - 1; i >= first; i--) {
        LLI v = a[i];
        auto nextIt = upper_bound(blocks[b].first.rbegin(), blocks[b].first.rend(), make_pair(v, MAX_N));
        if (nextIt == blocks[b].first.rend() || nextIt->second - i > 100) {
            items[i].next = -1;
            items[i].last = i;
            items[i].jumps = 0;
        } else {
            items[i].next = nextIt->second;
            items[i].last = items[items[i].next].last;
            items[i].jumps = items[items[i].next].jumps + 1;
        }
        while (!blocks[b].first.empty() && blocks[b].first.back().first <= v)
            blocks[b].first.pop_back();
        blocks[b].first.push_back(make_pair(v, i));
    }
}


int main(void) {
    n = getInt();
    int q = getInt();
    FOR(i, n) a[i] = getInt();
    sqSize = min((int)sqrt(n) + 1, n);
    if (sqSize <= 100) {
        if (n <= 100) sqSize = n; else sqSize = 101;
    }
    sqTotal = (n + sqSize - 1) / sqSize;
    FOR(i, sqTotal) recalculateBlock(i);

    FOR(i, q) {
        int t = getInt();
        if (t == 1) {
            int start = getInt() - 1;
            int k = getInt();
            int b = start / sqSize;
            LLI v = a[start] + blocks[b].correction;
            while (k > 0) {
                if (items[start].next < 0) {
                    b++;
                    if (b >= sqTotal) break;
                    auto nextIt = upper_bound(blocks[b].first.rbegin(), blocks[b].first.rend(), make_pair(v - blocks[b].correction, MAX_N));
                    if (nextIt == blocks[b].first.rend() || nextIt->second - start > 100) break;
                    k--;
                    start = nextIt->second;
                    v = a[start] + blocks[b].correction;
                } else if (items[start].jumps <= k) {
                    k -= items[start].jumps;
                    start = items[start].last;
                    v = a[start] + blocks[b].correction;
                } else {
                    while (k > 0) {
                        start = items[start].next;
                        k--;
                    }
                }
            }
            print(start + 1);
        } else {
            int l = getInt() - 1;
            int r = getInt() - 1;
            int x = getSignedInt();
            int b1 = l / sqSize;
            int b2 = r / sqSize;
            if (b1 == b2) {
                FORE(i, l, r + 1) a[i] += x;
                recalculateBlock(b1);
            } else {
                int bb = b1 * sqSize + sqSize;
                FORE(i, l, bb) a[i] += x;
                recalculateBlock(b1);
                FORE(i, b1 + 1, b2) blocks[i].correction += x;
                FORE(i, b2 * sqSize, r + 1) a[i] += x;
                recalculateBlock(b2);
            }
       }
    }
}

