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
