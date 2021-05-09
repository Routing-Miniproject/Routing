#include "Heaps.h"

HeapNode newMinHeapNode(Vertex To, int weight)
{
    HeapNode MinHeapNode = (HeapNode)malloc(sizeof(struct HeapNode));

    MinHeapNode->VertexID = To;
    MinHeapNode->Weight = weight;

    return MinHeapNode;
}

int IsEmpty(MinHeap PriorityQueue)
{
    if (PriorityQueue->size == 0)
        return 1;
    else
        return 0;
}

void SwapNode(HeapNode *a, HeapNode *b)
{
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

MinHeap BuildHeap(int V)
{
    MinHeap PriorityQueue = (MinHeap)malloc(sizeof(struct MinHeap));

    PriorityQueue->size = 0;
    PriorityQueue->capacity = V;
    PriorityQueue->IDK = (int *)malloc(V * sizeof(int));
    PriorityQueue->Array = (HeapNode *)malloc(V * sizeof(struct HeapNode));

    return PriorityQueue;
}

void DownHeap(MinHeap PriorityQueue, int in)
{
    int smallest, left, right;

    smallest = in;
    left = (2 * in) + 1;
    right = (2 * in) + 2;

    if (left < PriorityQueue->size && PriorityQueue->Array[left]->Weight < PriorityQueue->Array[smallest]->Weight)
        smallest = left;

    if (right < PriorityQueue->size && PriorityQueue->Array[right]->Weight < PriorityQueue->Array[smallest]->Weight)
        smallest = right;

    if (smallest != in)
    {
        HeapNode smallestNode = PriorityQueue->Array[smallest];
        HeapNode inNode = PriorityQueue->Array[in];

        PriorityQueue->IDK[smallestNode->VertexID] = in;
        PriorityQueue->IDK[inNode->VertexID] = smallest;

        SwapNode(&PriorityQueue->Array[smallest], &PriorityQueue->Array[in]);

        DownHeap(PriorityQueue, smallest);
    }
}

HeapNode ExtractMin(MinHeap PriorityQueue)
{
    if (IsEmpty(PriorityQueue))
        return NULL;

    HeapNode Root_Node = PriorityQueue->Array[0];

    HeapNode Last_Node = PriorityQueue->Array[PriorityQueue->size - 1];
    PriorityQueue->Array[0] = Last_Node;

    PriorityQueue->IDK[Root_Node->VertexID] = PriorityQueue->size - 1;
    PriorityQueue->IDK[Last_Node->VertexID] = 0;

    PriorityQueue->size -= 1;
    DownHeap(PriorityQueue, 0);

    return Root_Node;
}

void RelaxEdge(MinHeap PriorityQueue, Vertex v, int weight)
{
    int i = PriorityQueue->IDK[v];

    PriorityQueue->Array[i]->Weight = weight;

    while (i && PriorityQueue->Array[i]->Weight < PriorityQueue->Array[(i - 1) / 2]->Weight)
    {
        PriorityQueue->IDK[PriorityQueue->Array[i]->VertexID] = (i - 1) / 2;

        PriorityQueue->IDK[PriorityQueue->Array[(i - 1) / 2]->VertexID] = i;

        SwapNode(&PriorityQueue->Array[i], &PriorityQueue->Array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap PriorityQueue, int v)
{
    if (PriorityQueue->IDK[v] < PriorityQueue->size)
        return 1;

    return 0;
}
