#include <stdio.h>

int opcount = 0;


int isSubsetSum(int set[], int n, int sum) {
    opcount++;
    if (sum == 0)
        return 1;
    if (n == 0 && sum != 0)
        return 0;

    return isSubsetSum(set, n - 1, sum) || isSubsetSum(set, n - 1, sum - set[n - 1]);
}

int findPartition(int set[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += set[i];

    if (sum % 2 != 0)
        return 0;

    return isSubsetSum(set, n, sum / 2);
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int set[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &set[i]);

    printf("Opcount is : %d",opcount);

    if (findPartition(set, n))
        printf("The set can be partitioned into two subsets of equal sum.\n");
    else
        printf("The set cannot be partitioned into two subsets of equal sum.\n");

    return 0;
}
