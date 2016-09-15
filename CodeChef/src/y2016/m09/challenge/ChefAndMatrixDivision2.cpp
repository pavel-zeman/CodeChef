// If the average size of the block is less than 2, try to optimize the blocks, so that the blocks of the size of 2 have the minimum possible maximum
// https://www.codechef.com/SEPT16/problems/CHMTDV
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

#define MAX_P 512
int hd[MAX_P], vd[MAX_P];
int hp[MAX_P];
int a[MAX_P][MAX_P];
int b[MAX_P][MAX_P];

void transpose(int n, int p) {
    FOR(i, n) FOR(j, n) b[i][j] = a[j][i];
    FOR(i, n) FOR(j, n) a[i][j] = b[i][j];
    memcpy(hp, hd, sizeof(int) * (p + 1));
    memcpy(hd, vd, sizeof(int) * (p + 1));
    memcpy(vd, hp, sizeof(int) * (p + 1));
}

LLI getMaxSum(int start, int columns, int p) {
    LLI maxSum = 0;
    FOR(j, p) {
        LLI sum = 0;
        FORE(k, hd[j], hd[j + 1]) FORE(l, start, start + columns) sum += a[k][l];
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}

double getScore(int n, int p) {
    LLI maxSum = 0;
    FOR(i, p) FOR(j, p) {
        LLI sum = 0;
        FORE(k, hd[i], hd[i + 1]) FORE(l, vd[j], vd[j + 1]) sum += a[k][l];
        maxSum = max(maxSum, sum);
    }
    double q = (double)n / (double)p;
    return maxSum / q / q;
}




bool solveWithMostColumnsOfSizeOne(int n, int p, int numDoubleColumns) {
    vector<pair<LLI, int> > m;
    int origD[MAX_P];
    memcpy(origD, vd, sizeof(int) * (p + 1));
    FOR(i, n - 1) m.push_back(make_pair(-getMaxSum(i, 2, p), i));

    bool dd[MAX_P];
    FOR(i, n) dd[i] = false;

    sort(m.begin(), m.end());
    FOR(i, numDoubleColumns) {
        int pos = m.back().second;
        m.pop_back();
        while (dd[pos + 1] || (pos > 0 && dd[pos - 1])) {
            pos = m.back().second;
            m.pop_back();
        }
        dd[pos] = true;
    }

    int j = 0;
    FOR(i, p) {
        vd[i] = j;
        if (dd[j]) j++;
        j++;
    }
    vd[p] = n;

    bool changed = false;
    FOR(i, p) if (vd[i] != origD[i]) {
        changed = true;
        break;
    }

    transpose(n, p);

    return changed;
}

bool solveWithMostColumnsOfSizeTwo(int n, int p, int smallSize) {
    vector<pair<LLI, int> > m;
    LLI maxSum2[MAX_P];
    LLI maxSum1[MAX_P];
    int bigSize = smallSize + 1;

    FOR(i, n - bigSize + 1) maxSum2[i] = getMaxSum(i, bigSize, p);
    FOR(i, n - smallSize + 1) maxSum1[i] = getMaxSum(i, smallSize, p);

    bool changed = false;
    bool localChanged = true;
    while (localChanged) {
        localChanged = false;
        int maxPos;
        LLI maxV = 0;
        FOR(i, p) {
            int l = vd[i + 1] - vd[i];
            if (l == smallSize && maxSum1[vd[i]] >= maxV) {
                maxV = maxSum1[vd[i]];
                maxPos = i;
            } else if (l == bigSize && maxSum2[vd[i]] > maxV) {
                maxV = maxSum2[vd[i]];
                maxPos = i;
            }
        }
        if (vd[maxPos + 1] - vd[maxPos] == smallSize) return false;

        int p1 = maxPos - 1;
        while (p1 >= 0) {
            int l = vd[p1 + 1] - vd[p1];
            if (l == smallSize && maxSum2[vd[p1]] < maxV) break;
            if (l == bigSize && maxSum2[vd[p1] + 1] >= maxV) {
                p1 = -1;
                break;
            }
            p1--;
        }
        if (p1 >= 0) {
            //double originalScore = getScore(n, p);
            FORE(i, p1 + 1, maxPos + 1) vd[i]++;
            //double newScore = getScore(n, p);
            /*if (newScore >= originalScore)
                printf("Error - Changed score from %.10lf to %.10lf\n", originalScore, newScore);*/
            localChanged = true;
        } else {
            p1 = maxPos + 1;
            while (p1 < p) {
                int l = vd[p1 + 1] - vd[p1];
                if (l == smallSize && maxSum2[vd[p1] - 1] < maxV) break;
                if (l == bigSize && maxSum2[vd[p1] - 1] >= maxV) {
                    p1 = p;
                    break;
                }
                p1++;
            }
            if (p1 < p) {
                //double originalScore = getScore(n, p);
                FORE(i, maxPos + 1, p1 + 1) vd[i]--;
                //double newScore = getScore(n, p);
                /*if (newScore >= originalScore)
                    printf("Error - Changed score from %.10lf to %.10lf\n", originalScore, newScore);*/
                localChanged = true;
            }
        }
        changed = changed || localChanged;
        //localChanged = false;
    }
    transpose(n, p);

    return changed;
}


int main(void) {
    int n = getInt();
    int p = getInt();
    FOR(i, n) FOR(j, n) a[i][j] = getInt();


    vd[0] = hd[0] = 0;
    FOR(i, p) vd[i + 1] = hd[i + 1] = (i + 1) * n / p;

    if (p * 2 > n) {
        int numDoubleColumns = n - p;
        if (numDoubleColumns <= p - numDoubleColumns) {
            FOR(i, 100) {
                bool changed = false;
                FOR(j, 2)
                    changed = solveWithMostColumnsOfSizeOne(n, p, numDoubleColumns) || changed;
                if (!changed) break;
            }
        } else {
            FOR(i, 1000) {
                bool changed = false;
                FOR(j, 2)
                    changed = solveWithMostColumnsOfSizeTwo(n, p, 1) || changed;
                if (!changed) break;
                //printf("Changed %.10lf\n", getScore(n, p));
            }
        }
    } else if (n % p != 0) {
        FOR(i, 1000) {
            bool changed = false;
            FOR(j, 2)
                changed = solveWithMostColumnsOfSizeTwo(n, p, n / p) || changed;
            if (!changed) break;
            //printf("Changed %.10lf\n", getScore(n, p));
        }
    }

    FOR(i, p - 1) printf("%d ", hd[i + 1]);
    printf("\n");
    FOR(i, p - 1) printf("%d ", vd[i + 1]);
    printf("\n");

    //printf("%.10lf", getScore(n, p));
}

