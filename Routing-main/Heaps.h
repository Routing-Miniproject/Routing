#ifndef HEAPS_H
#define HEAPS_H

#include "graph.h"

typedef struct MinHeap* MinHeap;
typedef struct HeapNode* HeapNode;

// Structure to store the MinHeap data
struct MinHeap {
    int size;               // Current size of MinHeap
    int capacity;           // Maximum capacity of MinHeap
    int* IDK;               // Array to store the position of each Key
    HeapNode* Array;        // Array to store the Key-Value pair
};

// Structure to store the Key-Value pair
struct HeapNode {
    Vertex VertexID;        // Stores the VertexID of the vertex
    int Weight;             // Stores the weight of to reach the vertex from source vertex 
};

HeapNode newMinHeapNode(Vertex To, int weight);                     // Creates a new HeapNode and returns it's pointer
int IsEmpty(MinHeap PriorityQueue);                                 // To check if the Priority Queue is empty or not
void SwapNode(HeapNode* a, HeapNode* b);                            // Swaps the position of two HeapNodes using their pointers during DownHeap
MinHeap BuildHeap(int V);                                           // Builds a MinHeap of maximun capacity of V
void DownHeap(MinHeap PriorityQueue, int in);                       // Heapify the MinHeap
HeapNode ExtractMin(MinHeap PriorityQueue);                         // Extracts the pointer to the HeapNode with minimum key value
void RelaxEdge(MinHeap PriorityQueue, Vertex v, int weight);        // Relaxes the edge weight if required
int isInMinHeap(MinHeap PriorityQueue, int v);                      // Checks if the vertex is in the MinHeap or not

#endif
