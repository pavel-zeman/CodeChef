// Greedy algorithm, which prefers teachers with the highest sadness
// https://www.codechef.com/JULY17/problems/IPCTRAIN
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

#define MAX_N 100010
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


class MaxHeap {
public:
    HeapItem data[MAX_HEAP_ITEMS];
    int size;

    MaxHeap() {
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
        while (pos > 0 && temp.value > data[parent].value) {
            data[pos] = data[parent];
            pos = parent;
            parent = getParent(pos);
        }
        data[pos] = temp;
    }

    void down(int pos) {
        int son = getSon(pos);
        HeapItem temp = data[pos];
        while ((son < size && data[son].value > temp.value) || (son + 1 < size && data[son + 1].value > temp.value)) {
            int maxSon = son;
            if (son + 1 < size && data[son + 1].value > data[son].value) maxSon = son + 1;

            data[pos] = data[maxSon];

            pos = maxSon;
            son = getSon(pos);
        }
        data[pos] = temp;
    }

    void add(int value, int index) {
        int pos = size++;
        data[pos] = HeapItem(value, index);
        up(pos);
    }

    HeapItem removeTop() {
        HeapItem result = data[0];
        data[0] = data[--size];
        down(0);
        return result;
    }

    HeapItem & top() {
        return data[0];
    }

    bool empty() {
        return size == 0;
    }
};

MaxHeap heap;

int n, d;

struct Trainer {
    int d;
    int t;
    int s;

    bool operator<(const Trainer & other) const {
        return this->d < other.d;
    }
} trainers[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        d = getInt();
        LLI total = 0;
        FOR(i, n) {
            trainers[i].d = getInt();
            trainers[i].t = getInt();
            trainers[i].s = getInt();
            total += trainers[i].t * (LLI)trainers[i].s;
        }
        heap.size = 0;
        sort(trainers, trainers + n);
        int tp = 0;
        for(int i = 1; i <= d; i++) {
            while (tp < n && trainers[tp].d == i) {
                heap.add(trainers[tp].s, tp);
                tp++;
            }
            if (!heap.empty()) {
                int ind = heap.top().index;
                total -= trainers[ind].s;
                if (--trainers[ind].t == 0) heap.removeTop();
            }
        }
        print(total);
    }
}

