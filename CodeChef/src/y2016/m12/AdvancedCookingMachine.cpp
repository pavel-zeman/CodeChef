// Description
// https://www.codechef.com/DEC16/problems/BOUNCE
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

#define MAX_N 512
#define MAX_STRINGS 200000
#define MAX_S 10000
#define UR 0
#define UL 1
#define DR 2
#define DL 3

struct {
    int sl;
    char *s;
    int a;
    int b;
    int mab;
} strings[MAX_STRINGS];

int stringCount = 0;
char s[MAX_S];


bool findNext(int &x, int &y, int width, int height, int &dir, int pos) {
    int rx = -1, ry = -1;
    switch (dir) {
    case UR:
        rx = width - x;
        ry = height - y;
        x += min(rx, ry);
        y += min(rx, ry);

        if (rx == ry) return false;
        if (rx < ry) {
            dir = UL;
            s[pos] = 'R';
        } else {
            dir = DR;
            s[pos] = 'T';
        }
        break;

    case UL:
        rx = x;
        ry = height - y;
        x -= min(rx, ry);
        y += min(rx, ry);
        if (rx == ry) return false;
        if (rx < ry) {
            dir = UR;
            s[pos] = 'L';
        } else {
            dir = DL;
            s[pos] = 'T';
        }
        break;

    case DR:
        rx = width - x;
        ry = y;
        x += min(rx, ry);
        y -= min(rx, ry);

        if (rx == ry) return false;
        if (rx < ry) {
            dir = DL;
            s[pos] = 'R';
        } else {
            dir = UR;
            s[pos] = 'D';
        }
        break;

    case DL:
        rx = x;
        ry = y;
        x -= min(rx, ry);
        y -= min(rx, ry);
        if (rx == ry) return false;
        if (rx < ry) {
            dir = DR;
            s[pos] = 'L';
        } else {
            dir = UL;
            s[pos] = 'D';
        }
        break;
    }
    return true;
}

int main(void) {
    FORE(i, 1, MAX_N) FORE(j, 1, MAX_N) if (i != j && gcd(i, j) == 1) {
        int x = 0;
        int y = 0;
        int dir = 0;
        int width = i;
        int height = j;
        int pos = 0;
        while (findNext(x, y, width, height, dir, pos)) {
            //printf("%d %d %d\n", width, height, pos);
            pos++;
        }
        s[pos] = 0;
        strings[stringCount].a = width;
        strings[stringCount].b = height;
        strings[stringCount].mab = max(width, height);
        strings[stringCount].sl = pos;
        strings[stringCount].s = new char[pos + 1];
        strcpy(strings[stringCount].s, s);
        stringCount++;
        //if (stringCount % 1000 == 0) print(stringCount);
    }
    //print(stringCount);
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        if (n > 600) return 1;
        int sl = getInt();
        getString(s);
        LLI result = 0;
        FOR(i, stringCount) {
            if (strings[i].sl >= sl && !strncmp(s, strings[i].s, sl))
                result = (result + n / strings[i].mab * (LLI)strings[i].sl) % MOD;
        }
        print(result);
    }
}

