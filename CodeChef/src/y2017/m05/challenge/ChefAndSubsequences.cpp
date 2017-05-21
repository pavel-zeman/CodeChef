// Dynamic programming, which accumulates number of subsequences with product <= K
// https://www.codechef.com/MAY17/problems/CHEFCODE
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

class Hasher
{
public:
  size_t operator() (LLI const& key) const
  {
      return key ^ (key >> 32);
  }
};


int main(void) {
    int n = getInt();
    LLI k = getLongLongInt();
    vector<pair<LLI, int> > v1;
    v1.push_back(make_pair(1, 1));
    FOR(i, n) {
        LLI a = getLongLongInt();
        LLI mok = k / a;
        vector<pair<LLI, int> > v2;
        v2.reserve(v1.size());
        for(auto it = v1.begin(); it != v1.end(); it++)
            if (it->first <= mok) v2.push_back(make_pair(it->first * a, it->second));
            else break;
        vector<pair<LLI, int> > v3;
        v3.reserve(v1.size() + v2.size());
        int p1 = 0, p2 = 0;
        while (p1 < v1.size() && p2 < v2.size()) {
            if (v1[p1].first < v2[p2].first) v3.push_back(v1[p1++]);
            else if ((v1[p1].first > v2[p2].first)) v3.push_back(v2[p2++]);
            else {
                v3.push_back(make_pair(v1[p1].first, v1[p1].second + v2[p2].second));
                p1++;
                p2++;
            }
        }
        while (p1 < v1.size()) v3.push_back(v1[p1++]);
        while (p2 < v2.size()) v3.push_back(v2[p2++]);
        v1 = v3;
    }
    int r = 0;
    for(auto it = v1.begin(); it != v1.end(); it++) r += it->second;
    print(r - 1);
}

