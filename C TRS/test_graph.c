#include <stdio.h>
#include <assert.h>
#include "graph.h"

static void test_graph_creation_and_edges(void) {
    Graph* g = graph_create(5, false);
    assert(g != NULL);
    assert(g->num_vertices == 5);
    assert(g->is_directed == false);

    assert(graph_add_edge(g, 0, 1, 10) == true);
    assert(graph_add_edge(g, 0, 4, 20) == true);
    assert(graph_add_edge(g, 1, 2, 30) == true);
    assert(graph_add_edge(g, 1, 3, 40) == true);
    assert(graph_add_edge(g, 1, 4, 50) == true);
    assert(graph_add_edge(g, 2, 3, 60) == true);
    assert(graph_add_edge(g, 3, 4, 70) == true);

    /* Test invalid node edges */
    assert(graph_add_edge(g, -1, 2, 10) == false);
    assert(graph_add_edge(g, 0, 10, 10) == false);

    graph_free(g);
    printf("  [PASS] test_graph_creation_and_edges\n");
}

static void test_graph_bfs_and_dfs(void) {
    Graph* g = graph_create(4, true);
    assert(g != NULL);

    graph_add_edge(g, 0, 1, 1);
    graph_add_edge(g, 0, 2, 1);
    graph_add_edge(g, 1, 2, 1);
    graph_add_edge(g, 2, 0, 1);
    graph_add_edge(g, 2, 3, 1);
    graph_add_edge(g, 3, 3, 1);

    int order[GRAPH_MAX_VERTICES];
    int count = 0;

    graph_bfs(g, 2, order, &count);
    assert(count == 4);
    assert(order[0] == 2);

    count = 0;
    graph_dfs(g, 2, order, &count);
    assert(count == 4);
    assert(order[0] == 2);

    graph_free(g);
    printf("  [PASS] test_graph_bfs_and_dfs\n");
}

static void test_graph_dijkstra(void) {
    Graph* g = graph_create(5, true);
    assert(g != NULL);

    graph_add_edge(g, 0, 1, 10);
    graph_add_edge(g, 0, 4, 3);
    graph_add_edge(g, 1, 2, 2);
    graph_add_edge(g, 4, 1, 1);
    graph_add_edge(g, 4, 2, 8);
    graph_add_edge(g, 4, 3, 2);
    graph_add_edge(g, 3, 2, 4);

    /* Shortest path 0 -> 2: 0 -> 4 (3) + 4 -> 1 (1) + 1 -> 2 (2) = 6 */
    PathResult res = graph_dijkstra(g, 0, 2);
    assert(res.found == true);
    assert(res.distance == 6);
    assert(res.path_length == 4);
    assert(res.path[0] == 0);
    assert(res.path[1] == 4);
    assert(res.path[2] == 1);
    assert(res.path[3] == 2);

    /* Test unreachable target */
    Graph* g2 = graph_create(3, true);
    graph_add_edge(g2, 0, 1, 5);
    PathResult res2 = graph_dijkstra(g2, 0, 2);
    assert(res2.found == false);

    graph_free(g);
    graph_free(g2);
    printf("  [PASS] test_graph_dijkstra\n");
}

static void test_graph_cycle_detection(void) {
    /* Directed graph with cycle */
    Graph* g1 = graph_create(4, true);
    graph_add_edge(g1, 0, 1, 1);
    graph_add_edge(g1, 1, 2, 1);
    graph_add_edge(g1, 2, 0, 1);
    graph_add_edge(g1, 2, 3, 1);
    assert(graph_has_cycle(g1) == true);

    /* Directed graph without cycle */
    Graph* g2 = graph_create(4, true);
    graph_add_edge(g2, 0, 1, 1);
    graph_add_edge(g2, 0, 2, 1);
    graph_add_edge(g2, 1, 3, 1);
    graph_add_edge(g2, 2, 3, 1);
    assert(graph_has_cycle(g2) == false);

    /* Undirected graph with cycle */
    Graph* g3 = graph_create(3, false);
    graph_add_edge(g3, 0, 1, 1);
    graph_add_edge(g3, 1, 2, 1);
    graph_add_edge(g3, 2, 0, 1);
    assert(graph_has_cycle(g3) == true);

    graph_free(g1);
    graph_free(g2);
    graph_free(g3);
    printf("  [PASS] test_graph_cycle_detection\n");
}

int main(void) {
    printf("--- Running Graph Test Suite ---\n");
    test_graph_creation_and_edges();
    test_graph_bfs_and_dfs();
    test_graph_dijkstra();
    test_graph_cycle_detection();
    printf("=== ALL GRAPH TESTS PASSED ===\n");
    return 0;
}
