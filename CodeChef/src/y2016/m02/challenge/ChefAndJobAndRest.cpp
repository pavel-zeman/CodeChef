// In each step choose the book with the best possible rating per page
// https://www.codechef.com/FEB16/problems/CHEFJR
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



#define MAX_N 100010

set<pair<double, int> > setAll, setInterrupt;

#define TYPE_READ_ALL 1
#define TYPE_INTERRUPT 2

int n, m, k;
int r[MAX_N];
struct Book {
    int t, p, w;
    int preconditions;
    double ratio;
    vector<int> parents;
} book[MAX_N];

void insert(int i) {
    pair<double, int> p = make_pair(book[i].ratio, i);
    if (book[i].t == TYPE_READ_ALL) setAll.insert(p); else setInterrupt.insert(p);
}

int main(void) {
    n = getInt();
    m = getInt();
    k = getInt();
    FOR(i, n) r[i] = getInt();
    FOR(i, m) {
        book[i].t = getInt();
        book[i].p = getInt();
        book[i].w = getInt();
        book[i].ratio = -book[i].w / ((double)book[i].p);
    }
    FOR(i, k) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        book[a].parents.push_back(b);
        book[b].preconditions++;
    }

    FOR(i, m) if (book[i].preconditions == 0) {
        insert(i);
    }

    FOR(i, n) {
        vector<pair<int, int> > toRead;
        int remain = r[i];
        while (remain > 0) {
            bool all = false;
            set<pair<double, int> >::iterator itAll = setAll.begin();
            set<pair<double, int> >::iterator itInterrupt = setInterrupt.begin();
            while (itAll != setAll.end() || itInterrupt != setInterrupt.end()) {
                if (itAll != setAll.end() && book[itAll->second].p <= remain &&
                    (itInterrupt == setInterrupt.end() || itAll->first <= itInterrupt->first)) {
                    all = true;
                    break;
                }
                if (itInterrupt != setInterrupt.end() && (itAll == setAll.end() || itInterrupt->first <= itAll->first)) {
                    all = false;
                    break;
                }
                itAll++;
            }
            if (itAll != setAll.end() || itInterrupt != setInterrupt.end()) {
                int index, time;
                if (all) {
                    index = itAll->second;
                    time = book[index].p;
                    FOR(j, book[index].parents.size()) {
                        int l = book[index].parents[j];
                        if (--book[l].preconditions == 0) insert(l);
                    }
                    setAll.erase(itAll);
                } else {
                    index = itInterrupt->second;
                    time = book[index].p <= remain ? book[index].p : remain;
                    book[index].p -= time;
                    if (book[index].p == 0) {
                        FOR(j, book[index].parents.size()) {
                            int l = book[index].parents[j];
                            if (--book[l].preconditions == 0) insert(l);
                        }
                        setInterrupt.erase(itInterrupt);
                    } else {
                        setInterrupt.erase(itInterrupt);
                        book[index].ratio = -book[index].w / ((double)book[index].p);
                        insert(index);
                    }
                }
                toRead.push_back(make_pair(index + 1, time));
                remain -= time;
            } else {
                break;
            }
        }
        printf("%u ", toRead.size());
        FOR(j, toRead.size()) printf("%d %d  ", toRead[j].first, toRead[j].second);
        printf("\n");
    }
}

