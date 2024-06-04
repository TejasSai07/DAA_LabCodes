#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
};

struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void topologicalSortDFSUtil(struct Graph* graph, int vertex, int* visited, struct Node** stack, int* stackIndex) {
    visited[vertex] = 1;

    struct Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            topologicalSortDFSUtil(graph, temp->vertex, visited, stack, stackIndex);
        }
        temp = temp->next;
    }

    stack[++(*stackIndex)] = createNode(vertex);
}

void topologicalSortDFS(struct Graph* graph) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    struct Node** stack = (struct Node**)malloc(graph->vertices * sizeof(struct Node*));
    int stackIndex = -1;

    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            topologicalSortDFSUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    printf("Topological Order using DFS: ");
    while (stackIndex >= 0) {
        printf("%d ", stack[stackIndex--]->vertex);
    }

    free(visited);
    free(stack);
}

void topologicalSortSourceRemoval(struct Graph* graph) {
    int* inDegree = (int*)malloc(graph->vertices * sizeof(int));

    for (int i = 0; i < graph->vertices; i++) {
        inDegree[i] = 0;
    }

    for (int i = 0; i < graph->vertices; i++) {
        struct Node* temp = graph->adjList[i];
        while (temp != NULL) {
            inDegree[temp->vertex]++;
            temp = temp->next;
        }
    }

    struct Node** stack = (struct Node**)malloc(graph->vertices * sizeof(struct Node*));
    int stackIndex = -1;

    for (int i = 0; i < graph->vertices; i++) {
        if (inDegree[i] == 0) {
            stack[++stackIndex] = createNode(i);
        }
    }

    printf("\nTopological Order using Source Removal: ");
    while (stackIndex >= 0) {
        int vertex = stack[stackIndex--]->vertex;
        printf("%d ", vertex);

        struct Node* temp = graph->adjList[vertex];
        while (temp != NULL) {
            inDegree[temp->vertex]--;
            if (inDegree[temp->vertex] == 0) {
                stack[++stackIndex] = createNode(temp->vertex);
            }
            temp = temp->next;
        }
    }

    free(inDegree);
    free(stack);
}

int main() {
    int vertices, edges, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Graph* graph = createGraph(vertices);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    topologicalSortDFS(graph);

    topologicalSortSourceRemoval(graph);

    return 0;
}
