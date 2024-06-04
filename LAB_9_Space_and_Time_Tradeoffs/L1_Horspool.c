#include <stdio.h>
#include <string.h>

#define MAX 256

void preprocessShiftTable(char *pattern, int patternLength, int shiftTable[MAX]) {
    int i;
    for (i = 0; i < MAX; i++)
        shiftTable[i] = patternLength;
    for (i = 0; i < patternLength - 1; i++)
        shiftTable[pattern[i]] = patternLength - 1 - i;
}

int horspoolStringSearch(char *text, int textLength, char *pattern, int patternLength, int *comparisons) {
    int shiftTable[MAX];
    preprocessShiftTable(pattern, patternLength, shiftTable);
    int i = patternLength - 1;
    while (i < textLength) {
        int k = 0;
        while (k < patternLength && pattern[patternLength - 1 - k] == text[i - k]) {
            k++;
            (*comparisons)++;
        }
        if (k == patternLength)
            return i - patternLength + 1; 
        else
            i += shiftTable[text[i]]; 
    }
    return -1; 
}

int main() {
    char text[] = "xampletextforexample";
    char pattern[] = "example";
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int comparisons = 0;

    int position = horspoolStringSearch(text, textLength, pattern, patternLength, &comparisons);
    if (position != -1)
        printf("Pattern found at position: %d\n", position);
    else
        printf("Pattern not found\n");
    printf("Number of key comparisons: %d\n", comparisons);

    return 0;
}
