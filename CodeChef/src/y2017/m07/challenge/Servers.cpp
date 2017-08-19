// Description
// https://www.codechef.com/JULY17/problems/SRVRS
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

#define MAX_C 500010
#define MAX_Q 100010

struct Cpu {
    int x, y, p;
    int s, c;
} cpus[MAX_C];
int totalCpus;
vector<int> add[MAX_Q];


#define MAX_HEAP_ITEMS MAX_C
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
    int n = getInt();
    int q = getInt();
    FOR(i, n) {
        int x = getInt();
        int y = getInt();
        int k = getInt();
        FOR(j, k) {
            cpus[totalCpus].x = x;
            cpus[totalCpus].y = y;
            cpus[totalCpus].p = getInt();
            cpus[totalCpus].s = i + 1;
            cpus[totalCpus].c = j + 1;
            heap.add(cpus[totalCpus].p, totalCpus);
            totalCpus++;
        }
    }
    FOR(i, q) {
        for(auto it = add[i].begin(); it != add[i].end(); it++) heap.add(cpus[*it].p, *it);
        printf("?\n");
        fflush(stdout);
        int x = getInt();
        int y = getInt();
        auto top = heap.removeTop();
        printf("! %d %d\n", cpus[top.index].s, cpus[top.index].c);
        int nextPos = i + cpus[top.index].p;
        if (nextPos < q) add[nextPos].push_back(top.index);
    }
    printf("end\n");
    fflush(stdout);
}

