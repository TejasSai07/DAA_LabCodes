#include <stdio.h>
#include <stdlib.h>
typedef struct edge *e;
struct edge
{
    int d;
    e link;
};
e create(int val)
{
    e ob = (e)malloc(sizeof(struct edge));
    ob->d = val;
    ob->link = NULL;
    return ob;
}
e *adjacencyList(int vertices)
{
    int a;
    e *list = (e *)malloc(sizeof(struct edge) * vertices);
    for (int i = 0; i < vertices; ++i)
    {
        list[i] = create(i);
    }
    do
    {
        printf(" 1 for edge 2 to break\n");
        scanf("%d", &a);
        if (a == 1)
        {
            printf(" v1, v2\n");
            int s, d;
            scanf("%d %d", &s, &d);
            e temp = list[s];
            while (temp->link != NULL)
            {
                temp = temp->link;
            }
            temp->link = create(d);
            temp = list[d];
            while (temp->link != NULL)
            {
                temp = temp->link;
            }
            temp->link = create(s);
        }
    } while (a != 2);
    for (int i = 0; i < vertices; ++i)
    {
        e temp = list[i];
        while (temp != NULL)
        {
            printf("%d ", temp->d);
            temp = temp->link;
        }
        printf("\n");
    }
    return list;
}
int **adjacencyMatrix(int vertices)
{
    int **mat = (int **)malloc(sizeof(int *) * vertices);
    for (int i = 0; i < vertices; ++i)
    {
        mat[i] = (int *)calloc(sizeof(int), vertices);
    }
    int a;
    do
    {
        printf(" 1 for edge 2 to break\n");
        scanf("%d", &a);
        if (a == 1)
        {
            printf(" v1, v2\n");
            int s, d;
            scanf("%d %d", &s, &d);
            mat[s][d] = 1;
            mat[d][s] = 1;
        }
    } while (a != 2);
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return mat;
}
void main()
{
    printf("enter no. of vertices\n");
    int v;
    scanf("%d", &v);
    e *list = adjacencyList(v);
    int **mat = adjacencyMatrix(v);
}
