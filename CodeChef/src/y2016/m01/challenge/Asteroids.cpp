// Dirty solution based on trying multiple elevation angles and then calculating intersections of intervals (based on method 3 from https://www.google.cz/url?sa=t&rct=j&q=&esrc=s&source=web&cd=12&cad=rja&uact=8&ved=0ahUKEwj2oZX9pp_KAhWkh3IKHWxaBisQFghiMAs&url=http%3A%2F%2Fwww.qc.edu.hk%2Fmath%2FTeaching_Learning%2F36_Solve%2520trigo%2520equation.doc&usg=AFQjCNEY1GsO-ngDqwJX4YP2NyLz-KJOCw)
// https://www.codechef.com/JAN16/problems/ASTRD
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

#define MAX_N 160
#define STEP 0.1
#define MIN_DISTANCE 1e-3
#define MAX_STEP 4200
#define MM_PI (2 * M_PI)
int x[MAX_N], y[MAX_N], z[MAX_N];
int pairCount;
pair<double, int> pairs[4 * MAX_N];


void addAllOrNothing(double a, double b, double c) {
    if (-b >= c) {
        pairs[pairCount++] = make_pair(0, -1);
    }
}

bool isVisible(double a, double b, double c) {
    return -b >= c;
}

double fix(double a) {
    return a < 0 ? a + MM_PI : a;
}

void addPair(double a, double b, double c, double s1, double s2) {
    s1 = fix(s1);
    s2 = fix(s2);
    if (s1 > s2) swap(s1, s2);
    double t = (s1 + s2) / 2;
    if (a * sin(t) + b * cos(t) >= c) {
        pairs[pairCount++] = make_pair(s1, -1);
        pairs[pairCount++] = make_pair(s2, 1);
    } else {
        pairs[pairCount++] = make_pair(0, -1);
        pairs[pairCount++] = make_pair(s1, 1);
        pairs[pairCount++] = make_pair(s2, -1);
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        double r = getInt() + MIN_DISTANCE;
        FOR(i, n) {
            x[i] = getSignedInt();
            y[i] = getSignedInt();
            z[i] = getSignedInt();
        }

        int res = n >> 1;
        for(double i=0;i<=180;i+=STEP) {
            double a1 = i * M_PI / 180;
            double sa1 = sin(a1);
            double ca1 = cos(a1);
            if (sa1 == 0) {
                int visible = 0;
                FOR(k, n) {
                    double dist = ca1 * y[k] - r;
                    if (dist >= 0) {
                        visible++;
                        if (visible >= res) break;
                    }
                }
                if (visible < res) res = visible;
            } else {
                pairCount = 0;
                int visible = 0;
                FOR(k, n) {
                    double a = sa1 * y[k];
                    double b = sa1 * x[k];
                    double c = r - ca1 * z[k];
                    double d = a * a + b * b - c * c;
                    if (d <= 0) {
                        if (isVisible(a, b, c)) visible++;
                        if (visible >= res) break;
                    } else {
                        d = sqrt(d);
                        double t1 = (a + d) / (c + b);
                        double t2 = (a - d) / (c + b);
                        t1 = atan(t1) * 2;
                        t2 = atan(t2) * 2;
                        addPair(a, b, c, t1, t2);
                    }
                }
                if (visible < res) {
                    sort(pairs, pairs + pairCount);
                    int l = 0;
                    while (l < pairCount && pairs[l].first == 0) {
                        visible -= pairs[l].second;
                        l++;
                    }
                    for(;l<pairCount;l++) {
                        if (visible < res) res = visible;
                        visible -= pairs[l].second;
                    }
                    if (visible < res) res = visible;
                }
            }
        }
        print(res);
    }
}

