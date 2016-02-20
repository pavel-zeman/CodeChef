// Sort the numbers and go through them in descending order counting number of items greater than current item by at most D.
// https://www.codechef.com/FEB16/problems/SEAPERMS
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

void fail() {
    *((char *)0) = 0;
}


#define MAX_N 100010

int n, d;
int a[MAX_N];
set<pair<int, int> > data;

int calc() {
    int total = 1;
    set<pair<int, int> >::reverse_iterator it = data.rbegin();
    set<pair<int, int> >::reverse_iterator lastIt = data.rbegin();
    it++;
    int pos = n - 2;
    int lastPos = n - 1;
    while (it != data.rend()) {
        while (lastIt->first >= it->first + d) {
            lastIt++;
            lastPos--;
        }
        total = total * (LLI)(lastPos - pos + 1) % MOD;
        it++;
        pos--;
    }
    return total;
}


int main(void) {
    n = getInt();
    d = getInt();
    FOR(i, n) {
        a[i] = getInt();
        data.insert(make_pair(a[i], i));
    }
    int m = getInt();
    FOR(i, m) {
        int p = getInt() - 1;
        int v = getInt();
        data.erase(make_pair(a[p], p));
        a[p] = v;
        data.insert(make_pair(a[p], p));
        print(calc());
    }
}

