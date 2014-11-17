// We only need to calculate the K-th power of the input matrix, which can be done fast using sqaureing. We also have to handle duplicate words in the list.
// http://www.codechef.com/NOV14/problems/CHEFWORD
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define LETTERS 26
#define MAX_S 10
#define MAX_WORDS (LETTERS*LETTERS*LETTERS)

using namespace std;


#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

void multiply(double m1[LETTERS][LETTERS], double m2[LETTERS][LETTERS]) {
    double temp[LETTERS][LETTERS];
    FOR(i, LETTERS) FOR(j, LETTERS) {
        double sum = 0;
        FOR(k, LETTERS) sum += m1[i][k] * m2[k][j];
        temp[i][j] = sum;
    }
    FOR(i, LETTERS) FOR(j, LETTERS) m1[i][j] = temp[i][j];
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        int n, k;
        char s[MAX_S];
        scanf("%d %d %s", &n, &k, s);

        int length = strlen(s);

        double matrix[LETTERS][LETTERS];
        double resultMatrix[LETTERS][LETTERS];
        FOR(i, LETTERS) FOR(j, LETTERS) scanf("%lf", &matrix[i][j]);
        FOR(i, LETTERS) FOR(j, LETTERS) resultMatrix[i][j] = i == j ? 1 : 0; // create unit matrix

        // calculate k-th power of matrix
        while (k > 0) {
            if ((k & 1) == 1) multiply(resultMatrix, matrix);
            multiply(matrix, matrix);
            k >>= 1;
        }

        bool used[MAX_WORDS];
        FOR(i, MAX_WORDS) used[i] = false;

        double result = 0;
        FOR(i, n) {
            char s2[MAX_S];
            scanf("%s", s2);
            if ((int)strlen(s2) == length) {
                // check, if the word was already seen
                int wordIndex = 0;
                char *s3 = s2;
                while (*s3) wordIndex = wordIndex * LETTERS + (*s3++ - 'a');
                if (!used[wordIndex]) {
                    used[wordIndex] = true;
                    // calculate result for a single word character by character
                    double temp = 1;
                    FOR(j, length) temp *= resultMatrix[s[j] - 'a'][s2[j] - 'a'];
                    result += temp;
                }
            }
        }
        printf("%.10lf\n", result);
    }
}
