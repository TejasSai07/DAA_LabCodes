#include <stdio.h>
#include <stdlib.h>

int min_cost = 150540;
int opcount=0; 

int assignment(int jobs, int person, int **arr, int cost, int *job) {
    if (person == jobs) {
        for (int i = 0; i < jobs; ++i) {
            if (job[i] == 0) {
                cost += arr[person - 1][i];
                min_cost = (min_cost <= cost) ? min_cost : cost;
                return min_cost;
            }
        }
    } else {
        for (int i = 0; i < jobs; ++i) {
            if (job[i] == 0) {
                job[i] = 1;
                cost += arr[person - 1][i];
                assignment(jobs, person + 1, arr, cost, job);
                cost -= arr[person - 1][i];
                job[i] = 0;
            }
        }
    }
    return min_cost;
}

int main() {
    printf("Enter the number of people/jobs:\n");
    int p;
    scanf("%d", &p);

    int **arr = (int **)malloc(sizeof(int *) * p);
    for (int i = 0; i < p; ++i) {
        arr[i] = (int *)malloc(sizeof(int) * p);
    }

    int *job = (int *)calloc(sizeof(int), p);

    printf("Enter weights for each person and job:\n");
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < p; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("Minimum cost = %d\n", assignment(p, 1, arr, 0, job));
    printf("Opcount is : %d\n",opcount);
    for (int i = 0; i < p; ++i) {
        free(arr[i]);
    }
    free(arr);
    free(job);

    return 0;
}
