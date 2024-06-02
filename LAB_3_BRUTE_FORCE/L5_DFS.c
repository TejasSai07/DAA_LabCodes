#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 
int visited[MAX_VERTICES];
int pushOrder[MAX_VERTICES], popOrder[MAX_VERTICES];
int pushIndex = 0, popIndex = 0;

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjacencyList;
} Graph;

Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));   
    graph->numVertices = n;
    graph->adjacencyList = (Node**)malloc(n * sizeof(Node*));

    for (int i = 0; i < n; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void dfs(Graph* graph, int vertex) {
    visited[vertex] = 1;
    pushOrder[pushIndex++] = vertex;

    Node* currentNode = graph->adjacencyList[vertex];
    while (currentNode != NULL) {
        int adjacentVertex = currentNode->vertex;
        if (!visited[adjacentVertex]) {
            dfs(graph, adjacentVertex);
        }
        currentNode = currentNode->next;
    }

    popOrder[popIndex++] = vertex;
}

int main() {
    int numVertices = 6; 
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);

    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    dfs(graph, 0);

    printf("Push Order: ");
    for (int i = 0; i < pushIndex; i++) {
        printf("%d ", pushOrder[i]);
    }
    printf("\n");

    printf("Pop Order: ");
    for (int i = 0; i < popIndex; i++) {
        printf("%d ", popOrder[i]);
    }
    printf("\n");

    return 0;
}
