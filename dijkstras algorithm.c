#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Graph {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};

void initGraph(struct Graph *graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(struct Graph *graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}

int findMinDistance(int dist[], bool visited[], int vertices) {
    int minDist = INT_MAX, minIndex = -1;
    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && dist[v] < minDist) {
            minDist = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(struct Graph *graph, int startVertex) {
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];

    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[startVertex] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int u = findMinDistance(dist, visited, vertices);
        visited[u] = true;

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph->adjMatrix[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
            }
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
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
        int src, dest, weight;
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    int startVertex;
    printf("Enter the starting vertex for Dijkstra's algorithm: ");
    scanf("%d", &startVertex);

    dijkstra(&graph, startVertex);

    return 0;
}

