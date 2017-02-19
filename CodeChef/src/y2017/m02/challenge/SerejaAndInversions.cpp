// Use sorted map to pre-calculate pairs i < j such that Pi > Pj. Then use segment trees to calculate minimum of the second segment and list of conflicting positions for each position from the first segment.
// https://www.codechef.com/FEB17/problems/SEAINVS
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
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
int a[MAX_N];

int c[MAX_N / 2];
int cc;
int currentMin;
int l1, r1, l2, r2, ll;

int fact[MAX_N / 2];
vector<int> lower[MAX_N];
int maxTree[MAX_N * 3];
int minTree[MAX_N * 3];


void buildMax(int node, int l, int r) {
    if (l == r) {
        maxTree[node] = a[l];
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        buildMax(childNode, l, middle);
        buildMax(childNode + 1, middle + 1, r);
        maxTree[node] = max(maxTree[childNode], maxTree[childNode + 1]);
    }
}

void buildMin(int node, int l, int r) {
    if (l == r) {
        minTree[node] = a[l];
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        buildMin(childNode, l, middle);
        buildMin(childNode + 1, middle + 1, r);
        minTree[node] = min(minTree[childNode], minTree[childNode + 1]);
    }
}


int getMin(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return MAX_N;
    else {
        if (l >= start && r <= end) return minTree[node];
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        return min(getMin(childNode, l, middle, start, end), getMin(childNode + 1, middle + 1, r, start, end));
    }
}


void fillCs(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return;
    else {
        if (maxTree[node] < currentMin) return;
        if (l == r) {
            auto first = lower_bound(lower[l].begin(), lower[l].end(), l2);
            auto last = lower_bound(lower[l].begin(), lower[l].end(), r2);
            int totalInvalid = last - first;
            c[cc++] = ll - totalInvalid;
        } else {
            int middle = (l + r) >> 1;
            int childNode = node * 2 + 1;
            fillCs(childNode, l, middle, start, end);
            fillCs(childNode + 1, middle + 1, r, start, end);
        }
    }
}


int main(void) {
    fact[0] = 1;
    FORE(i, 1, sizeof(fact) / sizeof(fact[0])) fact[i] = fact[i - 1] * (LLI)i % MOD;

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n) a[i] = getInt();
        FOR(i, n) lower[i].clear();
        map<int, int> used;
        for(int i=n-1;i>=0;i--) {
            for(auto it=used.begin();it!=used.end();it++)
                if (it->first < a[i]) lower[i].push_back(it->second); else break;
            sort(lower[i].begin(), lower[i].end());
            used[a[i]] = i;
        }
        buildMin(0, 0, n - 1);
        buildMax(0, 0, n - 1);

        FOR(i, m) {
            l1 = getInt() - 1;
            r1 = getInt();
            l2 = getInt() - 1;
            r2 = getInt();
            ll = r1 - l1;
            cc = 0;
            currentMin = getMin(0, 0, n - 1, l2, r2 - 1);
            fillCs(0, 0, n - 1, l1, r1 - 1);

            sort(c, c + cc);

            int res = 1;
            FOR(j, cc) res = res * (LLI)(c[j] - j) % MOD;
            res = res * (LLI)fact[ll - cc] % MOD;
            print(res);
        }
    }
}

