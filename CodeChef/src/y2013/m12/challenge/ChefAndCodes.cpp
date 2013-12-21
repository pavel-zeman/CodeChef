// Sort the letters by the number of occurrences
// http://www.codechef.com/DEC13/problems/CHODE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <algorithm>



#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_LENGTH 150010
#define LETTERS 26

using namespace std;

char origFrequency[LETTERS + 10];
char line[MAX_LENGTH];

struct CurrFrequency {
    char c;
    int count;

    bool operator<(const CurrFrequency & other) const {
        return count < other.count || (count == other.count && c < other.c);
    }
} currFrequency[LETTERS];

int main(void) {
    gets(line);
    int t = atoi(line);
    FOR(tt, t) {
        gets(origFrequency);
        gets(line);

        FOR(i, LETTERS) currFrequency[i].c = 'a' + i, currFrequency[i].count = 0;

        char *start = line;
        while (*start) {
            if (isalpha(*start)) {
                char c = *start;
                if (isupper(c)) c = tolower(c);
                currFrequency[c - 'a'].count++;
            }
            start++;
        }

        sort(currFrequency, currFrequency + LETTERS);

        start = line;
        while (*start) {
            if (isalpha(*start)) {
                char c = *start;
                if (isupper(c)) c = tolower(c);
                int index = 0;
                while (currFrequency[index].c != c) index++;
                *start = isupper(*start) ? toupper(origFrequency[index]) : origFrequency[index];
            }
            start++;
        }
        printf("%s\n", line);

    }
}
