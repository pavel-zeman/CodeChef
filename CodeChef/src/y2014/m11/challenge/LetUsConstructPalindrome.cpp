// Go character by character from both sides and if there is a mismatch, try to remove the left or right one. If the original string is a palindrome, try to remove all the characters one by one.
// http://www.codechef.com/NOV14/problems/PRPALN
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define MAX_N 100010

using namespace std;

char data[MAX_N];

int start, end;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

bool checkPalindrome() {
    while (start < end) {
        if (data[start] != data[end]) return false;
        start++;
        end--;
    }
    return true;
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%s", data);
        int length = strlen(data);
        start = 0;
        end = length - 1;

        bool ok = false;

        if (!checkPalindrome()) {
            int start1 = start, end1 = end;
            start++;
            if (checkPalindrome()) ok = true; else {
                start = start1; end = end1;
                end--;
                ok = checkPalindrome();
            }
        } else {
            int i = 0;
            while (i <= length - 1 - i) {
                start = i;
                end = length - 1 - i - 1;
                if (checkPalindrome()) {
                    ok = true;
                    break;
                }
                start = i + 1;
                end = length - 1 - i;
                if (checkPalindrome) {
                    ok = true;
                    break;
                }
                i++;
            }
        }
        printf("%s\n", ok ? "YES" : "NO");
    }
}
