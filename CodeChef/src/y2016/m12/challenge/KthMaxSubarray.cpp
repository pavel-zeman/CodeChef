// Count sub-arrays with the greatest number, then with the second greatest number etc. Store the counts in array and use binary search to find the answer.
// https://www.codechef.com/DEC16/problems/KTHMAX
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
int value[MAX_N];
LLI total[MAX_N];

LLI comb(int a) {
    return (a * (LLI)(a - 1)) >> 1;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        vector<pair<int, int> > nums;
        nums.reserve(n);
        FOR(i, n) nums.push_back(make_pair(-getInt(), i));
        sort(nums.begin(), nums.end());

        int lastValue = nums[0].first;
        LLI totalSpaces = comb(n + 1);
        LLI lastTotalSpaces = totalSpaces;
        LLI currentTotal = 0;
        int totalPos = 0;

        set<int> used;
        used.insert(-1);
        used.insert(n);
        FOR(i, nums.size()) {
            if (nums[i].first != lastValue) {
                currentTotal += lastTotalSpaces - totalSpaces;
                total[totalPos] = currentTotal;
                value[totalPos++] = -lastValue;
                lastValue = nums[i].first;
                lastTotalSpaces = totalSpaces;
            }
            int p = nums[i].second;
            pair<set<int>::iterator, bool> cur = used.insert(p);
            set<int>::iterator next = cur.first;
            set<int>::iterator prev = cur.first;
            next++;
            prev--;
            totalSpaces -= comb(*next - *prev) - comb(*next - p) - comb(p - *prev);
        }
        currentTotal += lastTotalSpaces - totalSpaces;
        total[totalPos] = currentTotal;
        value[totalPos++] = -lastValue;

        FOR(i, m) {
            LLI *res = lower_bound(total, total + totalPos, getLongLongInt());
            print(value[res - total]);
        }

    }
}

