// Dynamic programming + heap to get the lowest price for each dish.
// http://www.codechef.com/JULY15/problems/MCHEF
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MAX_K 510
#define INF -10000000000000000LL

int a[MAX_N];
int c[MAX_N];
vector<int> start[MAX_N];
vector<int> end[MAX_N];
int n, k, m;

long long int v[MAX_K];

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

void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}


#define MAX_HEAP_ITEMS MAX_N
class HeapItem {
public:
    int value;
    int index; // index of the value in some external array

    HeapItem() {}

    HeapItem(int value, int index) {
        this->value = value;
        this->index = index;
    }
};


class MinHeap {
public:
    HeapItem data[MAX_HEAP_ITEMS];
    int size;
    int position[MAX_HEAP_ITEMS];

    MinHeap() {
        size = 0;
    }

    int getSon(int a) {
        return (a << 1) + 1;
    }

    int getParent(int a) {
        return (a - 1) >> 1;
    }

    void up(int pos) {
        int parent = getParent(pos);
        HeapItem temp = data[pos];
        while (pos > 0 && temp.value < data[parent].value) {
            data[pos] = data[parent];
            position[data[pos].index] = pos;

            pos = parent;
            parent = getParent(pos);
        }
        data[pos] = temp;
        position[data[pos].index] = pos;
    }

    void down(int pos) {
        int son = getSon(pos);
        HeapItem temp = data[pos];
        while ((son < size && data[son].value < temp.value) || (son + 1 < size && data[son + 1].value < temp.value)) {
            int maxSon = son;
            if (son + 1 < size && data[son + 1].value < data[son].value) maxSon = son + 1;

            data[pos] = data[maxSon];
            position[data[pos].index] = pos;

            pos = maxSon;
            son = getSon(pos);
        }
        data[pos] = temp;
        position[data[pos].index] = pos;
    }

    void add(int value, int index) {
        int pos = size++;
        data[pos] = HeapItem(value, index);
        position[index] = pos;
        up(pos);
    }

    HeapItem removeTop() {
        HeapItem result = data[0];
        position[data[0].index] = -1;
        data[0] = data[--size];
        position[data[0].index] = 0;

        down(0);
        return result;
    }

    void removeAtIndex(int index) {
        int pos = position[index];
        position[index] = -1;
        if (pos <= size - 1) {
            data[pos] = data[size - 1];
            position[data[pos].index] = pos;
            if (pos > 0 && data[pos].value < data[getParent(pos)].value) {
                up(pos);
            } else {
                down(pos);
            }
        }
        size--;
    }

    void printContents() {
        printf("Heap: ");
        FOR(i, size) printf("%d=%d,", data[i].value, data[i].index);
        printf("\n");
    }

    int minValue() {
        return data[0].value;
    }

    bool empty() {
        return size == 0;
    }

    void checkIntegrity() {
        FORE(i, 1, size) if (data[i].value < data[getParent(i)].value) {
            printf("Value at %d is less than value at %d\n", i, getParent(i));
            fail();
        }
    }
};

MinHeap heap;


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        if (!heap.empty()) fail();
        n = getInt();
        k = getInt();
        m = getInt();
        FOR(i, n) a[i] = getSignedInt();
        FOR(i, n) start[i].clear(), end[i].clear();
        FOR(i, m) {
            int l = getInt() - 1;
            int r = getInt() - 1;
            c[i] = getInt();
            start[l].push_back(i);
            end[r].push_back(i);
        }
        FOR(i, k) v[i] = INF;
        v[k] = 0;
        int k1 = k + 1;
        long long int add = 0;
        FOR(i, n) {
            FOR(j, start[i].size()) heap.add(c[start[i][j]], start[i][j]);

            if (a[i] >= 0 || heap.empty() || heap.minValue() > k) {
                add += a[i];
            } else {
                int price = heap.minValue();
                int fin = k1 - price;
                FOR(j, fin) v[j] = mx(v[j] + a[i], v[j + price]);
                FORE(j, k1 - price, k1) v[j] += a[i];
            }

            FOR(j, end[i].size()) heap.removeAtIndex(end[i][j]);
        }

        long long int result = INF;
        FOR(i, k + 1) if (v[i] > result) result = v[i];
        if (result == INF) fail();
        print(result + add);
    }
}
