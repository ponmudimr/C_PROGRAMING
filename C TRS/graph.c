#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

static AdjListNode* create_node(int dest, int weight) {
    AdjListNode* new_node = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!new_node) return NULL;
    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

Graph* graph_create(int num_vertices, bool is_directed) {
    if (num_vertices <= 0 || num_vertices > GRAPH_MAX_VERTICES) {
        return NULL;
    }
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->num_vertices = num_vertices;
    graph->is_directed = is_directed;
    graph->array = (AdjList*)malloc((size_t)num_vertices * sizeof(AdjList));
    if (!graph->array) {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < num_vertices; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void graph_free(Graph* graph) {
    if (!graph) return;
    if (graph->array) {
        for (int i = 0; i < graph->num_vertices; ++i) {
            AdjListNode* curr = graph->array[i].head;
            while (curr) {
                AdjListNode* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(graph->array);
    }
    free(graph);
}

bool graph_add_edge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src < 0 || src >= graph->num_vertices || dest < 0 || dest >= graph->num_vertices) {
        return false;
    }

    AdjListNode* new_node = create_node(dest, weight);
    if (!new_node) return false;
    new_node->next = graph->array[src].head;
    graph->array[src].head = new_node;

    if (!graph->is_directed && src != dest) {
        AdjListNode* rev_node = create_node(src, weight);
        if (!rev_node) return false;
        rev_node->next = graph->array[dest].head;
        graph->array[dest].head = rev_node;
    }

    return true;
}

void graph_print(const Graph* graph) {
    if (!graph) return;
    for (int v = 0; v < graph->num_vertices; ++v) {
        AdjListNode* p_crawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (p_crawl) {
            printf("-> %d(w:%d)", p_crawl->dest, p_crawl->weight);
            p_crawl = p_crawl->next;
        }
        printf("\n");
    }
}
