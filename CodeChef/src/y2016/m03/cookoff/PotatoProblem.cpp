// Solution based on convex hull with N^2 complexity, which is unfortunately too slow
// https://www.codechef.com/COOK68/problems/KTHCON
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

void fail() {
    *((char *)0) = 0;
}


typedef LLI T;
struct PT {
  T x, y;
  PT() {}
  PT(T x, T y) : x(x), y(y) {}
  bool operator<(const PT &rhs) const { return make_pair(y,x) < make_pair(rhs.y,rhs.x); }
  bool operator==(const PT &rhs) const { return make_pair(y,x) == make_pair(rhs.y,rhs.x); }
  int index;
};

T cross(PT p, PT q) { return p.x*q.y-p.y*q.x; }
T area2(PT a, PT b, PT c) { return cross(a,b) + cross(b,c) + cross(c,a); }


void ConvexHull(vector<PT> &pts) {
  sort(pts.begin(), pts.end());
  vector<PT> up, dn;
  for (int i = 0; i < (int)pts.size(); i++) {
    while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
    while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
    up.push_back(pts[i]);
    dn.push_back(pts[i]);
  }
  pts = dn;
  for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);

}

#define MAX_N 100010
PT points[MAX_N];
bool hull[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        vector<PT> all;
        FOR(i, n) {
            points[i].x = getSignedInt();
            points[i].y = getSignedInt();
            points[i].index = i;
            all.push_back(points[i]);
            hull[i] = false;
        }
        ConvexHull(all);
        if ((int)all.size() == n) printf("-1\n");
        else {
            FOR(i, all.size()) hull[all[i].index] = true;
            vector<int> notHull;
            FOR(i, n) if (!hull[i]) notHull.push_back(i);
            LLI total = 0;
            FOR(i, all.size()) {
                int next = (i + 1) % all.size();
                total += all[i].x * all[next].y - all[next].x * all[i].y;
            }
            total = abs(total);
            LLI minDelete = total;
            FOR(i, all.size()) {
                int next = (i + 1) % all.size();
                LLI a = all[next].y - all[i].y;
                LLI b = -(all[next].x - all[i].x);
                LLI c = -a * all[i].x -b * all[i].y;
                FOR(j, notHull.size()) {
                    int pp = notHull[j];
                    LLI temp = abs(a * points[pp].x + b * points[pp].y + c);
                    if (temp < minDelete) minDelete = temp;
                }
            }
            total -= minDelete;
            printf("%lld\n", total);
        }

    }
}

