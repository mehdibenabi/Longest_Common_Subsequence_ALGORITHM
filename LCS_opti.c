#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Optimized DP solution that returns both the LCS length and the LCS string
void lcs_optimized(char *X, char *Y, char *lcs_result) {
    int m = strlen(X);
    int n = strlen(Y);
    int prev[n + 1], current[n + 1];

    // Initialize previous row

    
    memset(prev, 0, sizeof(prev));

    // Build the LCS length table
    for (int i = 1; i <= m; i++) {
        memset(current, 0, sizeof(current));
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                current[j] = prev[j - 1] + 1;
            } else {
                current[j] = (prev[j] > current[j - 1]) ? prev[j] : current[j - 1];
            }
        }
        memcpy(prev, current, sizeof(current));  // Copy current row to previous
    }

    // LCS length is stored in prev[n]
    int lcs_length = prev[n];

    // Build the LCS string by tracing back
    int i = m, j = n;
    int index = lcs_length;
    lcs_result[index] = '\0';  // Null-terminate the LCS string

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_result[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (prev[j] >= current[j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Print the results
    printf("Length of LCS: %d\n", lcs_length);
    printf("LCS: %s\n", lcs_result);
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int max_length = (strlen(X) > strlen(Y) ? strlen(X) : strlen(Y)) + 1;
    char lcs_result[max_length];

    lcs_optimized(X, Y, lcs_result);

    return 0;
}
