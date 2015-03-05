#include <stdio.h>
#include <limits.h>

#include "Graph.h"

/************************************************************************************/
// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
#define V 9
void print_solution(int dist[], int n) {
    printf("Vertex distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
// Find index of undiscovered node with shortest distance from discovered graph.
int min_distance(int dist[], bool spt_set[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (spt_set[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}
// The output array. dist[i] will hold the shortest distance from src to i
void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool spt_set[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        spt_set[i] = false;
    }
    dist[src] = 0;

    for (int i = 0; i < V - 1; ++i) {
        int u = min_distance(dist, spt_set);
        spt_set[u] = true;
        for (int v = 0; v < V; ++v)
            // Update all nodes not in SPT that are connected to vertex 'u', have distance information,
            // but whose distance is the worst then the one just discovered.
            if (!spt_set[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    print_solution(dist, V);
}
/*
int graph[V][V] = { 
      0   1   2   3   4   5   6   7   8
    { 0,  4,  0,  0,  0,  0,  0,  8,  0 },
    { 4,  0,  8,  0,  0,  0,  0, 11,  0 },
    { 0,  8,  0,  7,  0,  4,  0,  0,  2 },
    { 0,  0,  7,  0,  9, 14,  0,  0,  0 },
    { 0,  0,  0,  9,  0, 10,  0,  0,  0 },
    { 0,  0,  4,  0, 10,  0,  2,  0,  0 },
    { 0,  0,  0, 14,  0,  2,  0,  1,  6 },
    { 8, 11,  0,  0,  0,  0,  1,  0,  7 },
    { 0,  0,  2,  0,  0,  0,  6,  7,  0 }
};

dijkstra(graph, 0);

Vertex   Distance from Source
0        0
1        4
2        12
3        19
4        21
5        11
6        9
7        8
8        14
*/
/************************************************************************************/