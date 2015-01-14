// Use binary tree with all the possible values of x in leaves. In each vertex, store the list of positions, that contain all values of all the leaves of the whole subtree.
// http://www.codechef.com/JAN15/problems/XRQRS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <set>
#include <algorithm>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N ((1<<20) + 10)
#define BITS 18

struct vector {
    int *data;
    int icapacity;
    int isize;

    vector() {
        data = NULL;
        icapacity = 0;
        isize = 0;
    }

    void push_back(int v) {
        if (isize == icapacity) {
            if (icapacity == 0) {
                icapacity = 4;
                data = new int[icapacity];
            } else {
                icapacity <<= 2;
                int *data2 = new int[icapacity];
                FOR(i, isize) data2[i] = data[i];
                delete [] data;
                data = data2;
            }
        }
        data[isize++] = v;
    }

    void pop_back() {
        isize--;
    }

    int size() const {
        return isize;
    }

    int operator[](int index) const {
        return data[index];
    }

    bool empty() const {
        return isize == 0;
    }

};


int a[MAX_N >> 1];
vector trie[MAX_N];
int n;

int son(int x) {
    return (x << 1) + 1;
}


char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

// fast print
void print(int a) {
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



void add(int v) {
    a[n] = v;
    int pos = 0;
    int mask = 1 << BITS;
    while (mask > 0) {
        pos = son(pos);
        if ((v & mask) != 0) pos++;
        mask >>= 1;
        trie[pos].push_back(n);
    }
    n++;
}

void deleteLast() {
    n--;
    int v = a[n];
    int pos = 0;
    int mask = 1 << BITS;
    while (mask > 0) {
        pos = son(pos);
        if ((v & mask) != 0) pos++;
        mask >>= 1;
        trie[pos].pop_back();
    }
}

int findGreaterOrEqual(vector &data, int value) {
    if (data[data.size() - 1] < value) return -1;
    int l = 0;
    int r = data.size() - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (value > data[m]) l = m + 1; else r = m - 1;
    }
    if (r < 0) r = 0;
    while (r < data.size() && data[r] < value) r++;
    return r < data.size() ? r : -1;
}




int findLessOrEqual(vector &data, int value) {
    if (value < data[0]) return -1;
    int l = 0;
    int r = data.size() - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (value >= data[m]) l = m + 1; else r = m - 1;
    }
    if (l >= data.size()) l = data.size() - 1;
    while (l >= 0 && data[l] > value) l--;
    return l;
}


int getNumbersInRange(int l, int r, int pos) {
    if (!trie[pos].empty()) {
        int pl = findGreaterOrEqual(trie[pos], l);
        if (pl == -1 || trie[pos][pl] > r) return 0;
        int pr = findLessOrEqual(trie[pos], r);
        int result = pr != -1 && pl <= pr ? pr - pl + 1 : 0;
        return result;
    } else {
        return 0;
    }
}

bool existNumbersInRange(int l, int r, int pos) {
    if (!trie[pos].empty()) {
        int pl = findGreaterOrEqual(trie[pos], l);
        if (pl == -1 || trie[pos][pl] > r) return false;
        return true;
    } else {
        return false;
    }
}

int countLowerThan(int l, int r, int x) {
    int total = 0;
    int pos = 0;
    int mask = 1 << BITS;
    while (mask > 0) {
        pos = son(pos);
        if ((x & mask) != 0) {
            total += getNumbersInRange(l, r, pos);
            pos++;
        }
        mask >>= 1;
    }
    total += getNumbersInRange(l, r, pos);
    return total;
}

int getKthLowest(int l, int r, int k) {
    int pos = 0;
    FOR(i, BITS + 1) {
        pos = son(pos);
        int leftChildren = getNumbersInRange(l, r, pos);
        if (k >= leftChildren) {
            k -= leftChildren;
            pos++;
        }
        if (trie[pos].size() == 1) break;
    }
    return a[trie[pos][0]];
}

int calcXor(int l, int r, int x) {
    int pos = 0;
    int mask = 1 << BITS;
    while (mask > 0) {
        pos = son(pos);
        if ((x & mask) != 0) {
            if (!existNumbersInRange(l, r, pos)) pos++;
        } else {
            if (existNumbersInRange(l, r, pos + 1)) pos++;
        }
        mask >>= 1;
    }
    return a[trie[pos][0]];
}

int main(void) {
    int m = getInt();
    n = 0;
    FOR(i, m) {
        int type = getInt();
        int l, r, x, k;

        switch (type) {
            case 0:
                x = getInt();
                add(x);
                break;

            case 1:
                l = getInt() - 1;
                r = getInt() - 1;
                x = getInt();
                print(calcXor(l, r, x));
                break;

            case 2:
                k = getInt();
                FOR(j, k) deleteLast();
                break;

            case 3:
                l = getInt() - 1;
                r = getInt() - 1;
                x = getInt();
                print(countLowerThan(l, r, x));
                break;

            case 4:
                l = getInt() - 1;
                r = getInt() - 1;
                k = getInt() - 1;
                print(getKthLowest(l, r, k));
                break;
        }
    }
}

