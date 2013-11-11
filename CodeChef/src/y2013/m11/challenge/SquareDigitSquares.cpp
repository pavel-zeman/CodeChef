// Get all the numbers (there is only a couple of them) and check them one by one (we could also calculate the numbers on the fly, but this way the running time would be wors)
// http://www.codechef.com/NOV13/problems/SDSQUARE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_V 100001

int perfectNumbers[] = {
    1, 2, 3, 7, 10, 12, 20, 21, 30, 38, 70, 97, 100, 102, 107, 120, 138, 200, 201, 210, 212, 300, 380, 648, 700, 701, 951, 970, 997,
    1000, 1002, 1007, 1020, 1049, 1070, 1200, 1380, 1393, 2000, 2001, 2010, 2100, 2120, 3000, 3148, 3153, 3451, 3743, 3747, 3800, 4462,
    6357, 6480, 7000, 7001, 7010, 7071, 9510, 9700, 9701, 9970, 9997, 10000, 10002, 10007, 10020, 10070, 10097, 10200, 10243, 10490, 10538,
    10679, 10700, 12000, 13800, 13930, 20000, 20001, 20010, 20100, 20102, 20247, 20347, 20348, 21000, 21200, 22138, 30000, 31480, 31488,
    31530, 34510, 37430, 37470, 37538, 38000, 38071, 38602, 44620, 63357, 63403, 63570, 64800, 70000, 70001, 70010, 70100, 70107, 70299,
    70710, 95100, 97000, 97001, 97010, 99501, 99700, 99970, 99997, 100000, 100001};
long long int squares[sizeof(perfectNumbers) / sizeof(perfectNumbers[0])];

char c = 0;
long long int getInt() {
    long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

int main(void) {
    FOR(i, (int)(sizeof(perfectNumbers) / sizeof(perfectNumbers[0]))) squares[i] = ((long long int)perfectNumbers[i]) * perfectNumbers[i];
    int t = getInt();
    FOR(tt, t) {
        long long int a = getInt(), b = getInt();
        int i = 0;
        while (squares[i] < a) i++;
        int count = 0;
        while (squares[i] <= b) i++, count++;

        printf("%d\n", count);
    }
}
