// Brute force for small sets, random subset generation for all other sets 
// http://www.codechef.com/NOV13/problems/SEAVEC
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <sys/resource.h>
#include <time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_DATA 100010
#define MAX_T 11
#define MAX_LEVEL 20
#define MAX_TIME 2600000
#define CHECK_INTERVAL 500000
#define MAX_PROB 50

int data[MAX_T][MAX_DATA];
int usableData[MAX_T][MAX_DATA];
int a[MAX_T][MAX_DATA];
int indexes[MAX_T][MAX_DATA];
int n[MAX_T], k[MAX_T];
int usableN[MAX_T];

long long int sumA[MAX_T];
double maxTotal[MAX_T];
int resultSize[MAX_T];
int result[MAX_T][MAX_DATA];

long long int minDiff;
int curN, curK;
int curUsableN;
int selected[MAX_DATA];
int minSelected[MAX_DATA];
int remaining[MAX_DATA];
int maxLevel;
int curT;
bool used[MAX_DATA];
int prob[MAX_T][MAX_DATA * MAX_PROB];
int probCount[MAX_T];

int startTime;
bool finish = false;

int timeCounter = 0;

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



int getTime() {
    struct rusage t;
    struct timeval tv;
    getrusage(RUSAGE_SELF, &t);
    tv = t.ru_utime;
    return t.ru_utime.tv_sec * 1000000 + t.ru_utime.tv_usec;
}

void startTimer() {
    startTime = getTime();
}

int currentTime() {
    return getTime() - startTime;
}


bool lower(int *v1, int *v2) {
    FOR(i, curK) if (v1[i] > v2[i]) return false;
    return true;
}

long long int diff(int *v1, int *v2) {
    long long int result = 0;
    FOR(i, curK) result += v1[i] - v2[i];
    return result;
}

long long int sum(int *v) {
    long long int result = 0;
    FOR(i, curK) result += v[i];
    return result;
}

bool sub(int *v1, int *v2) {
    FOR(i, curK) {
        if (v1[i] >= v2[i]) {
            v1[i] -= v2[i];
        } else {
            FOR(j, i) v1[j] += v2[j];
            return false;
        }
    }
    return true;
}

void add(int *v1, int *v2) {
    FOR(i, curK) v1[i] += v2[i];
}

void generate(int level, int first) {
    if (level == maxLevel) {
        int d = sum(remaining);
        if (d < minDiff) {
            minDiff = d;
            FOR(i, level) minSelected[i] = selected[i];
        }
    } else {
        FORE(i, first, curUsableN) {
            if (sub(remaining, usableData[curT] + i * curK)) {
                selected[level] = i;
                generate(level + 1, i + 1);
                add(remaining, usableData[curT] + i * curK);
            }
        }
    }
}

void crash() {
    *((char *)0) = 0;
}

int cmp(const void *p1, const void *p2) {
    return *((int *)p1) - *((int *)p2);
}


