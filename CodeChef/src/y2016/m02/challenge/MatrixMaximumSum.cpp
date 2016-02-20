// The formula for C(i,j) can be rewritten to C(i,j) = (A(i)+i)*(B(j)+j). After modifying A(i) and B(j), this can be reduced to C(i,j)=A(i)*B(j). And this can be calculated by calculating running maximum.
// https://www.codechef.com/FEB16/problems/MTMXSUM
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
int a[MAX_N];
int b[MAX_N];
int m[MAX_N];


struct Interval {
    int start;
    int end;
    int steps;
};

void prepare(int *src, int n) {
    FOR(i, n) m[i] = src[i];
    list<Interval> intervals;

    FOR(i, n) {
        int start = i;
        if (i + 1 < n && m[i + 1] < m[i]) {
            while (i + 1 < n && m[i + 1] <= m[i]) i++;
            Interval interval;
            interval.start = start;
            interval.end = i;
            interval.steps = 0;
            intervals.push_back(interval);
        }
    }

    LLI total = 0;
    FOR(i, n) total += m[i];

    FOR(i, n) {
        src[i] = total % MOD;
        if (intervals.empty() || intervals.begin()->start > i)
            total -= m[i];
        else
            total -= m[intervals.begin()->start];

        int lastStart = n + 1;

        list<Interval>::reverse_iterator it = intervals.rbegin();
        while (it != intervals.rend()) {
            total += m[it->start] - m[it->end - it->steps];
            it->steps++;

            if (it->end + 1 < n && m[it->end + 1] < m[it->end - it->steps]) {
                for(int j=0;j<it->end - it->start - it->steps;j++)
                    m[it->end - j] = m[it->end - j - it->steps];
                for(int j=0;j<it->steps;j++)
                    m[it->start + j + 1] = m[it->start];

                if (lastStart == it->end + 1) {
                    list<Interval>::reverse_iterator it2 = it;
                    it2--;
                    for(int j=0;j<it2->end - it2->start - it2->steps;j++)
                        m[it2->end - j] = m[it2->end - j - it2->steps];
                    for(int j=0;j<it2->steps;j++)
                        m[it2->start + j + 1] = m[it2->start];
                    it->start += it->steps;
                    it->end = it2->end;
                    it->steps = 0;

                    it2++;
                    intervals.erase(it2.base());
                } else {
                    it->start += it->steps;
                    it->end++;
                    it->steps = 0;
                }
            }

            if (it->steps == it->end - it->start) {
                FORE(i, it->start, it->end) m[i + 1] = m[it->start];
                ++it;
                it = list<Interval>::reverse_iterator(intervals.erase(it.base()));
            } else {
                lastStart = it->start;
                it++;
            }
        }
    }
}

int main(void) {
    int n = getInt();
    FOR(i, n) a[i] = getInt() + i + 1;
    FOR(i, n) b[i] = getInt() + i + 1;
    prepare(a, n);
    prepare(b, n);
    FOR(i, n) printf("%lld ", a[i] * (LLI)b[i] % MOD);
}

