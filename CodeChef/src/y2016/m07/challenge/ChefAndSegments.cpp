// Try each possible position of the first segment (a,b) and maintain list of possible sub-intervals to choose the second segment from
// https://www.codechef.com/JULY16/problems/CHSGMNTS
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


#define MAX_N 1024
int a[MAX_N];
vector<int> positions[MAX_N];
bool used[MAX_N];

int convert(int n) {
    int totalNumbers = 0;
    map<int, int> m;
    FOR(i, n) {
        map<int, int>::iterator it = m.find(a[i]);
        int v;
        if (it == m.end()) {
            v = m[a[i]] = totalNumbers;
            totalNumbers++;
        } else v = it->second;
        a[i] = v;
    }
    return totalNumbers;
}

int calc(int l) {
    return (l + 1) * l / 2;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) a[i] = getInt();
        int nums = convert(n);
        FOR(i, nums) positions[i].clear();

        LLI result = 0;
        for(int i = n - 2; i >= 0; i--) {
            vector<pair<int, int>> ints1, ints2;
            FOR(j, nums) used[j] = false;
            positions[a[i + 1]].push_back(i + 1);
            ints1.push_back(make_pair(i + 1, n - 1));
            int currentSize = calc(n - 1 - (i + 1) + 1);
            for(int j = i; j >= 0; j--) {
                if (!used[a[j]]) {
                    used[a[j]] = true;
                    int pSize = positions[a[j]].size();
                    int i1Pos = 0;
                    if (pSize > 0) {
                        ints2.clear();
                        pSize--;
                        while (pSize >= 0 && i1Pos < (int)ints1.size()) {
                            if (ints1[i1Pos].second < positions[a[j]][pSize]) {
                                ints2.push_back(ints1[i1Pos]);
                                i1Pos++;
                            } else if (positions[a[j]][pSize] < ints1[i1Pos].first) {
                                pSize--;
                            } else {
                                if (ints1[i1Pos].first == ints1[i1Pos].second) {
                                    currentSize--;
                                    i1Pos++;
                                    pSize--;
                                } else {
                                    int p = positions[a[j]][pSize];
                                    if (p == ints1[i1Pos].first) {
                                        currentSize -= ints1[i1Pos].second - ints1[i1Pos].first + 1;
                                        ints1[i1Pos].first++;
                                    } else if (p == ints1[i1Pos].second) {
                                        currentSize -= ints1[i1Pos].second - ints1[i1Pos].first + 1;
                                        ints1[i1Pos].second--;
                                    } else {
                                        ints2.push_back(make_pair(ints1[i1Pos].first, p - 1));
                                        currentSize -= calc(ints1[i1Pos].second - ints1[i1Pos].first + 1);
                                        currentSize += calc(p - 1 - ints1[i1Pos].first + 1);
                                        currentSize += calc(ints1[i1Pos].second - (p + 1) + 1);
                                        ints1[i1Pos].first = p + 1;
                                    }
                                    pSize--;
                                }
                            }
                        }
                        while (i1Pos < (int)ints1.size()) {
                            ints2.push_back(ints1[i1Pos]);
                            i1Pos++;
                        }
                        ints1.clear();
                        FOR(j, ints2.size()) ints1.push_back(ints2[j]);
                    }
                }
                if (currentSize == 0) break;
                result += currentSize;
            }
        }
        print(result);
    }
}

