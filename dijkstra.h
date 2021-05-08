#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "Heaps.h"

typedef struct PathNode* PathNode;

struct PathNode {
    Vertex VertexID;
    PathNode NextNode;
};

#define TIME_CONSTANT 5
#define PROPORTION 10
#define VEHICLE_CONS 15
#define LOAD_FACTOR 2

int GetWeight(Graph G, Node Current, Node Destination, int time);
void dijkstra(Graph G, Vertex S, Vertex E, int time);
void PrintPath(Vertex S, Vertex E, int* time, int* Path, int start_time);

#endif