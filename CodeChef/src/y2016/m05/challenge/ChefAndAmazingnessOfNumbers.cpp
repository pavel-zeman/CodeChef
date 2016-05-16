// THe commented out method shows, how to calculate the result for a single value. In general, the number of combinations of res and prev in this method is low (tens of thousands), so we can cache it to effectively calculate the result.
// https://www.codechef.com/MAY16/problems/CHEFNUM
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

namespace std {
    template<> struct hash<pair<int, int> > {
        size_t operator () (const pair<int,int> &p) const {
            return p.first * p.second;
        }
    };
}

int xors[1 << 16][10];
int sum[1 << 16];
// <start number, order> -> <prev, res>
unordered_map<pair<int, int>, unordered_map<pair<int, int>, int> > cache;


/*int fill(int *data, int v) {
    int pos = 0;
    while (v > 0) {
        data[pos++] = v % 10;
        v /= 10;
    }
    return pos;
}

int calc(int v) {
    int data[10];
    int res = 0;
    int s = fill(data, v);
    int prev = 0;
    FOR(j, s) {
        prev = xors[prev][data[j]]; // | (1 << data[j]);
        res |= prev;
    }
    //ss.insert(res);
    //ss2.insert(make_pair(res, prev));
    return res;
}*/


void fillData() {
    unordered_map<pair<int, int>, int> d;
    FOR(i, 10) {
        int prev = xors[0][i];
        d[make_pair(prev, prev)]++;
        cache[make_pair(i, 0)] = d;
    }
    FORE(i, 1, 9) {
        unordered_map<pair<int, int>, int> d;
        unordered_map<pair<int, int>, int> &src = cache[make_pair(9, i - 1)];
        FOR(j, 10) {
            for(unordered_map<pair<int, int>, int>::iterator it = src.begin(); it != src.end(); it++) {
                int prev = it->first.first;
                int res = it->first.second;
                int c = it->second;
                prev = xors[prev][j];
                res |= prev;
                d[make_pair(prev, res)] += c;
            }
            cache[make_pair(j, i)] = d;
        }
    }
}

int calc(int v) {
    if (v == 0) return 0;
    bool add = false;
    if (v == 1000000000) {
        v--;
        add = true;
    }
    unordered_map<pair<int, int>, int> d;
    d[make_pair(0, 0)] = 1;
    int order = 0;
    while (v > 0) {
        unordered_map<pair<int, int>, int> res;
        int digit = v % 10;
        if (digit > 0) res = cache[make_pair(digit - 1, order)];
        for(unordered_map<pair<int, int>, int>::iterator it = d.begin(); it != d.end(); it++) {
            int prev = it->first.first;
            int resv = it->first.second;
            int c = it->second;
            prev = xors[prev][digit];
            resv |= prev;
            res[make_pair(prev, resv)] += c;
        }
        d = res;

        v /= 10;
        order++;
    }
    int result = 0;
    for(unordered_map<pair<int, int>, int>::iterator it = d.begin(); it != d.end(); it++)
        result = (result + sum[it->first.second] * it->second) % MOD;
    if (add) result = (result + 1) % MOD;
    return result;
}


int main(void) {
    FOR(i, sizeof(xors) / sizeof(xors[0])) {
        FOR(j, 10) {
            int res = 0;
            int t = i;
            FOR(k, 16) {
                if ((t & 1) == 1) res |= 1 << (j ^ k);
                t >>= 1;
            }
            xors[i][j] = res | (1 << j);
        }
    }
    FOR(i, sizeof(sum) / sizeof(sum[0])) {
        int t = i;
        int total = 0;
        FOR(j, 16) {
            if ((t & 1) == 1) total += j;
            t >>= 1;
        }
        sum[i] = total;
    }
    fillData();

    int tt = getInt();
    FOR(ttt, tt) {
        int l = getInt();
        int r = getInt();
        int res = calc(r) - calc(l - 1);
        if (res < 0) res += MOD;
        print(res);
    }
}

