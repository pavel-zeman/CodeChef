//
// http://www.codechef.com/NOV14/problems/SPELL
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define MAX_SIZE 10000200

using namespace std;

char data[MAX_SIZE];

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int main(void) {
    gets(data);
    int d = atoi(data);
    FOR(i, d) gets(data);
    gets(data);
    puts(data);
}
