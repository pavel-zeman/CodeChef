#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXBITS 170
#define MAXN 200
#define MAXLENGTH 20

//#define TEST

char passwords[MAXN][MAXLENGTH];
bool honeyPot[MAXN];
int length[MAXN];


void generatePassword(char *dest) {
    int length = (rand() % 5) + 8;
    FOR(i, length) dest[i] = 'a' + (rand() % 26);
    dest[length] = 0;
}

void printPasswords(int n) {
    FOR(i, n) printf("%s\n", passwords[i]);
    fflush(stdout);
}

bool contains(int *data, int value, int count) {
    FOR(i, count) if (data[i] == value) return true;
    return false;
}



char testPasswords[MAXN][MAXLENGTH];
bool testHoneyPot[MAXN];

void generateTestData(int n, int h) {
    FOR(i, n) {
        generatePassword(testPasswords[i]);
        testHoneyPot[i] = (rand() % 3) == 0;
    }
}

void calcHash(char * data, int *result) {
    FOR(i, 20) result[i] = 0;
    int pos = 0;
    while (*data != 0) {
        int start = (*data + pos) % 20;
        FOR(i, *data) {
            result[start] ^= *data ^ i;
            start = (start + 1) % 20;
        }
        pos++;
        data++;
    }
}

int compareHashes(int *h1, int *h2) {
    int total = 0;
    FOR(i, 20) {
        int v1 = h1[i];
        int v2 = h2[i];
        FOR(j, 8) {
            if ((v1 & 1) == (v2 & 1)) total++;
            v1 >>= 1;
            v2 >>= 1;
        }
    }
    return total;
}

int calcBitMatch(char *p1, char *p2) {
    int h1[20];
    int h2[20];
    calcHash(p1, h1);
    calcHash(p2, h2);
    int total = compareHashes(h1, h2);
    return total * total;
}


void printTestResult(int n) {
#ifdef TEST
    int total2 = 0;
    FOR(i, n) {
        if (testHoneyPot[i] && honeyPot[i]) {
            // nothing here
            //printf("%d honeypots\n", i);
        } else if (testHoneyPot[i] != honeyPot[i]) {
            printf("%d honeypot error %d %d\n", i, honeyPot[i], testHoneyPot[i]);
        } else {
            int h1[20];
            int h2[20];
            calcHash(passwords[i], h1);
            calcHash(testPasswords[i], h2);
            int total = compareHashes(h1, h2);
            total2 += total * total;
            printf("%d not honeypots %d %d\n", i, length[i], total);
        }
    }
    printf("Total: %d\n", total2);
#endif
}

#ifdef TEST
int calcScore(int n) {
    int total = 0;
    FOR(i, n) {
        if (!testHoneyPot[i]) {
            total += calcBitMatch(passwords[i], testPasswords[i]);
        }
    }
    return total;
}
#endif

#ifndef TEST
int calcScore(int n) {
    int result;
    scanf("%d", &result);
    return result;
}
#endif

int sqr(int a) {
    return a * a;
}

int main(void) {
    int t, n, h, score;
    char originalPassword[MAXLENGTH];

    srand(time(NULL));

    scanf("%d%d%d", &t, &n, &h);
    FOR(i, n) generatePassword(passwords[i]);
    generateTestData(n, h);

    printPasswords(n);
    score = calcScore(n);
    t--;

    FOR(i, n) {
        int possibilityCount = 0;
        int possibilities[MAXLENGTH];
        while (true) {
            strcpy(originalPassword, passwords[i]);

            generatePassword(passwords[i]);
            int newScore;
            printPasswords(n);
            newScore = calcScore(n);
            t--;

            int diff = abs(newScore - score);
            if (diff == 0) {
                honeyPot[i] = true;
                break;
            } else {
                honeyPot[i] = false;
                int newPossibilities[MAXLENGTH];
                int newPossibilityCount = 0;
                FOR(k, MAXBITS) FORE(l, k + 1, MAXBITS) {
                    // we don't care, if the number of bits is very high or very low, because its highly unprobable
                    if (l * l - k * k == diff && l >= 50 && l <= 110 && k >= 50 && k <= 110) {
                        if (possibilityCount == 0 || (newScore > score && contains(possibilities, k, possibilityCount)) || (newScore < score && contains(possibilities, l, possibilityCount))) {
                            newPossibilities[newPossibilityCount++] = l;
                        }
                    }
                }
                if (newScore < score) {
                    strcpy(passwords[i], originalPassword);
                } else {
                    score = newScore;
                }
                if (newPossibilityCount == 1) {
                    length[i] = newPossibilities[0];
                    break;
                } else if (newPossibilityCount == 0) {
                    char *a = NULL;
                    *a = 0;
                } else {
                    possibilityCount = newPossibilityCount;
                    memcpy(possibilities, newPossibilities, sizeof(int) * possibilityCount);
                }
            }
        }
        //("Found length at pos %d, remaining %d\n", i, t);

    }
    printTestResult(n);
    while (t-- > 0) {
        int minPos = 0;
        int minValue = MAXBITS;
        FOR(i, n) if (!honeyPot[i] && length[i] < minValue) {
            minValue = length[i];
            minPos = i;
        }
        strcpy(originalPassword, passwords[minPos]);
        //printf("Generating at position %d\n", minPos);
        generatePassword(passwords[minPos]);
        printPasswords(n);
        int newScore = calcScore(n);
        if (newScore > score) {
            FOR(i, MAXBITS) if (sqr(length[minPos] + i) - sqr(length[minPos]) == newScore - score) {
                length[minPos] += i;
                score = newScore;
                break;
            }
        } else {
            strcpy(passwords[minPos], originalPassword);
        }
    }
    printTestResult(n);
}
