#ifndef MINHEAP_MINHEAP_H
#define MINHEAP_MINHEAP_H

//The array associated with this minheap implementation starts at index 0
//left_child 2i + 1
//right_child 2i + 2
//parent GIF((i-1)/2)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

#define MIN(a,b)    a>=b ? a : b

typedef Node ElementType;
typedef ElementType* MinHeap;

void Swap(ElementType* X, ElementType* Y);
void SwapInt(int* X, int* Y);
MinHeap BuildHeap(MinHeap A, int NumElem);
MinHeap DownHeap(MinHeap A, int NumElem, int index);
MinHeap UpHeap(MinHeap A, int NumElem, int index);
int FindParent(int child);
MinHeap DeleteMinHeapElement(MinHeap A, int NumElem, int index);
int FindMinHeapElement(MinHeap A, int NumElem, ElementType X);// same O(N) code as for a general binary tree which returns the array index of X
MinHeap InsertMinHeapElement(MinHeap A, int NumElem, ElementType X);
Vertex ExtractMin(MinHeap A, int NumElem);

#endif //MINHEAP_MINHEAP_H