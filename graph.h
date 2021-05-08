#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

#define PRESENT 1
#define ABSENT 0

#define UNI_CROSSING_TIME 15;

typedef struct GraphInfo *Graph;
typedef struct NodeInfo *Node;
typedef int Vertex;

struct GraphInfo
{
    int NumVertex;
    int NumEdge;
    Node *VertexList;
};

struct NodeInfo
{
    // If node is a Vertex
    Vertex VertexID;
    int NumHalls;
    int NumEdge;
    float IncTraff;

    // If Node is an Edge
    int EdgeID;
    float traf_density;
    float distance;
    int SpeedLim;

    // Pointer to Next node
    Node NextNode;
};

Node MakeNode();
Graph CreateGraph(int NumVertex);
void InsertEdge(Graph G, Vertex Start, Vertex End, float distance, int speed, float traf_density);
void DeleteEdge(Graph G, Vertex u, Vertex v);


//function to generate map 
Graph getmap(); 

#endif
