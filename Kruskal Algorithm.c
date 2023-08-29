#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int vertices, edges;
    struct Edge edge[MAX_VERTICES];
};

void initGraph(struct Graph *graph, int vertices, int edges) {
    graph->vertices = vertices;
    graph->edges = edges;
    for (int i = 0; i < edges; i++) {
        graph->edge[i].src = 0;
        graph->edge[i].dest = 0;
        graph->edge[i].weight = 0;
    }
}

int compareEdges(const void *a, const void *b) {
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void kruskalMST(struct Graph *graph) {
    int vertices = graph->vertices;
    struct Edge result[vertices];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compareEdges);

    int parent[vertices];
    int rank[vertices];
    for (int v = 0; v < vertices; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    while (e < vertices - 1 && i < graph->edges) {
        struct Edge nextEdge = graph->edge[i++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionSets(parent, rank, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d: %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

int main() {
    struct Graph graph;
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    initGraph(&graph, vertices, edges);

    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        graph.edge[i].src = src;
        graph.edge[i].dest = dest;
        graph.edge[i].weight = weight;
    }

    kruskalMST(&graph);

    return 0;
}

