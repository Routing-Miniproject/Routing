

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef int ElementType;
typedef struct GraphInfo* Graph;
typedef struct NodeInfo* Node;
typedef int Weight;
typedef int Vertex;

//This graph ADT uses adjacency list

struct GraphInfo
{
    int NumVertex;
    Node* VertexList;

};

struct NodeInfo
{
    Vertex VertexID;
    ElementType* data;
    Weight weight;
    Node NextNode;
};

Node MakeNode();
Node DeleteNode(Node N);
Graph CreateGraph(int NumVertex);
Graph DeleteGraph(Graph G);
Graph InsertEdge(Graph G, Vertex u, Vertex v, Weight w);
Graph DeleteEdge(Graph G, Vertex u, Vertex v);


#endif //GRAPH_GRAPH_H
