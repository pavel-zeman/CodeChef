// Generate random permutation and then try all the permutations of the last LOCAL_PERMUTE digits. Repeat, until time limit.
// http://www.codechef.com/JAN15/problems/SEAND2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>
#include <time.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXD 1020
#define MAX_N 110
#define MAX_T 102

#define LOCAL_PERMUTE 6
#define LONG_NUMBER_SEGMENT 9
#define LONG_NUMBER_POWER 1000000000


#define MAX_HEAP_ITEMS 1020
template <class PAYLOAD> class HeapItem {
public:
    int value;
    PAYLOAD payload;

    HeapItem() {}

    HeapItem(int value, PAYLOAD payload) {
        this->value = value;
        this->payload = payload;
    }
};


template <class PAYLOAD> class MaxHeap {
public:
    HeapItem<PAYLOAD> data[MAX_HEAP_ITEMS];
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

    void add(int value, PAYLOAD payload) {
        int pos = size++;
        data[pos] = HeapItem<PAYLOAD>(value, payload);
        int parent = getParent(pos);
        while (pos > 0 && data[pos].value > data[parent].value) {
            HeapItem<PAYLOAD> temp = data[pos];
            data[pos] = data[parent];
            data[parent] = temp;
            pos = parent;
            parent = getParent(pos);
        }
        printContents();
    }

    HeapItem<PAYLOAD> removeTop() {
        HeapItem<PAYLOAD> result = data[0];
        data[0] = data[--size];
        int pos = 0;
        int son = getSon(pos);
        while ((son < size && data[son].value > data[pos].value) || (son + 1 < size && data[son + 1].value > data[pos].value)) {
            int maxSon = son;
            if (son + 1 < size && data[son + 1].value > data[son].value) maxSon = son + 1;
            HeapItem<PAYLOAD> temp = data[pos];
            data[pos] = data[maxSon];
            data[maxSon] = temp;
            pos = maxSon;
            son = getSon(pos);
        }
        printContents();
        return result;
    }

    void printContents() {
        /*printf("Heap: ");
        FOR(i, size) printf("%d=%d,", data[i].value, data[i].payload);
        printf("\n");*/
    }

    int getMinValue() {
        return data[0].value;
    }

    bool empty() {
        return size == 0;
    }
};


char input[MAX_T][MAXD];
int integer[MAXD];
int inputSize[MAX_T];
int n[MAX_T];
int b[MAX_T][MAX_N];
int sumb[MAX_T];
int remainders[MAX_N];
int localMinValue;
long long int longNumber[MAXD / LONG_NUMBER_SEGMENT];
long long int longNumberSize;
int initialPermutationValue;
int localMinPermutationValue;
int permutation[LOCAL_PERMUTE];

int globalMinInteger[MAX_T][MAXD];
int globalMinPermutationValue[MAX_T];
int globalMinValue[MAX_T];
MaxHeap<int> heap;


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

void readInteger(int t) {
    char *result = input[t];
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        *result++ = c - '0';
        c = getc_unlocked(stdin);
    }
    *result = 0;
    inputSize[t] = result - input[t];
}

void generatePermutation(int t) {
    FOR(i, inputSize[t]) integer[i] = input[t][i];
    FOR(i, inputSize[t]) {
        int j = rand() % (inputSize[t] - i);
        char t = integer[i];
        integer[i] = integer[i + j];
        integer[i + j] = t;
    }

    int count[10];
    FOR(i, 10) count[i] = 0;
    FOR(i, LOCAL_PERMUTE) count[integer[i]]++;
    int pos = 0;
    initialPermutationValue = 0;
    for(int i=9;i>0;i--) FOR(j, count[i]) integer[pos++] = i;
    for(int i=LOCAL_PERMUTE - 1;i>=0;i--) initialPermutationValue = initialPermutationValue * 10 + integer[i];

    pos = 0;
    longNumberSize = 0;
    while (pos < inputSize[t]) {
        int segmentEnd = pos + LONG_NUMBER_SEGMENT;
        if (segmentEnd > inputSize[t]) segmentEnd = inputSize[t];
        int power = 1;
        int value = 0;
        while (pos < segmentEnd) {
            value += power * integer[pos++];
            power *= 10;
        }
        longNumber[longNumberSize++] = value;
    }
}

