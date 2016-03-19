// Divide the lines into sets by their direction (combination of A and B) and then choose the largest set.
// https://www.codechef.com/DEC15/problems/PLANEDIV
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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        map<pair<int, int>, set<pair<int, pair<int, int> > > > data;
        int n = getInt();
        FOR(i, n) {
            int a = getSignedInt();
            int b = getSignedInt();
            int c = getSignedInt();
            if (a < 0) { a = -a; b = -b; c = -c;}
            int g1 = gcd(a, b);
            int g2 = gcd(g1, c);

            pair<int, pair<int, int> > item;
            item.first = a / g2;
            item.second.first = b / g2;
            item.second.second = c / g2;
            data[make_pair(a / g1, b / g1)].insert(item);
        }
        int result = 0;
        for(map<pair<int, int>, set<pair<int, pair<int, int> > > >::iterator it = data.begin(); it != data.end(); it++)
            result = mx(result, (int)it->second.size());
        print(result);
    }
}
