// Segment tree with lazy propagation
// https://www.codechef.com/OCT16/problems/BGQRS
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


#define MAX_N 100010
int five[MAX_N], two[MAX_N];
int totalFives[MAX_N], totalTwos[MAX_N];


struct Node {
    int two;
    int five;

    int lazyTwo;
    int lazyFive;

    int replaceTwo;
    int replaceFive;
    int replaceStartIndex;

} nodes[MAX_N * 3];

int getTotal(int startIndex, int endIndex, int v) {
    return v == 2 ? totalTwos[endIndex] - totalTwos[startIndex - 1] : totalFives[endIndex] - totalFives[startIndex - 1];
}

int numDivisors(int value, int div) {
    int result = 0;
    while (value % div == 0) {
        result++;
        value /= div;
    }
    return result;
}

void buildTree(int node, int a, int b) {
    if (a == b) {
        nodes[node].five = five[a];
        nodes[node].two = two[a];
    } else {
        int mid = (a + b) >> 1;
        int child = (node << 1) + 1;
        buildTree(child, a, mid);
        buildTree(child + 1, mid + 1, b);
        nodes[node].two = nodes[child].two + nodes[child + 1].two;
        nodes[node].five = nodes[child].five + nodes[child + 1].five;
    }
    nodes[node].lazyTwo = 0;
    nodes[node].lazyFive = 0;
    nodes[node].replaceStartIndex = 0;
}

void distributeReplace(int node, int na, int nb) {
    int child = (node << 1) + 1;
    int mid = (na + nb) >> 1;

    if (nodes[node].replaceStartIndex > 0) {
        nodes[node].two = nodes[node].replaceTwo * (nb - na + 1) + getTotal(nodes[node].replaceStartIndex, nodes[node].replaceStartIndex + nb - na, 2);
        nodes[node].five = nodes[node].replaceFive * (nb - na + 1) + getTotal(nodes[node].replaceStartIndex, nodes[node].replaceStartIndex + nb - na, 5);
        //printf("New replaces %lld %lld for %d %d\n", nodes[node].two, nodes[node].five, na + 1, nb + 1);
        if (na != nb) {
            nodes[child].lazyTwo = 0;
            nodes[child].lazyFive = 0;
            nodes[child].replaceTwo = nodes[node].replaceTwo;
            nodes[child].replaceFive = nodes[node].replaceFive;
            nodes[child].replaceStartIndex = nodes[node].replaceStartIndex;

            nodes[child + 1].lazyTwo = 0;
            nodes[child + 1].lazyFive = 0;
            nodes[child + 1].replaceTwo = nodes[node].replaceTwo;
            nodes[child + 1].replaceFive = nodes[node].replaceFive;
            nodes[child + 1].replaceStartIndex = nodes[node].replaceStartIndex + (mid - na + 1);
        }
        nodes[node].replaceStartIndex = 0;
    }
}


void distributeMul(int node, int na, int nb) {
    int child = (node << 1) + 1;
    if (nodes[node].lazyTwo > 0 || nodes[node].lazyFive > 0) {
        nodes[node].two += nodes[node].lazyTwo * (nb - na + 1);
        nodes[node].five += nodes[node].lazyFive * (nb - na + 1);
        if (na != nb) {
            nodes[child].lazyTwo += nodes[node].lazyTwo;
            nodes[child].lazyFive += nodes[node].lazyFive;
            nodes[child + 1].lazyTwo += nodes[node].lazyTwo;
            nodes[child + 1].lazyFive += nodes[node].lazyFive;
        }
        nodes[node].lazyTwo = 0;
        nodes[node].lazyFive = 0;
    }
}

void mulTree(int node, int na, int nb, int l, int r, int twoCount, int fiveCount) {
    int child = (node << 1) + 1;
    distributeReplace(node, na, nb);
    distributeMul(node, na, nb);
    if (nb < l || na > r) return;

    if (na >= l && nb <= r) {
        nodes[node].two += twoCount * (nb - na + 1);
        nodes[node].five += fiveCount * (nb - na + 1);
        if (na != nb) {
            nodes[child].lazyTwo += twoCount;
            nodes[child].lazyFive += fiveCount;
            nodes[child + 1].lazyTwo += twoCount;
            nodes[child + 1].lazyFive += fiveCount;
        }
        return;
    }

    int mid = (na + nb) >> 1;
    mulTree(child, na, mid, l, r, twoCount, fiveCount);
    mulTree(child + 1, mid + 1, nb, l, r, twoCount, fiveCount);

    nodes[node].two = nodes[child].two + nodes[child + 1].two;
    nodes[node].five = nodes[child].five + nodes[child + 1].five;
}


