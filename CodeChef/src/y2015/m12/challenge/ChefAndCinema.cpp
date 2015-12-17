// There are several special cases, which must be handled
// https://www.codechef.com/DEC15/problems/CHCINEMA
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int


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
    while (!(ccc >= 'a' && ccc <= 'z')) ccc = getc_unlocked(stdin);
    while (ccc >= 'a' && ccc <= 'z') {
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

void fail() {
    *((char *)0) = 0;
}

LLI numBoth(int x) {
    return (x + 1) >> 1;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int nOrig = n;
        int m = getInt();
        int mOrig = m;
        LLI z = getLongLongInt();
        LLI l = getLongLongInt();
        LLI r = getLongLongInt();
        LLI b = getLongLongInt();

        LLI result = 0;
        if ((m & 1) == 0) {
            result += min(l, (LLI)n);
            l -= min(l, (LLI)n);
            int aaa = min(r, n - result);
            result += aaa;
            r -=  aaa;
            m--;
        }


        if (m == 1) {
            result += min(l, (LLI)n);
            n -= min(l, (LLI)n);
            result += min(r, (LLI)n);
            n -= min(r, (LLI)n);
            result += min(b, (LLI)n);
            n -= min(b, (LLI)n);
        } else {
            // rows with left + single both
            LLI rows = min(min(l / (m - 1), b), (LLI)n);
            result += rows * m;
            l -= rows * (m - 1);
            b -= rows;
            n -= rows;

            rows = min(l / m, (LLI)n);
            result += rows * m;
            l -= rows * m;
            n -= rows;

            // rows with right + single both
            rows = min(min(r / (m - 1), b), (LLI)n);
            result += rows * m;
            r -= rows * (m - 1);
            b -= rows;
            n -= rows;

            rows = min(r / m, (LLI)n);
            result += rows * m;
            r -= rows * m;
            n -= rows;

            if (n == 0) goto end;

            // finish left and right
            if (n == 1) {
                int xx = min(l + r, (LLI)m);
                result += xx;
                result += min(b, numBoth(m - xx));
                b -= min(b, numBoth(m - xx));
                n--;
            } else {
                int s = l + r;

                while (s > 0 && n > 0) {
                    int xx = min(m, s);
                    n--;
                    if (b == 0) {
                        result += xx;
                        s -= xx;
                    } else {
                        if (xx == m) {
                            xx--;
                            s -= xx;
                            b--;
                            result += m;
                        } else {
                            if (xx > 1 && n > 0 &&  ((m - xx) & 1) == 0 && b >= numBoth(m - xx + 1)) {
                                xx--;
                                result += xx;
                                s -= xx;
                                result += numBoth(m - xx);
                                b -= numBoth(m - xx);
                            } else {
                                result += xx;
                                s -= xx;
                                result += min(b, numBoth(m - xx));
                                b -= min(b, numBoth(m - xx));
                            }
                        }
                    }
                }
            }

            if (n == 0) goto end;

            // add both
            rows = min((LLI)n, b / numBoth(m));
            result += rows * numBoth(m);
            n -= rows;
            b -= rows * numBoth(m);
            if (b > 0 && n > 0) result += b;

        }
        end:
        LLI remain = ((long long int)nOrig) * mOrig - result;
        result += min(z, remain);

        printf("%lld\n", result);
   }
}

