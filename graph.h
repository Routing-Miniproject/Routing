#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

#include "MinHeap.h"

#define PRESENT 1
#define ABSENT 0

typedef struct GraphInfo *Graph;
typedef struct NodeInfo *Node;
typedef int Vertex;

//This graph ADT uses adjacency list

struct GraphInfo
{
    int NumVertex;
    int NumEdge;
    Node *VertexList;
};

//some of the atributes of NodeInfo are declared as pointers so that changing any node of a
//given vertex v, changes all the nodes in the adjacency list, corresponding to vertex v
/*struct NodeInfo
{
    Vertex VertexID;
    int *data;
    int weight;
    int *distance;
    int *HeapIndex;
    Vertex *predecessor;

    Node NextNode;
};
*/
struct NodeInfo
{
    //For a Vertex
    Vertex VertexID;
    int NumHalls;
    float IncTraff;
    int NumEdges;
    int SignalDelay;

    //For an Edge
    float TraffDen;
    float distance;
    int SpeedLim;

    int *HeapIndex;
    Vertex *predecessor;

    // Pointer to Next node
    Node NextNode;
};

Node MakeNode();
Node DeleteNode(Node N);
Graph CreateGraph(int NumVertex);
Graph DeleteGraph(Graph G);
Graph InsertEdge(Graph G, Vertex u, Vertex v, int w);
Graph DeleteEdge(Graph G, Vertex u, Vertex v);
void Dijkstra(Graph G);
Graph RelaxEdge(Graph G, MinHeap A, int NumHeapElem, Vertex u, Vertex v);
Graph AddNode(Graph G);
Graph RemoveNode(Graph G, Vertex v);

float GetWeight(Graph G, Vertex u, Vertex v, float distance, float speed, float traf_density); 
//function to generate map 
Graph getmap(); 

#endif //GRAPH_GRAPH_H
