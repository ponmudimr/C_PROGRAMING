#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <stdbool.h>

#define GRAPH_MAX_VERTICES 100
#define GRAPH_INF 1000000000

typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int num_vertices;
    bool is_directed;
    AdjList* array;
} Graph;

typedef struct PathResult {
    int distance;
    int path[GRAPH_MAX_VERTICES];
    int path_length;
    bool found;
} PathResult;

/* Core Graph Operations */
Graph* graph_create(int num_vertices, bool is_directed);
void graph_free(Graph* graph);
bool graph_add_edge(Graph* graph, int src, int dest, int weight);
void graph_print(const Graph* graph);

#endif /* GRAPH_H */
