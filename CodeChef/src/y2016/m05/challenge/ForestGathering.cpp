// Sort the logs by ascending time to reach L meters. Then go one by one until W meters of wood can be provided.
// https://www.codechef.com/MAY16/problems/FORESTGA
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 100010
struct Wood {
    int h;
    int r;
    LLI t;

    bool operator<(const Wood &other) const {
        return this->t < other.t;
    }

} woods[MAX_N];

int main(void) {
    int n = getInt();
    LLI w = getLongLongInt();
    LLI l = getLongLongInt();
    FOR(i, n) {
        woods[i].h = getInt();
        woods[i].r = getInt();
        woods[i].t = woods[i].h >= l ? 0 : (l - woods[i].h + woods[i].r - 1) / woods[i].r;
    }
    sort(woods, woods + n);

    LLI totalH = 0;
    LLI totalR = 0;
    LLI result = -1;
    LLI lastT = 0;
    FOR(i, n) {
        LLI t = woods[i].t;
        if (totalH + totalR * t >= w) {
            result = max(totalR == 0 ? 0 : (w - totalH + totalR - 1) / totalR, lastT);
            break;
        }
        lastT = t;
        totalR += woods[i].r;
        totalH += woods[i].h;
    }
    if (result < 0) result = max((w - totalH + totalR - 1) / totalR, lastT);
    print(result);
}

