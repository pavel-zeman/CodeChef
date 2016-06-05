// Remove useless courses and then store previous course for each course end and power of 2 courses.
// https://www.codechef.com/SNCKPA16/problems/SUBSEG2
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

bool order(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second || (a.second == b.second && a.first > b.first);
}

#define MAX_N 100010
#define MAX_INT 1000010
vector<pair<int, int>> courses;
vector<pair<int, int>> courses2;
vector<int> prevPosition[MAX_INT];
bool removed[MAX_N];

int startIndex[MAX_INT];
int endIndex[MAX_INT];
int prevEndIndex[MAX_INT];



int main(void) {
    FOR(i, MAX_INT) startIndex[i] = endIndex[i] = -1;
    int n = getInt();
    int q = getInt();
    FOR(i, n) {
        int start = getInt();
        int end = getInt();
        courses.push_back(make_pair(start, end));
    }
    sort(courses.begin(), courses.end(), order);

    int lastStart = -1;
    FOR(i, courses.size()) {
        if (courses[i].second != lastStart) {
            courses2.push_back(courses[i]);
            lastStart = courses[i].second;
        }
    }
    sort(courses2.begin(), courses2.end());
    courses.clear();
    lastStart = -1;
    FOR(i, courses2.size()) {
        if (courses2[i].first != lastStart) {
            courses.push_back(courses2[i]);
            startIndex[courses2[i].first] = courses.size() - 1;
            endIndex[courses2[i].second] = courses.size() - 1;
            lastStart = courses2[i].first;
        }
    }

    deque<int> active;
    FOR(i, MAX_INT) {
        if (startIndex[i] >= 0) active.push_back(startIndex[i]);
        if (endIndex[i] >= 0) {
            int ei = endIndex[i];
            if (!removed[ei]) {
                while (active.front() != ei) {
                    startIndex[courses[active.front()].first] = -1;
                    endIndex[courses[active.front()].second] = -1;
                    removed[active.front()] = true;
                    active.pop_front();
                }
                active.pop_front();
            }
        }
    }

    int currentPrev = -1;
    FOR(i, MAX_INT) {
        if (endIndex[i] >= 0) currentPrev = endIndex[i];
        prevEndIndex[i] = currentPrev;
    }
    FOR(i, MAX_INT) if (endIndex[i] >= 0) {
        int ei = endIndex[i];
        prevPosition[i].push_back(courses[ei].first);
        ei = prevEndIndex[courses[ei].first - 1];
        int pow = 0;
        while (ei >= 0) {
            if ((int)prevPosition[courses[ei].second].size() > pow) {
                prevPosition[i].push_back(prevPosition[courses[ei].second][pow]);
                pow++;
                ei = prevEndIndex[*prevPosition[i].rbegin() - 1];
            } else break;
        }
    }


    FOR(i, q) {
        int a = getInt();
        int b = getInt();
        int ei = prevEndIndex[b];
        int result = 0;
        while (ei >= 0) {
            if (courses[ei].first < a) break;
            int lastValid = prevPosition[courses[ei].second].size() - 1;
            FOR(j, prevPosition[courses[ei].second].size()) {
                if (prevPosition[courses[ei].second][j] < a) {
                    lastValid = j - 1;
                    break;
                }
            }
            result += 1 << lastValid;
            ei = prevEndIndex[prevPosition[courses[ei].second][lastValid] - 1];
        }
        print(result);
    }


}

