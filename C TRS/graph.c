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

void graph_bfs(const Graph* graph, int start_vertex, int* visit_order, int* visited_count) {
    if (!graph || !visit_order || !visited_count || start_vertex < 0 || start_vertex >= graph->num_vertices) {
        if (visited_count) *visited_count = 0;
        return;
    }

    bool visited[GRAPH_MAX_VERTICES] = { false };
    int queue[GRAPH_MAX_VERTICES];
    int front = 0, rear = 0;

    visited[start_vertex] = true;
    queue[rear++] = start_vertex;
    *visited_count = 0;

    while (front < rear) {
        int current = queue[front++];
        visit_order[(*visited_count)++] = current;

        AdjListNode* temp = graph->array[current].head;
        while (temp) {
            int adj = temp->dest;
            if (!visited[adj]) {
                visited[adj] = true;
                queue[rear++] = adj;
            }
            temp = temp->next;
        }
    }
}

static void dfs_helper(const Graph* graph, int v, bool visited[], int* visit_order, int* visited_count) {
    visited[v] = true;
    visit_order[(*visited_count)++] = v;

    AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int adj = temp->dest;
        if (!visited[adj]) {
            dfs_helper(graph, adj, visited, visit_order, visited_count);
        }
        temp = temp->next;
    }
}

void graph_dfs(const Graph* graph, int start_vertex, int* visit_order, int* visited_count) {
    if (!graph || !visit_order || !visited_count || start_vertex < 0 || start_vertex >= graph->num_vertices) {
        if (visited_count) *visited_count = 0;
        return;
    }

    bool visited[GRAPH_MAX_VERTICES] = { false };
    *visited_count = 0;
    dfs_helper(graph, start_vertex, visited, visit_order, visited_count);
}

static int min_distance(const int dist[], const bool spt_set[], int num_vertices) {
    int min = GRAPH_INF;
    int min_index = -1;

    for (int v = 0; v < num_vertices; v++) {
        if (!spt_set[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

PathResult graph_dijkstra(const Graph* graph, int start_vertex, int target_vertex) {
    PathResult res;
    res.distance = GRAPH_INF;
    res.path_length = 0;
    res.found = false;

    if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices ||
        target_vertex < 0 || target_vertex >= graph->num_vertices) {
        return res;
    }

    int dist[GRAPH_MAX_VERTICES];
    bool spt_set[GRAPH_MAX_VERTICES];
    int parent[GRAPH_MAX_VERTICES];

    for (int i = 0; i < graph->num_vertices; i++) {
        dist[i] = GRAPH_INF;
        spt_set[i] = false;
        parent[i] = -1;
    }

    dist[start_vertex] = 0;

    for (int count = 0; count < graph->num_vertices - 1; count++) {
        int u = min_distance(dist, spt_set, graph->num_vertices);
        if (u == -1 || dist[u] == GRAPH_INF) break;

        spt_set[u] = true;

        AdjListNode* temp = graph->array[u].head;
        while (temp) {
            int v = temp->dest;
            int weight = temp->weight;

            if (!spt_set[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    if (dist[target_vertex] != GRAPH_INF) {
        res.distance = dist[target_vertex];
        res.found = true;

        int temp_path[GRAPH_MAX_VERTICES];
        int count = 0;
        int curr = target_vertex;
        while (curr != -1) {
            temp_path[count++] = curr;
            curr = parent[curr];
        }

        res.path_length = count;
        for (int i = 0; i < count; i++) {
            res.path[i] = temp_path[count - 1 - i];
        }
    }

    return res;
}

static bool is_cyclic_directed_util(const Graph* graph, int v, bool visited[], bool rec_stack[]) {
    if (!visited[v]) {
        visited[v] = true;
        rec_stack[v] = true;

        AdjListNode* temp = graph->array[v].head;
        while (temp) {
            int adj = temp->dest;
            if (!visited[adj] && is_cyclic_directed_util(graph, adj, visited, rec_stack)) {
                return true;
            } else if (rec_stack[adj]) {
                return true;
            }
            temp = temp->next;
        }
    }
    rec_stack[v] = false;
    return false;
}

static bool is_cyclic_undirected_util(const Graph* graph, int v, bool visited[], int parent) {
    visited[v] = true;

    AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int adj = temp->dest;
        if (!visited[adj]) {
            if (is_cyclic_undirected_util(graph, adj, visited, v)) {
                return true;
            }
        } else if (adj != parent) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool graph_has_cycle(const Graph* graph) {
    if (!graph) return false;

    bool visited[GRAPH_MAX_VERTICES] = { false };

    if (graph->is_directed) {
        bool rec_stack[GRAPH_MAX_VERTICES] = { false };
        for (int i = 0; i < graph->num_vertices; i++) {
            if (!visited[i]) {
                if (is_cyclic_directed_util(graph, i, visited, rec_stack)) {
                    return true;
                }
            }
        }
    } else {
        for (int i = 0; i < graph->num_vertices; i++) {
            if (!visited[i]) {
                if (is_cyclic_undirected_util(graph, i, visited, -1)) {
                    return true;
                }
            }
        }
    }

    return false;
}
