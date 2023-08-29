#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Queue {
    int data[MAX_VERTICES];
    int front, rear;
};

void initialize(struct Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isEmpty(struct Queue *queue) {
    return queue->front == -1;
}

void enqueue(struct Queue *queue, int value) {
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear++;
    }
    queue->data[queue->rear] = value;
}

int dequeue(struct Queue *queue) {
    int value = queue->data[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return value;
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

void BFS(struct Graph *graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    struct Queue queue;
    initialize(&queue);

    visited[startVertex] = 1;
    printf("Breadth First Traversal (starting from vertex %d): ", startVertex);

    enqueue(&queue, startVertex);

    while (!isEmpty(&queue)) {
        int currentVertex = dequeue(&queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                enqueue(&queue, i);
                visited[i] = 1;
            }
        }
    }

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
    printf("Enter the starting vertex for BFS traversal: ");
    scanf("%d", &startVertex);

    BFS(&graph, startVertex);

    return 0;
}

