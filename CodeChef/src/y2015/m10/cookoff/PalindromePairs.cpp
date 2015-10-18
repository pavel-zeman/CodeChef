// Create trie from the reversed strings, then check each word character by character while traversing the trie and checking, whether current suffix is a palindrome (using modification of Manacher's algorithm)
// https://www.codechef.com/COOK63/problems/PP
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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

int getString(char *data) {
    char *start = data;
    while (!(ccc >= 'a' && ccc <= 'z')) ccc = getc_unlocked(stdin);
    while (ccc >= 'a' && ccc <= 'z') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
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


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_N 1000010
#define MAX_CHILDREN 26
#define MAX_NODES 1000010
#define INVALID -1
int start[MAX_N];
char data[MAX_N];

int P[MAX_N * 2];
char T[MAX_N * 2];
bool palindromeStart[MAX_N], palindromeEnd[MAX_N];

struct Node {
    int count;
    int palindromeCount;
    int children[MAX_CHILDREN];
} nodes[MAX_NODES];

int totalNodes;

void resetNode(int node) {
    nodes[totalNodes].count = 0;
    nodes[totalNodes].palindromeCount = 0;
    FOR(i, MAX_CHILDREN) nodes[node].children[i] = INVALID;
}

void addNodes(int start, int end) {
    int node = 0;
    for(int i=end;i>=start;i--) {
        int nextNode = nodes[node].children[data[i] - 'a'];
        if (nextNode == INVALID) {
            resetNode(totalNodes);
            nodes[node].children[data[i] - 'a'] = totalNodes;
            nextNode = totalNodes;
            totalNodes++;
        }
        if (palindromeStart[i]) nodes[node].palindromeCount++;
        node = nextNode;
    }
    nodes[node].count++;
}

int preProcess(int start, int end) {
  int n = end - start;
  int resultPos = 0;
  T[resultPos++] = '^';
  FORE(i, start, end) {
    T[resultPos++] = '#';
    T[resultPos++] = data[i];
  }
  T[resultPos++] = '#';
  T[resultPos++] = '$';
  return resultPos;
}

void allPalindromes(int start, int end) {
  int n = preProcess(start, end);
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)

    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;

    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;

    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }

  // Find the maximum element in P.
  int maxLen = 0;
  int centerIndex = 0;
  int origLength = end - start;
  //FORE(i, 1, n - 1) printf("%d ", P[i]);
  //printf("\n");
  for (int i = 1; i < n-1; i++) {
    int ps = (i - 1 - P[i]) >> 1;
    int pe = ps + P[i];
    //printf("%d %d\n", ps, pe);
    if (P[i] > 1) {
        if (pe == end - start) palindromeEnd[start + ps] = true;
        if (ps == 0) palindromeStart[start + pe - 1] = true;
    }
  }
  palindromeStart[start] = true;
  palindromeEnd[end - 1] = true;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int pos = 0;
        long long int total = 0;
        totalNodes = 1;
        resetNode(0);

        FOR(i, n) {
            start[i] = pos;
            pos += getString(data + pos);
            FORE(j, start[i], pos) palindromeStart[j] = palindromeEnd[j] = false;
            allPalindromes(start[i], pos);
            addNodes(start[i], pos - 1);
        }
        start[n] = pos;
        /*FOR(i, n) {
            FORE(j, start[i], start[i + 1]) printf("%d ", palindromeStart[j]);
            printf("\n");
            FORE(j, start[i], start[i + 1]) printf("%d ", palindromeEnd[j]);
            printf("\n");
        }*/

        FOR(i, n) {
            int node = 0;
            FORE(j, start[i], start[i + 1]) {
                int nextNode = nodes[node].children[data[j] - 'a'];
                node = nextNode;
                if (node == INVALID) break;
                if (nodes[node].count > 0) {
                    if (palindromeEnd[j + 1] || j + 1 == start[i + 1]) total += nodes[node].count;
                }
            }
            if (node != INVALID) total += nodes[node].palindromeCount;
            if (palindromeEnd[start[i]]) total--;
        }
        print(total);
    }
}

