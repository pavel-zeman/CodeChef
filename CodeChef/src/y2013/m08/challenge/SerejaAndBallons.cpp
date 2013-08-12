// Interval tree with each interval split into left and right part
// http://www.codechef.com/AUG13/problems/SEABAL
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <list>
#include <vector>
#include <algorithm>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MAX_M 100010
#define MAX_COUNT 1000000000

using namespace std;


int n, m;
int a[MAX_N];

struct Interval {
    int l;
    int r;
    int leftCount;
    int rightCount;
    bool inLeftList;
    bool inRightList;
} intervals[MAX_M];

struct TreeItem {
    int value;
    struct TreeItem *left;
    struct TreeItem *right;
    vector<int> leftPoints;
    vector<int> rightPoints;
} root;


char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}


bool compareLeft(int a, int b) {
    return intervals[a].l < intervals[b].l;
}

bool compareRight(int a, int b) {
    return intervals[a].r > intervals[b].r;
}


void createNode(struct TreeItem *root, vector<int> &li) {
    int minv = MAX_COUNT;
    int maxv = 0;
    for(vector<int>::iterator it = li.begin(); it != li.end(); it++) {
        minv = min(minv, intervals[*it].l);
        maxv = max(maxv, intervals[*it].r);
    }
    int middle = (minv + maxv) / 2;
    //printf("Creating node for %d\n", middle);
    root->value = middle;


    vector<int> currentItems;
    vector<int> left;
    vector<int> right;
    currentItems.reserve(li.size());
    left.reserve(li.size());
    right.reserve(li.size());

    for(vector<int>::iterator it = li.begin(); it != li.end(); it++) {
        if (intervals[*it].r < middle) left.push_back(*it);
        else if (intervals[*it].l > middle) right.push_back(*it);
        else currentItems.push_back(*it);
    }

    if (left.size() > 0) {
        struct TreeItem *leftItem = new TreeItem();
        leftItem->left = NULL;
        leftItem->right = NULL;
        root->left = leftItem;
        createNode(leftItem, left);
    }
    if (right.size() > 0) {
        struct TreeItem *rightItem = new TreeItem();
        rightItem->left = NULL;
        rightItem->right = NULL;
        root->right = rightItem;
        createNode(rightItem, right);
    }
    if (currentItems.size() > 0) {
        root->leftPoints.reserve(currentItems.size());
        root->rightPoints.reserve(currentItems.size());

        sort(currentItems.begin(), currentItems.end(), compareLeft);
        for(vector<int>::iterator it = currentItems.begin();it != currentItems.end();it++) {
            root->leftPoints.push_back(*it);
            intervals[*it].inLeftList = true;
        }
        int last = middle + 1;
        for(int i=currentItems.size() - 1;i>=0;i--) {
            intervals[currentItems[i]].leftCount = last - intervals[currentItems[i]].l;

            last = intervals[currentItems[i]].l;
        }

        sort(currentItems.begin(), currentItems.end(), compareRight);
        for(vector<int>::iterator it = currentItems.begin();it != currentItems.end() && intervals[*it].r > middle;it++) {
            root->rightPoints.push_back(*it);
            intervals[*it].inRightList = true;
        }
        last = middle;
        for(int i=currentItems.size() - 1;i>=0;i--) {
            intervals[currentItems[i]].rightCount = intervals[currentItems[i]].r - last;
            last = intervals[currentItems[i]].r;
        }

    }
}


void createTree(void) {
    vector<int> li(m);
    FOR(i, m) li[i] = i;

    root.left = NULL;
    root.right = NULL;
    createNode(&root, li);
}

int findLessOrEqual(vector<int> &data, int value) {
    int l = 0;
    int r = data.size() - 1;
    while (r > l) {
        int middle = (r + l) >> 1;
        if (intervals[data[middle]].l <= value) l = middle + 1; else r = middle - 1;
    }
    if (l >= (int)data.size()) l--;
    if (intervals[data[l]].l > value) l--;
    return l;
}

int findGreaterOrEqual(vector<int> &data, int value) {
    int l = 0;
    int r = data.size() - 1;
    while (r > l) {
        int middle = (r + l) >> 1;
        if (intervals[data[middle]].r >= value) l = middle + 1; else r = middle - 1;
    }
    if (l >= (int)data.size()) l--;
    if (intervals[data[l]].r < value) l--;
    return l;
}


int decrement(struct TreeItem *root, int value) {
    int result = 0;
    if (value == root->value) {
        if (!root->leftPoints.empty()) {
            int i = root->leftPoints.size() - 1;
            intervals[root->leftPoints[i]].leftCount--;
            while (i >= 0 && intervals[root->leftPoints[i]].leftCount == 0) {
                if (!intervals[root->leftPoints[i]].inRightList) { result++;}
                intervals[root->leftPoints[i]].inLeftList = false;
                root->leftPoints.pop_back();
                i--;
            }
        }
    } else {
        if (value < root->value) {
            if (!root->leftPoints.empty() && value >= intervals[root->leftPoints.front()].l) {
                int i = findLessOrEqual(root->leftPoints, value);
                intervals[root->leftPoints[i]].leftCount--;
                if (i == (int)root->leftPoints.size() - 1) {
                    while (i >= 0 && intervals[root->leftPoints[i]].leftCount == 0) {
                        if (!intervals[root->leftPoints[i]].inRightList) result++;
                        intervals[root->leftPoints[i]].inLeftList = false;
                        root->leftPoints.pop_back();
                        i--;
                    }
                }
            }
            if (root->left != NULL) result += decrement(root->left, value);
        } else {
            if (!root->rightPoints.empty() && value <= intervals[root->rightPoints.front()].r) {
                int i = findGreaterOrEqual(root->rightPoints, value);
                intervals[root->rightPoints[i]].rightCount--;
                if (i == (int)root->rightPoints.size() - 1) {
                    while (i >= 0 && intervals[root->rightPoints[i]].rightCount == 0) {
                        if (!intervals[root->rightPoints[i]].inLeftList) result++;
                        intervals[root->rightPoints[i]].inRightList = false;
                        root->rightPoints.pop_back();
                        i--;
                    }
                }
            }
            if (root->right != NULL) result += decrement(root->right, value);
        }
    }
    return result;
}

int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, n) a[i] = getInt();
    FOR(i, m) intervals[i].l = getInt() - 1, intervals[i].r = getInt() - 1;

    createTree();

    int k = getInt();
    int ans = 0;

    FOR(i, k) {
        int x = getInt();
        int y = x + ans - 1;
        if (--a[y] == 0)
            ans += decrement(&root, y);
        printf("%d\n", ans);
    }
}

