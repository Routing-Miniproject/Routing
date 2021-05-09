#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "Heaps.h"

typedef struct PathNode* PathNode;

struct PathNode {
    Vertex VertexID;
    PathNode NextNode;
};

#define TIME_CONSTANT_AB 5
#define TIME_CONSTANT_BE 2
#define PROPORTION_AB 30
#define PROPORTION_BE 10
#define VEHICLE_CONS 3.7
#define LOAD_FACTOR_IN 2.1
#define LOAD_FACTOR_OUT 0.2

int GetWeight(Graph G, Node Current, Node Destination, int time);
void dijkstra(Graph G, Vertex S, Vertex E, int time);
void PrintPath(Vertex S, Vertex E, int* time, int* Path, int start_time);

#endif