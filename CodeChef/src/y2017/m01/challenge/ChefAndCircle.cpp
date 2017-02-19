// The circle must contain at least 2 of the input points. So choose radius, choose a point and then rotate circle with given radius around the point to calculate maximum points inside. Binary search for the optimal radius.
// https://www.codechef.com/JAN17/problems/CHEFCIRC
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

#define MAX_N 510
struct Point {
    double x;
    double y;

    bool operator<(const Point & other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

} points[MAX_N];
int n, m;

double sqr(double a) {
    return a * a;
}

double dist(int p1, int p2) {
    return sqrt(sqr(points[p1].x - points[p2].x) + sqr(points[p1].y - points[p2].y));
}

struct ELItem {
    int index;
    int diff;

    ELItem(int index, int diff) {
        this->index = index;
        this->diff = diff;
    }

    bool operator<(const ELItem & other) const {
        return index < other.index || (index == other.index && diff < other.diff);
    }

};

bool containsAtLeastM(int p, double r) {
    int totalIn = 0;
    vector<pair<double, ELItem>> items;
    FOR(i, n) {
        if (points[p].x == points[i].x && points[p].y == points[i].y) totalIn++;
        else {
            double d = dist(p, i);
            double a = d / 2;
            if (d <= r * 2) {
                double p2x = (points[p].x + points[i].x) / 2;
                double p2y = (points[p].y + points[i].y) / 2;
                double h = sqrt(sqr(r) - sqr(a));
                double p3x = p2x - h * (points[i].y - points[p].y) / d - points[p].x;
                double p3y = p2y + h * (points[i].x - points[p].x) / d - points[p].y;
                double angle1 = atan2(p3y, p3x);
                p3x = p2x + h * (points[i].y - points[p].y) / d - points[p].x;
                p3y = p2y - h * (points[i].x - points[p].x) / d - points[p].y;
                double angle2 = atan2(p3y, p3x);
                double diff = angle2 - angle1;
                if (diff < 0) diff += 2 * M_PI;
                if (diff > M_PI) swap(angle1, angle2);
                items.push_back(make_pair(angle1, ELItem(i, 1)));
                items.push_back(make_pair(angle2, ELItem(i, -1)));
            }
        }
    }
    sort(items.begin(), items.end());
    bool inside[n];
    memset(inside, 0, sizeof(inside));
    for(auto it = items.begin(); it != items.end(); it++) {
        if (it->second.diff > 0) {
            inside[it->second.index] = true;
            totalIn++;
        } else {
            if (inside[it->second.index]) {
                inside[it->second.index] = false;
                totalIn--;
            }
        }
        if (totalIn >= m) return true;
    }
    for(auto it = items.begin(); it != items.end(); it++) {
        totalIn += it->second.diff;
        if (totalIn >= m) return true;
        if (it->first > -M_PI/2) break;
    }
    return false;
}

bool check(double r) {
    FOR(i, n) if (containsAtLeastM(i, r)) return true;
    return false;
}

int main(void) {
    scanf("%d%d", &n, &m);
    FOR(i, n) scanf("%lf%lf", &points[i].x, &points[i].y);
    sort(points, points + n);
    int seq = 0;
    Point last = points[0];
    bool found = false;
    FOR(i, n) {
        if (last.x == points[i].x && last.y == points[i].y) {
            seq++;
        } else {
            seq = 1;
            last = points[i];
        }
        if (seq == m) {
            found = true;
            break;
        }
    }
    if (found) printString("0");
    else {
        double mm = 0;
        double mx = sqrt(2 * sqr(1001));
        while (mx - mm > 2e-2) {
            double mid = (mm + mx) / 2;
            if (check(mid)) mx = mid; else mm = mid;
        }
        printf("%lf\n", (mm + mx) / 2);
    }
}

