#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

// Fonction pour calculer la longueur de la LCS
int lcs_dp(char *A, char *B, int m, int n, char *lcs_str) {
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    int length = dp[m][n];
    lcs_str[length] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            lcs_str[length - 1] = A[i - 1];
            i--;
            j--;
            length--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return dp[m][n];
}

// Fonction pour obtenir l'utilisation de la mémoire
void get_memory_usage(long *memory_usage) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    *memory_usage = usage.ru_maxrss;  // En kilobytes
}

int main() {
    int N;
    printf("Entrez le nombre de tests à effectuer (ne dépassant pas 29929) : ");
    int result = scanf("%d", &N);

    if (result != 1) {
        printf("Erreur de saisie. Veuillez entrer un nombre valide.\n");
        return 1;
    }

    if (N > 29929) {
        printf("Le nombre de tests est trop élevé, je vais ajuster à 29929\n");
        N = 29929;
    } else if (N < 1) {
        printf("Le nombre de tests doit être au moins 1.\n");
        return 1;
    }

    char *strings[] =  {
        "Algorithm","API", "Array", "Application", "Binary", "Bit", "Byte", "Buffer", "Cache", 
        "Cloud", "Compiler", "CSS", "Database", "Debugging", "Deployment", "Docker", "Encryption", 
        "Endpoint", "Framework", "Git", "GitHub", "GUI", "Hash", "HTML", "HTTP", "HTTPS", "IP Address", 
        "Java", "JavaScript", "JSON", "Kernel", "LAN", "Library", "Linux", "Machine Learning", "Malware", 
        "Node.js", "Object-Oriented", "PHP", "Python", "Query", "React", "Repository", "REST", "SaaS", 
        "Security", "Server", "SQL", "SSH", "SSL", "Stateless", "Syntax", "TCP", "URL", "User Interface", 
        "Virtual Machine", "Version Control", "WebSocket", "XML", "DNS", "Firewall", "Hosting", "Load Balancer", 
        "Microservices", "Node", "Object", "OAuth", "Package", "Patch", "Proxy", "Query Language", "Recursion", 
        "Router", "Sandbox", "Shell", "Software", "SQL Injection", "SVN", "System Architecture", "Token", "UI/UX", 
        "VPN", "Webhook", "Wireless", "XSS", "HTTP/2", "Cross-Platform", "Dockerfile", "GitLab", "IDE", "MVC", 
        "SDK", "DNS Server", "RAM", "API Gateway", "Authentication", "Cloud Storage", "Data Mining", "Web Scraping",
        "abc", "xyz", "qwerty", "asdf", "zxcvbn", "aaa", "bbb", "ccc", "123", "abc123", "password", "letmein",
        "iloveyou", "1234", "welcome", "admin", "root", "guest", "test", "qwertyuiop", "12345", "letmein1",
        "hello123", "dragon", "sunshine", "princess", "football", "qwerty12", "monkey", "trustno1", "superman",
        "qwertz", "abc12345", "123123", "qazwsx", "1qaz2wsx", "qwerty1", "admin123", "123qwe", "123abc", "qwert",
        "asdf1234", "password1", "letmein2", "1234abcd", "1password", "asdfghjkl", "password123", "letmein123",
        "123qwerty", "sunshine123", "123abc123", "qwerty789", "password1q", "open1234", "Tg1@p5$6", "9aVx%z4G",
        "n2Fd!mW8", "Vn8@Km2$k", "Np9^Xo5#t", "gK4!p3Ae", "Ff5@y8Tb", "R$U7k9tL", "8Zm2@W3a", "X6jFx9&k",
        "Ab2#P6zZ", "T8p#G5@d", "Nc$1Tx9J", "wG8%qY7Z", "5N9#l@8J", "7Rp$yF3z", "fQ6v#A9u", "2Rg@tP5V", "Lw8p@W1s"
    };

    int total_strings = sizeof(strings) / sizeof(strings[0]);
    char lcs_str[100];
    
    // Ouvrir le fichier CSV pour écrire les données de performance
    FILE *file = fopen("performance_data.csv", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Écrire l'entête du fichier CSV
    fprintf(file, "Taille_L1,Taille_L2,Temps_Execution(ms),Memoire_Utilisee(KB)\n");

    // Boucles pour générer toutes les paires possibles
    int pair_count = 0;
    for (int i = 0; i < total_strings && pair_count < N; i++) {
        for (int j = i; j < total_strings && pair_count < N; j++) {
            char *A = strings[i];
            char *B = strings[j];
            int m = strlen(A);
            int n = strlen(B);

            // Mesurer le temps d'exécution
            clock_t start = clock();

            // Mesurer l'utilisation de la mémoire
            long before_memory;
            get_memory_usage(&before_memory);

            int length = lcs_dp(A, B, m, n, lcs_str);

            clock_t end = clock();
            double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

            long after_memory;
            get_memory_usage(&after_memory);

            long memory_usage = after_memory - before_memory;

            // Affichage des résultats
            printf("Test %d:\n", pair_count + 1);
            printf("Chaîne 1 : %s\n", A);
            printf("Chaîne 2 : %s\n", B);
            printf("Longueur de la LCS : %d\n", length);
            if (length == 0) {
                printf("Il n'existe pas de LCS\n");
            } else {
                printf("La LCS est : %s\n", lcs_str);
            }
            printf("Temps d'exécution: %f secondes\n", cpu_time_used);
            printf("Mémoire utilisée: %ld KB\n\n", memory_usage);

            // Écrire les données dans le fichier CSV
            fprintf(file, "%d,%d,%f,%ld\n", m, n, cpu_time_used * 1000, memory_usage);

            pair_count++;
        }
    }

    fclose(file);

    return 0;
}
