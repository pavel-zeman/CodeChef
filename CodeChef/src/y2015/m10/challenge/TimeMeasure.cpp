// The angle between hands is always a whole number of degree halves. For each such angle (except for 0 and 180) there are exactly 2 times. Pre-calculate the times and then just us them.
// https://www.codechef.com/OCT15/problems/TIMEASR
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


void printTime(int time) {
    printf("%02d:%02d\n", time / 60, time % 60);
}

#define ALLOWED_DIFF (1.0 / 120)
#define DEGREES 361
int counts[DEGREES];
int times[DEGREES][2];

int main(void) {
    int angle = 0;
    FOR(i, 12 * 60) {
        int temp = angle <= 360 ? angle : 720 - angle;
        times[temp][counts[temp]] = i;
        counts[temp]++;
        angle = (angle + 11) % 720;
    }

    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        double a;
        scanf("%lf", &a);
        int aint = a;
        int index = -1;
        if (abs(a - aint) < ALLOWED_DIFF) index = aint * 2;
        else if (abs(a - aint - 1.0 / 2) < ALLOWED_DIFF) index = aint * 2 + 1;
        if (index >= 0)
            FOR(i, counts[index])
                printTime(times[index][i]);
    }
}