void replaceTree(int node, int na, int nb, int l, int r, int twoCount, int fiveCount) {
    int child = (node << 1) + 1;
    int mid = (na + nb) >> 1;
    if (na >= l && nb <= r) {
        nodes[node].two = twoCount * (nb - na + 1) + getTotal(na - l + 1, nb - l + 1, 2);
        nodes[node].five = fiveCount * (nb - na + 1) + getTotal(na - l + 1, nb - l + 1, 5);
        //printf("Setting replaces %lld %lld for %d %d\n", nodes[node].two, nodes[node].five, na + 1, nb + 1);
        if (na != nb) {
            //printf("Setting replace for child nodes %d, %d\n", child, child + 1);
            nodes[child].lazyTwo = 0;
            nodes[child].lazyFive = 0;
            nodes[child].replaceTwo = twoCount;
            nodes[child].replaceFive = fiveCount;
            nodes[child].replaceStartIndex = na - l + 1;

            nodes[child + 1].lazyTwo = 0;
            nodes[child + 1].lazyFive = 0;
            nodes[child + 1].replaceTwo = twoCount;
            nodes[child + 1].replaceFive = fiveCount;
            nodes[child + 1].replaceStartIndex = na - l + 1 + (mid - na + 1);
        }
        nodes[node].replaceStartIndex = 0;
        nodes[node].lazyFive = 0;
        nodes[node].lazyTwo = 0;
        return;
    }

    distributeReplace(node, na, nb);
    distributeMul(node, na, nb);

    if (nb < l || na > r) return;

    replaceTree(child, na, mid, l, r, twoCount, fiveCount);
    replaceTree(child + 1, mid + 1, nb, l, r, twoCount, fiveCount);

    nodes[node].two = nodes[child].two + nodes[child + 1].two;
    nodes[node].five = nodes[child].five + nodes[child + 1].five;
}

LLI totalFive, totalTwo;
void calcProduct(int node, int na, int nb, int l, int r) {
    if (nb < l || na > r) return;

    //printf("Processing node %d from %d to %d\n", node, na + 1, nb + 1);
    distributeReplace(node, na, nb);
    distributeMul(node, na, nb);

    if (na >= l && nb <= r) {
        //printf("Adding %lld %lld from %d to %d\n", nodes[node].two, nodes[node].five, na + 1, nb + 1);
        totalTwo += nodes[node].two;
        totalFive += nodes[node].five;
        return;
    }

    int mid = (na + nb) >> 1;
    int child = (node << 1) + 1;
    calcProduct(child, na, mid, l, r);
    calcProduct(child + 1, mid + 1, nb, l, r);
}


int main(void) {
    int step = 2;
    while (step < MAX_N) {
        for(int i = step; i < MAX_N; i += step) totalTwos[i]++;
        step *= 2;
    }
    step = 5;
    while (step < MAX_N) {
        for(int i = step; i < MAX_N; i += step) totalFives[i]++;
        step *= 5;
    }
    FORE(i, 1, MAX_N) {
        totalTwos[i] += totalTwos[i - 1];
        totalFives[i] += totalFives[i - 1];
    }


    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n) {
            int a = getInt();
            five[i] = numDivisors(a, 5);
            two[i] = numDivisors(a, 2);
        }
        buildTree(0, 0, n - 1);
        LLI result = 0;
        FOR(i, m) {
            int type = getInt();
            int l = getInt() - 1;
            int r = getInt() - 1;
            int x, y;
            switch (type) {
            case 1:
                x = getInt();
                mulTree(0, 0, n - 1, l, r, numDivisors(x, 2), numDivisors(x, 5));
                break;
            case 2:
                y = getInt();
                replaceTree(0, 0, n - 1, l, r, numDivisors(y, 2), numDivisors(y, 5));
                break;
            case 3:
                totalFive = 0;
                totalTwo = 0;
                calcProduct(0, 0, n - 1, l, r);
                result += min(totalFive, totalTwo);
                //print(min(totalFive, totalTwo));
                break;
            }
        }
        print(result);
    }
}

