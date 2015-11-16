// Start with the nodes with the highest multiplier, use the most valuable letters
// https://www.codechef.com/NOV15/problems/SCRABBLE
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

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

void getString(char *dst) {
    while (!((ccc >= 'A' && ccc <= 'Z') || ccc == '_' || ccc == '.')) ccc = getc_unlocked(stdin);
    while ((ccc >= 'A' && ccc <= 'Z') || ccc == '_' || ccc == '.') {
        *dst++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *dst = 0;
}


template <class type> void print(type a, bool newLine = true) {
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
    if (newLine) putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

void print(char c) {
    putc_unlocked(c, stdout);
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

#define LETTERS 26

struct Node {
    bool used;
    bool final;
    int next[LETTERS];
} nodes[590000];

int totalNodes = 1;

int addNode() {
    nodes[totalNodes].used = false;
    nodes[totalNodes].final = false;
    return totalNodes++;
}

void addWord(char *word) {
    int node = 0;
    while (*word) {
        if (nodes[node].next[*word - 'A'] == 0) {
            nodes[node].next[*word - 'A'] = addNode();
        }
        node = nodes[node].next[*word - 'A'];
        word++;
    }
    nodes[node].final = true;
}

#define MAX_N 100010
#define EMPTY '.'
#define BLANK_TILE '_'

int n, m;
char sortedLetters[] = "QZJXKFHVWYBCMPDGEAIONRTLSU";
char multiplier[MAX_N];
char letter[MAX_N];
vector<int> neighbor[MAX_N];
char tiles[40];
bool tileUsed[40];
int tilePos[40];
int totalTiles;
                //A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
int priority[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,9,1,1,1,1,4,4,8,4,9};

int wordNode[100];

int checkStep;
bool checkFail;


struct SortedNode {
    int nodeNum;

    bool operator<(const SortedNode &other) const {
        return multiplier[this->nodeNum] > multiplier[other.nodeNum];
    }

} sortedNode[MAX_N];

bool check(int node, int trieNode, int lettersUsed, int depth);

bool next(int node, int trieNode, int lettersUsed, int depth) {
    trieNode = nodes[trieNode].next[letter[node] - 'A'];
    if (trieNode == 0) return false;
    if (lettersUsed > 0 && nodes[trieNode].final && !nodes[trieNode].used ) {
        print(lettersUsed);
        FOR(i, totalTiles) {
            if (tileUsed[i]) {
                print(tilePos[i] + 1, false);
                print(' ');
                print(tiles[i]);
                print('\n');
            }
        }
        print(depth);
        FOR(i, depth) {
            print(wordNode[i] + 1, false);
            print(' ');
        }
        print('\n');
        FOR(i, depth) print(letter[wordNode[i]]);
        print('\n');
        nodes[trieNode].used = true;

        return true;
    } else {
        for(vector<int>::iterator it = neighbor[node].begin(); it != neighbor[node].end(); it++) {
            bool res = check(*it, trieNode, lettersUsed, depth);
            if (res) return true;
            if (checkFail) break;
        }
        return false;
    }

}

bool check(int node, int trieNode, int lettersUsed, int depth) {
    checkStep++;
    if (checkStep >= 1000000) {
        checkFail = true;
        return false;
    }
    wordNode[depth] = node;
    if (letter[node] >= 'A' && letter[node] <= 'Z') {
        return next(node, trieNode, lettersUsed, depth + 1);
    } else if (letter[node] == EMPTY) {
        FOR(i, totalTiles)
            if (!tileUsed[i]) {
                tileUsed[i] = true;
                tilePos[i] = node;
                if (tiles[i] == BLANK_TILE) {
                    FOR(i, LETTERS) {
                        letter[node] = sortedLetters[i];
                        bool res = next(node, trieNode, lettersUsed + 1, depth + 1);
                        if (res) return true;
                        if (checkFail) break;
                    }
                } else {
                    letter[node] = tiles[i];
                    bool res = next(node, trieNode, lettersUsed + 1, depth + 1);
                    if (res) return true;
                }
                letter[node] = EMPTY;
                tileUsed[i] = false;
            }
    } else if (letter[node] == BLANK_TILE) {
        FOR(i, LETTERS) {
            letter[node] = sortedLetters[i];
            bool res = next(node, trieNode, lettersUsed, depth + 1);
            if (res) return true;
            if (checkFail) break;
        }
        letter[node] = BLANK_TILE;
    }
    return false;
}

int getPriority(char c) {
    if (c == '_') return 10; else return priority[c - 'A'];
}

int main(void) {
    clock_t startTime = clock();
    nodes[0].final = false;
    FOR(i, LETTERS) nodes[0].next[i] = 0;

    int d = getInt();
    FOR(i, d) {
        char word[100];
        getString(word);
        addWord(word);
    }
    n = getInt();
    m = getInt();
    FOR(i, n) multiplier[i] = getInt();
    FOR(i, n) sortedNode[i].nodeNum = i;
    sort(sortedNode, sortedNode + n);
    getString(letter);
    FOR(i, m) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        neighbor[a].push_back(b);
        neighbor[b].push_back(a);
    }
    srand(time(NULL));
    int step = 0;
    while (true) {
        getString(tiles);
        totalTiles = strlen(tiles);
        FOR(i, totalTiles)
            FORE(j, 1, totalTiles - i)
                if (getPriority(tiles[j - 1]) < getPriority(tiles[j]))
                    swap(tiles[j - 1], tiles[j]);
        FOR(i, totalTiles) tileUsed[i] = false;
        bool ok = false;
        FOR(i, n) {
            checkStep = 0;
            checkFail = false;
            if (check(sortedNode[(i + step) % n].nodeNum, 0, 0, 0)) {
                ok = true;
                step = (i + step) % n;
                break;
            }
            if (clock() - startTime > 9 * CLOCKS_PER_SEC) break;
        }
        if (!ok) break;
        fflush(stdout);
    }
    print(-1);
}

