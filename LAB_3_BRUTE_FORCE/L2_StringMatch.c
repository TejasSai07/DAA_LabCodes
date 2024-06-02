#include <stdio.h>
#include <string.h>

int opcount = 0;

int bruteForceStringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            opcount++;
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m)
            return i;
    }
    return -1; 
}

int main() {
    char text[100], pattern[50];

    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    int result = bruteForceStringMatch(text, pattern);

    printf("Opcount is : %d\n",opcount);

    if (result != -1)
        printf("Pattern found at index %d\n", result);
    else
        printf("Pattern not found\n");

    return 0;
}
