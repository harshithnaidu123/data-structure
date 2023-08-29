#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Stack {
    int data[MAX_VERTICES];
    int top;
};

void initialize(struct Stack *stack) {
    stack->top = -1;
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void push(struct Stack *stack, int value) {
    stack->data[++stack->top] = value;
}

int pop(struct Stack *stack) {
    return stack->data[stack->top--];
}

struct Graph {
    int vertices;
    int edges;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};

void initGraph(struct Graph *graph, int vertices) {
    graph->vertices = vertices;
    graph->edges = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(struct Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
    graph->edges++;
}

void DFS(struct Graph *graph, int startVertex, int visited[]) {
    printf("%d ", startVertex);
    visited[startVertex] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[startVertex][i] == 1 && !visited[i]) {
            DFS(graph, i, visited);
        }
    }
}

void depthFirstTraversal(struct Graph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    DFS(graph, startVertex, visited);
    printf("\n");
}

int main() {
    struct Graph graph;
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initGraph(&graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        int src, dest;
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(&graph, src, dest);
    }

    int startVertex;
    printf("Enter the starting vertex for DFS traversal: ");
    scanf("%d", &startVertex);

    printf("Depth First Traversal (starting from vertex %d): ", startVertex);
    depthFirstTraversal(&graph, startVertex);

    return 0;
}