int main(void) {
    //srand(time(NULL));
    startTimer();
    int t = getInt();
    FOR(tt, t) {
        curN = n[tt] = getInt();
        curK = k[tt] = getInt();

        FOR(i, curN) {
            FOR(j, curK) data[tt][i * curK + j] = getInt();
        }
        FOR(j, curK) a[tt][j] = getInt();
        sumA[tt] = sum(a[tt]);


        curUsableN = 0;
        FOR(i, curN) {
            if (lower(data[tt] + i * curK, a[tt])) {
                indexes[tt][curUsableN] = i;
                FOR(j, curK) usableData[tt][curUsableN * curK + j] = data[tt][i * curK + j];
                curUsableN++;
            }
        }
        usableN[tt] = curUsableN;

        resultSize[tt] = 0;
        maxTotal[tt] = -1;

    }


    // first check the items, that can be solved completely
    FOR(l, MAX_LEVEL) {
        maxLevel = l + 1;
        FOR(tt, t) {
            if (usableN[tt] <= 10 && l + 1 <= usableN[tt]) {
                minDiff = sumA[tt];
                curN = n[tt];
                curK = k[tt];
                curUsableN = usableN[tt];
                curT = tt;

                FOR(i, curK) remaining[i] = a[tt][i];
                generate(0, 0);

                if (minDiff < sumA[tt] && (l + 1) / (minDiff + 1.0) > maxTotal[tt]) {
                    maxTotal[tt] = (l + 1) / (minDiff + 1.0);
                    resultSize[tt] = l + 1;
                    FOR(i, l + 1) result[tt][i] = minSelected[i];
                }
            }
        }
    }

    int numNext = 0;
    FOR(tt, t) if (usableN[tt] > 10) numNext++;

    if (numNext > 0) {
        FOR(tt, t) {
            if (usableN[tt] > 10) {
                long long int sums[MAX_DATA];
                FOR(i, usableN[tt]) sums[i] = sum(usableData[tt] + i * k[tt]);
                long long int maxSum = 0;
                FOR(i, usableN[tt]) if (sums[i] > maxSum) maxSum = sums[i];
                int pCount = 0;
                FOR(i, usableN[tt]) {
                    int c = sums[i] * MAX_PROB / maxSum;
                    if (c < 1) c = 1;
                    FOR(j, c) prob[tt][pCount++] = i;
                }
                probCount[tt] = pCount;
            }
        }

        while (!finish) {
            FOR(tt, t) {
                if (usableN[tt] > 10) {
                    curUsableN = usableN[tt];

                    curN = n[tt];
                    curK = k[tt];
                    curT = tt;

                    int pCount = probCount[tt];

                    FOR(i, curK) remaining[i] = a[tt][i];
                    timeCounter += curK;
                    int s = 0;
                    int failures = 0;

                    FOR(i, curUsableN) used[i] = false;

                    while (s < curUsableN) {
                        //int p = rand() % curUsableN;
                        int p = prob[tt][rand() % pCount];
                        FOR(i, 100) {
                            //if (used[p]) p = rand() % curUsableN; else break;
                            if (used[p]) p = prob[tt][rand() % pCount]; else break;
                        }

                        timeCounter += curK;
                        if (timeCounter >= CHECK_INTERVAL) {
                            timeCounter = 0;
                            if (currentTime() > MAX_TIME) {
                                finish = true;
                                break;
                            }
                        }
                        if (used[p]) break;

                        used[p] = true;
                        if (sub(remaining, usableData[curT] + p * curK)) {
                            selected[s++] = p;
                            failures = 0;
                        } else {
                            if (++failures >= 100) break;
                        }
                    }


                    if (s > 0) {
                        long long int d = sum(remaining);
                        double r = s / (d + 1.0);
                        if (r > maxTotal[tt]) {
                            maxTotal[tt] = r;
                            resultSize[tt] = s;
                            FOR(i, s) result[tt][i] = selected[i];

                        }
                    }
                }
                if (finish) break;
            }
        }
    }



    FOR(tt, t) {
        printf("%d\n", resultSize[tt]);
        if (resultSize[tt] > 0) {
            //int r[MAX_DATA];


            qsort(result[tt], resultSize[tt], sizeof(result[tt][0]), cmp);

            /*FOR(i, k[tt]) r[i] = 0;
            FOR(i, resultSize[tt] - 1) if (result[tt][i] == result[tt][i + 1]) crash();
            FOR(i, resultSize[tt]) {
                FOR(j, k[tt]) r[j] += usableData[tt][result[tt][i] * k[tt] + j];
            }
            FOR(i, k[tt]) if (r[i] > a[tt][i]) {
                printf("Error for result %d at index %d\n", tt, i);
                exit(1);
            } */ //else {printf("%d ", a[tt][i] - r[i]);}



            FOR(i, resultSize[tt]) printf("%d ", indexes[tt][result[tt][i]] + 1);
            puts("");
        }
    }

}

