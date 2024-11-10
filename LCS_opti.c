#include <stdio.h>
#include <string.h>


int lcs_optimized(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int prev[n + 1], current[n + 1];

    memset(prev, 0, sizeof(prev));

    for (int i = 1; i <= m; i++) {
        memset(current, 0, sizeof(current));
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                current[j] = prev[j - 1] + 1;
            } else {
                current[j] = (prev[j] > current[j - 1]) ? prev[j] : current[j - 1];
            }
        }
        memcpy(prev, current, sizeof(current));  
    }

    return prev[n];
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    double start,fin,temps_cpu,resultat; ;
    
    start = clock();
    resultat=lcs_optimized(X, Y);
    fin = clock();

    printf("Length of LCS (Space-Optimized DP): %d\n", resultat);
    printf("Time: %f\n", (fin-start)/CLOCKS_PER_SEC);
    return 0;
}
