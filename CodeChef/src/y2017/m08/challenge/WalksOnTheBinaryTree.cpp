// When changing any bit except for the top 17 ones (log2(100000)) all the nodes "below" the highest changed bit are newly visited. The top 17 bits can be brute forced.
// https://www.codechef.com/AUG17/problems/WALKBT
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

#define DEPTH 17
#define MAX_Q 1000010
int n;
LLI used;
int usedNodes;
struct Node {
    int c[2];
} nodes[4000000];
map<int, int> m;
int maxDepth[MAX_Q];
int lastVisit[1 << DEPTH];


void add(int c, int queryPos) {
    if (c >= n) return;

    auto it = m.lower_bound(c);
    if (it->first > c) it--;
    int endPos;
    if (it->second == 0) {
        auto next = it;
        next++;
        int nextIndex = next->first;
        if (it->first == c) {
            if (c > 0) m.erase(it); else it->second = 1;
        } else m[c] = 1;
        if (c + 1 < n) {
            if (c + 1 == nextIndex) m.erase(nextIndex); else m[c + 1] = 0;
        }
        endPos = c;
    } else {
        auto next = it;
        next++;
        int nextIndex = next->first;
        endPos = nextIndex;
        if (it->first == c) {
            if (c > 0) m.erase(it); else it->second = 0;
        } else m[c] = 0;
        m[nextIndex] = 1;
        if (nextIndex + 1 < n) {
            if (m.find(nextIndex + 1) == m.end()) m[nextIndex + 1] = 0; else m.erase(nextIndex + 1);
        }
    }
    if (c <= n - DEPTH) maxDepth[queryPos] = min(endPos, n - DEPTH - 1);
    else maxDepth[queryPos] = -1;
}

void dump() {
    for(auto it = m.begin(); it != m.end(); it++) printf("%d:%d, ", it->first, it->second);
    printf("\n");
}

void walk(int c, int queryPos) {
    add(c, queryPos);
    int pos = 0;
    int prevPos = n;
    if (n <= 20) {
        for(auto it = ++(m.rbegin()); it != m.rend(); it++) {
            int cp = it->first;
            int v = it->second;
            FOR(i, prevPos - cp) {
                if (nodes[pos].c[v] < 0) {
                    nodes[used].c[0] = nodes[used].c[1] = -1;
                    nodes[pos].c[v] = used++;
                }
                pos = nodes[pos].c[v];
            }
            prevPos = cp;
        }
    } else {
        int d = 0;
        int index = 0;
        for(auto it = ++(m.rbegin()); it != m.rend(); it++) {
            int cp = it->first;
            int v = it->second;
            FOR(i, prevPos - cp) {
                if (nodes[pos].c[v] < 0) {
                    nodes[usedNodes].c[0] = nodes[usedNodes].c[1] = -1;
                    nodes[pos].c[v] = usedNodes++;
                    used++;
                }
                pos = nodes[pos].c[v];
                index <<= 1;
                index |= v;
                if (++d == DEPTH) goto end;
            }
            prevPos = cp;
        }
        end:
        int prevPos = lastVisit[index];
        if (prevPos >= 0) {
            int mx = *max_element(maxDepth + prevPos + 1, maxDepth + queryPos + 1);
            if (mx >= 0) used += mx + 1;
        } else used += n - DEPTH;
        //printf("Index: %d, PrevPos: %d, maxDepth: %d\n", index, lastVisit[index], maxDepth[queryPos]);
        lastVisit[index] = queryPos;
    }
    //dump();
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m.clear();
        m[0] = 0;
        m[n] = 0;
        FOR(i, sizeof(lastVisit) / sizeof(lastVisit[0])) lastVisit[i] = -1;
        int q = getInt();
        used = 1;
        usedNodes = 1;
        nodes[0].c[0] = nodes[0].c[1] = -1;
        int queryPos = 0;
        FOR(i, q) {
            char ss[10];
            getString(ss);
            if (ss[0] == '!') walk(getInt(), queryPos++); else print(used);
        }

    }
}

