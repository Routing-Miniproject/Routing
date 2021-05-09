#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "Heaps.h"

typedef struct PathNode *PathNode;

struct PathNode
{
    Vertex VertexID;
    PathNode NextNode;
};

#define TIME_CONSTANT_AB 5
#define TIME_CONSTANT_BE 2
#define PROPORTION_AB 80
#define PROPORTION_BE 50
#define VEHICLE_CONS_IN 5.7
#define VEHICLE_CONS_OUT 20.2
#define LOAD_FACTOR_IN 8.1
#define LOAD_FACTOR_OUT 1.2

int GetWeight(Graph G, Node Current, Node Destination, int time);
void dijkstra(Graph G, Vertex S, Vertex E, int time);
void PrintPath(Vertex S, Vertex E, int *time, int *Path, int start_time, float *distance);

#endif
