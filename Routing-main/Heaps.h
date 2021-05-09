#ifndef HEAPS_H
#define HEAPS_H

#include "graph.h"

typedef struct MinHeap *MinHeap;
typedef struct HeapNode *HeapNode;

struct MinHeap
{
    int size;
    int capacity;
    int *IDK;
    HeapNode *Array;
};

struct HeapNode
{
    Vertex VertexID;
    int Weight;
};

HeapNode newMinHeapNode(Vertex To, int weight);
int IsEmpty(MinHeap PriorityQueue);
void SwapNode(HeapNode *a, HeapNode *b);
MinHeap BuildHeap(int V);
void DownHeap(MinHeap PriorityQueue, int in);
HeapNode ExtractMin(MinHeap PriorityQueue);
void RelaxEdge(MinHeap PriorityQueue, Vertex v, int weight);
int isInMinHeap(MinHeap PriorityQueue, int v);

#endif