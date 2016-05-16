// Just "brute force" solution - start with the least weight and then use Dijkstra algorithm to find way to following junction.
// https://www.codechef.com/MAY16/problems/SHOP2
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


#define MAX_HEAP_ITEMS 1010
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


#define MAX_GOODS 1000
#define MAX_N 1010

struct Goods {
    int weight;
    int junctionToBuy;
    int index;
    bool bought;

    bool operator<(const Goods &other) const {
        return this->weight < other.weight;
    }
} goods[MAX_GOODS];

int price[MAX_N][MAX_GOODS];

vector<int> neighbors[MAX_N];

int prevNode[MAX_N];
int visited[MAX_N];
int searchNum;
int path[MAX_N];
vector<int> commands;
vector<int> totalPath;
set<int> toBuyAtJunction[MAX_N];
map<int, vector<int>> toBuyAtIndex;
bool junctionInPath[MAX_N];
int cost[MAX_N][MAX_N];
int nodeCost[MAX_N];
int testb[MAX_GOODS];

int findPath(int start, int end) {
    heap.size = 0;
    nodeCost[start] = 0;
    heap.add(0, start);
    visited[start] = ++searchNum;
    while (true) {
        HeapItem item = heap.removeTop();
        int node = item.index;
        //print(node);
        if (node == end) {
            int pos = 0;
            while (node != start) {
                path[pos++] = node;
                node = prevNode[node];
            }
            return pos;
        }
        FOR(i, neighbors[node].size()) {
            int next = neighbors[node][i];
            if (visited[next] != searchNum) {
                visited[next] = searchNum;
                nodeCost[next] = item.value + cost[node][next];
                heap.add(nodeCost[next], next);
                prevNode[next] = node;
            } else {
                if (item.value + cost[node][next] < nodeCost[next]) {
                    heap.removeAtIndex(next);
                    nodeCost[next] = item.value + cost[node][next];
                    heap.add(nodeCost[next], next);
                    prevNode[next] = node;
                }
            }
        }
    }
}

int main(void) {
    int n = getInt();
    int m = getInt();
    int k = getInt();
    getInt(); // ignore the budget
    //int f = getInt();
    FOR(i, k) {
        int p = getInt();
        goods[i].weight = getInt();
        goods[i].index = i;
        int minPrice = 1000000000;
        int minJunction = -1;
        FOR(j, p) {
            int junction = getInt() - 1;
            int pp = getInt();
            price[junction][i] = pp;
            if (pp < minPrice) {
                minPrice = pp;
                minJunction = junction;
            }
        }
        goods[i].junctionToBuy = minJunction;

    }
    sort(goods, goods + k);
    FOR(i, k) {
        toBuyAtJunction[goods[i].junctionToBuy].insert(i);
    }
    FOR(i, m) {
        int x = getInt() - 1;
        int y = getInt() - 1;
        cost[x][y] = cost[y][x] = getInt();
        neighbors[x].push_back(y);
        neighbors[y].push_back(x);
    }
    int curj = 0;
    totalPath.push_back(curj);

    for(set<int>::iterator it = toBuyAtJunction[curj].begin(); it != toBuyAtJunction[curj].end(); it++) {
        goods[*it].bought = true;
    }

    FOR(i, k) {
        if (!goods[i].bought) {
            int l = findPath(curj, goods[i].junctionToBuy) - 1;
            while (l >= 0) {
                int node = path[l--];
                totalPath.push_back(node);
                if (!toBuyAtJunction[node].empty()) {
                    for(set<int>::iterator it = toBuyAtJunction[node].begin(); it != toBuyAtJunction[node].end(); it++) {
                        goods[*it].bought = true;
                    }
                }
            }
            curj = goods[i].junctionToBuy;
        }
    }
    int l = findPath(curj, n - 1) - 1;
    while (l >= 0) totalPath.push_back(path[l--]);
    l = totalPath.size() - 1;
    while (l >= 0) {
        int j = totalPath[l];
        if (!junctionInPath[j]) {
            junctionInPath[j] = true;
            if (!toBuyAtJunction[j].empty()) {
                for(set<int>::iterator it = toBuyAtJunction[j].begin(); it != toBuyAtJunction[j].end(); it++) {
                    toBuyAtIndex[l].push_back(goods[*it].index);
                }
            }
        }
        l--;
    }

    FOR(i, totalPath.size()) {
        int j = totalPath[i];
        if (i > 0) commands.push_back(j + 1);
        if (toBuyAtIndex.find(i) != toBuyAtIndex.end()) {
            vector<int> &data = toBuyAtIndex[i];
            FOR(k, data.size()) commands.push_back(-data[k] - 1);
        }
    }

    FOR(i, commands.size()) {
        int x = commands[i];
        if (x < 0) testb[-x - 1]++;
    }

    FOR(i, k) {
        if (testb[i] < 1) fail();
    }

    print(commands.size());
    FOR(i, commands.size()) print(commands[i]);
}

