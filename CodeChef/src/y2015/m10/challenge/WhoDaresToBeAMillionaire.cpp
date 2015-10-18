// Count the total number of correct answers and then choose maximum winnings for the count of correct answers not more than total correct answers (and there is a special case, when all the answers are correct)
// https://www.codechef.com/OCT15/problems/WDTBAM
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


void getString(char *data) {
    while (!(ccc >= 'A' && ccc <= 'Z')) ccc = getc_unlocked(stdin);
    while (ccc >= 'A' && ccc <= 'Z') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
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

#define MAX_N 1010

char correct[MAX_N];
char chef[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        getString(correct);
        getString(chef);
        int totalCorrect = 0;
        FOR(i, n) totalCorrect += correct[i] == chef[i];
        int result = 0;
        if (totalCorrect == n) {
            FOR(i, n) getInt();
            result = getInt();
        } else {
            FOR(i, n + 1) {
                int w = getInt();
                if (i <= totalCorrect) result = mx(result, w);
            }
        }
        print(result);
    }
}

