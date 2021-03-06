// Simple brute force solution
// https://www.codechef.com/COOK63/problems/STEM
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

void getString(char *data) {
    while (!(ccc >= 'a' && ccc <= 'z')) ccc = getc_unlocked(stdin);
    while (ccc >= 'a' && ccc <= 'z') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
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

#define MAX_N 20
#define MAX_L 30
string strings[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        char str[MAX_L];
        FOR(i, n) {
            getString(str);
            strings[i] = string(str);
        }
        int start = -1;
        int length = -1;
        int startLen = strings[0].length();
        string result("");
        for(int i=startLen; i>0;i--) {
            for(start = 0; start+i<=startLen;start++) {
                string stringToSearch = strings[0].substr(start, i);
                bool ok = true;
                FORE(j, 1, n) {
                    if (strings[j].find(stringToSearch) == string::npos) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    if (result.length() == 0 || stringToSearch < result) result = stringToSearch;
                }
            }
            if (result.length() > 0) break;
        }
        printString(result.c_str());
    }
}

