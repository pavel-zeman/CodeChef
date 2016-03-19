// Calculate all possible sums, store them as a "histogram" (number of occurrences for each sum) and then do binary search
// https://www.codechef.com/MARCH16/problems/HBIRD
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
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

#define MAX_DATA 113000
#define MAX_HUNGRY (MAX_DATA * 25)
#define MAX_VALUE 1000000010
char data[MAX_DATA];
int rowSum[MAX_DATA];
int columnSum[MAX_DATA];
int c[MAX_HUNGRY];
int totalCount[MAX_HUNGRY];
int sums[MAX_HUNGRY];

int main(void) {
    int rows = getInt();
    int columns = getInt();
    int q = getInt();
    int pos = 0;
    FOR(i, rows) FOR(j, columns) data[pos++] = getInt();
    pos = 0;
    int sum = 0;
    FOR(i, rows) {
        FOR(j, columns) {
            rowSum[pos] = sum;
            sum += data[pos++];
        }
    }
    rowSum[pos] = sum;

    FOR(i, columns) {
        sum = 0;
        FOR(j, rows) {
            sum += data[pos = j * columns + i];
            columnSum[pos] = sum;
        }
    }

    // go down
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j + k < columns && i + k < rows; k++) {
                sum += rowSum[(i + k) *  columns + j + k + 1] - rowSum[(i + k) *  columns + j];
                c[sum]++;
            }
        }
    }
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j - k >= 0 && i + k < rows; k++) {
                sum += rowSum[(i + k) *  columns + j + 1] - rowSum[(i + k) *  columns + j - k];
                c[sum]++;
            }
        }
    }

    // go up
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j + k < columns && i - k >= 0; k++) {
                sum += rowSum[(i - k) *  columns + j + k + 1] - rowSum[(i - k) *  columns + j];
                c[sum]++;
            }
        }
    }
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j - k >= 0 && i - k >= 0; k++) {
                sum += rowSum[(i - k) *  columns + j + 1] - rowSum[(i - k) *  columns + j - k];
                c[sum]++;
            }
        }
    }

    // vertical
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j + k < columns && j - k >= 0 && i + k < rows; k++) {
                sum += rowSum[(i + k) *  columns + j + k + 1] - rowSum[(i + k) *  columns + j - k];
                c[sum]++;
            }
        }
    }
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j + k < columns && j - k >= 0 && i - k >= 0; k++) {
                sum += rowSum[(i - k) *  columns + j + k + 1] - rowSum[(i - k) *  columns + j - k];
                c[sum]++;
            }
        }
    }

    // horizontal
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j + k < columns && i - k >= 0 && i + k < rows; k++) {
                sum += columnSum[(i + k) *  columns + j + k] - columnSum[(i - k) *  columns + j + k] + data[(i - k) * columns + j + k];
                c[sum]++;
            }
        }
    }
    FOR(i, rows) {
        FOR(j, columns) {
            int sum = data[i * columns + j];
            for(int k = 1; j - k >= 0 && i - k >= 0 && i + k < rows; k++) {
                sum += columnSum[(i + k) *  columns + j - k] - columnSum[(i - k) *  columns + j - k] + data[(i - k) * columns + j - k];
                c[sum]++;
            }
        }
    }

    LLI total = 0;
    sums[0] = totalCount[0] = 0;
    FORE(i, 1, MAX_HUNGRY) {
        total += i * (LLI)c[i];
        if (total > MAX_VALUE) {
            FORE(j, i, MAX_HUNGRY) sums[j] = MAX_VALUE;
            break;
        }
        sums[i] = total;
        totalCount[i] = totalCount[i - 1] + c[i];
    }

    FOR(i, q) {
        int g = getInt();
        int *it = upper_bound(sums, sums + MAX_HUNGRY, g);
        int pos = it - sums - 1;
        int birds = totalCount[pos];
        if (pos < MAX_HUNGRY - 1) birds += (g - sums[pos]) / (pos + 1);

        print(birds);
    }

}

