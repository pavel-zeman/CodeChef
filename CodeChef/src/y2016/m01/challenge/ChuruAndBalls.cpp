// First make sure, that the sequence is non-decreasing. Then try to find the "optimum" GCD as each prime from 2 up to maximum number of balls in a single bucket.
// https://www.codechef.com/JAN16/problems/CBALLS
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

#define MAX_N 10010
bool isPrime[MAX_N];
int bucket[MAX_N];

int main(void) {
    FORE(i, 2, MAX_N) isPrime[i] = true;
    FORE(i, 2, MAX_N)
        if (isPrime[i])
            for(int j=i +i;j<MAX_N;j += i) isPrime[j] = false;


    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int maxValue = 3;
        FOR(i, n) {
            bucket[i] = getInt();
            maxValue = max(maxValue, bucket[i]);
        }
        maxValue++;
        int m1 = 0;
        FORE(i, 1, n)
            if (bucket[i] < bucket[i - 1]) {
                m1 += bucket[i - 1] - bucket[i];
                bucket[i] = bucket[i - 1];
            }

        int m2 = n * maxValue;
        FOR(i, maxValue)
            if (isPrime[i]) {
                int temp = 0;
                FOR(j, n) {
                    if (bucket[j] % i != 0) temp += i - bucket[j] % i;
                    if (temp >= m2) break;
                }
                if (temp < m2) m2 = temp;
            }
        print(m1 + m2);
    }
}