void calcInitialRemainders(int t) {
    FOR(i, n[t]) {
        long long int remainder = 0;
        for(int j=longNumberSize - 1;j>=0;j--) {
            remainder = remainder * LONG_NUMBER_POWER + longNumber[j];
            remainder = remainder % b[t][i];
        }
        remainders[i] = remainder;
    }
}

void checkPermutation(int t, int level, int value) {
    if (level < LOCAL_PERMUTE) {
        value *= 10;
        int v1 = permutation[level];
        FORE(i, level, LOCAL_PERMUTE) {
            int v2 = permutation[i];
            permutation[i] = v1;
            checkPermutation(t, level + 1, value + integer[v2]);
            permutation[i] = v2;
        }
    } else {
        int f = 0;
        FOR(i, n[t]) f += (remainders[i] + value - initialPermutationValue) % b[t][i];
        if (f < localMinValue) {
            localMinValue = f;
            localMinPermutationValue = value;
        }
    }
}

void checkSmallPermutation(int t, int level, int value) {
    if (level < inputSize[t]) {
        value *= 10;
        int v1 = permutation[level];
        FORE(i, level, inputSize[t]) {
            int v2 = permutation[i];
            permutation[i] = v1;
            checkSmallPermutation(t, level + 1, value + integer[v2]);
            permutation[i] = v2;
        }
    } else {
        int f = 0;
        FOR(i, n[t]) f += value % b[t][i];
        if (f < localMinValue) {
            localMinValue = f;
            localMinPermutationValue = value;
        }
    }
}

int getValue(int tt) {
    return ((long long int)globalMinValue[tt]) * 1000000 / sumb[tt];
}


int main(void) {
    FOR(i, LOCAL_PERMUTE) permutation[i] = i;
    srand(1);
    int t = getInt();
    clock_t startTime = clock();

    FOR(tt, t) {
        readInteger(tt);
        n[tt] = getInt();
        sumb[tt] = 0;
        FOR(i, n[tt]) sumb[tt] += (b[tt][i] = getInt());

        if (inputSize[tt] <= LOCAL_PERMUTE) {
            localMinValue = MAX_N * 1000000;
            FOR(i, inputSize[tt]) integer[i] = input[tt][i];
            checkSmallPermutation(tt, 0, 0);
            globalMinPermutationValue[tt] = localMinPermutationValue;
        } else {
            globalMinValue[tt] = sumb[tt];
            heap.add(getValue(tt), tt);
        }
    }


    while (clock() - startTime < 4.9 * CLOCKS_PER_SEC && !heap.empty()) {
        while (clock() - startTime < 4.9 * CLOCKS_PER_SEC && !heap.empty()) {
            HeapItem<int> root = heap.removeTop();
            clock_t localStartTime = clock();
            int item = root.payload;
            while (clock() - startTime < 4.9 * CLOCKS_PER_SEC && clock() - localStartTime < CLOCKS_PER_SEC) {
                localMinValue = MAX_N * 1000000;
                generatePermutation(item);
                calcInitialRemainders(item);
                checkPermutation(item, 0, 0);
                if (localMinValue < globalMinValue[item]) {
                    globalMinValue[item] = localMinValue;
                    globalMinPermutationValue[item] = localMinPermutationValue;
                    FOR(i, inputSize[item]) globalMinInteger[item][i] = integer[i];
                    heap.add(getValue(item), item);
                    break;
                }
            }
        }
        if (heap.empty()) {
            FOR(tt, t)
                if (inputSize[tt] > LOCAL_PERMUTE)
                    heap.add(getValue(tt), tt);
        }
    }

    FOR(tt, t) {
        if (inputSize[tt] <= LOCAL_PERMUTE) {
            printf("%d\n", globalMinPermutationValue[tt]);
        } else {
            for(int i=inputSize[tt] - 1;i>=LOCAL_PERMUTE;i--) printf("%d", globalMinInteger[tt][i]);
            printf("%d\n", globalMinPermutationValue[tt]);
        }
    }
}
