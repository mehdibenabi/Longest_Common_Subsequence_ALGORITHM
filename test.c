#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// int LCS_recursive(char *X, char *Y, int m, int n, char *lcs) {
//     if (m == 0 || n == 0) {
//         lcs[0] = '\0';
//         return 0;
//     }

//     if (X[m - 1] == Y[n - 1]) {
//         int len = LCS_recursive(X, Y, m - 1, n - 1, lcs);
//         lcs[len] = X[m - 1];
//         lcs[len + 1] = '\0';
//         return len + 1;
//     } else {
//         char *lcsX = (char *)malloc((m + n + 1) * sizeof(char));
//         char *lcsY = (char *)malloc((m + n + 1) * sizeof(char));
//         int exclude_last_X = LCS_recursive(X, Y, m, n - 1, lcsX);
//         int exclude_last_Y = LCS_recursive(X, Y, m - 1, n, lcsY);

//         if (exclude_last_X > exclude_last_Y) {
//             strcpy(lcs, lcsX);
//             free(lcsY);
//             free(lcsX);
//             return exclude_last_X;
//         } else {
//             strcpy(lcs, lcsY);
//             free(lcsY);
//             free(lcsX);
//             return exclude_last_Y;
//         }
//     }
// }



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
            // Character in LCS, add it to result
            lcs_result[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (prev[j] == current[j - 1]) {
            j--;
        } else {
            i--;
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


void generate_random_string(char *str, int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for ( i = 0; i < length; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length] = '\0';
}


int main() {
    int m, i,n;
    srand(time(NULL));

    FILE *fp = fopen("resultats_lcs_test.csv", "w");
    if (!fp) {
        perror("Erreur d'ouverture du fichier CSV");
        return 1;
    }
    fprintf(fp, "Longueur X,Longueur Y,Chaîne X,Chaîne Y,Longueur LCS,LCS (extrait),Temps d'exécution (s),Mémoire utilisée (octets)\n");

    // Starting values for m and n
    m = 10;
    n = 20;

    // Loop to generate random lengths for m and n
    for ( i = 0; i < 5; i++) { // Run 5 tests with different m and n
        char *X = (char *)malloc((m + 1) * sizeof(char));
        char *Y = (char *)malloc((n + 1) * sizeof(char));
        char *lcs = (char *)malloc((m > n ? m + 1 : n + 1) * sizeof(char)); // Ensure lcs has enough space

        // Generate random strings for the current m and n lengths
        generate_random_string(X, m);
        generate_random_string(Y, n);

        // Measure the execution time for finding the LCS
        clock_t start = clock();
        int lcs_length = lcs_optimized(X, Y);
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Calculate the memory used
        size_t memory_used = sizeof(char) * (m + n + (m > n ? m : n));

        // Print results for each test, including X and Y
        printf("Test pour longueurs m = %d, n = %d:\n", m, n);
        printf("Chaîne X: %s\n", X);
        printf("Chaîne Y: %s\n", Y);
        printf("Longueur LCS: %d\n", lcs_length);
        printf("LCS (extrait): %.50s\n", lcs);
        printf("Temps d'exécution: %f secondes\n", cpu_time_used);
        printf("Mémoire utilisée: %zu octets\n\n", memory_used);

        // Save results to CSV, including X and Y
        fprintf(fp, "%d,%d,%s,%s,%d,%.50s,%f,%zu\n", m, n, X, Y, lcs_length, lcs, cpu_time_used, memory_used);
        fflush(fp);

        // Free memory
        free(X);
        free(Y);
        free(lcs);

        // Increment lengths of m and n for the next test
        m += 20;
        n += 30;
    }

    fclose(fp);
    printf("Résultats enregistrés dans resultats_lcs_test.csv\n");
    return 0;
}