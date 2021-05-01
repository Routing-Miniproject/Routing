#include "MinHeap.h"

//O(log N)
MinHeap DownHeap(MinHeap A, int NumElem, int index)
{
    int parent=index;
    int child = 2*index + 1;

    while(child < NumElem)
    {
        if (child+1 < NumElem)
        {
            if (*(A[child+1]->distance) < *(A[child]->distance))
            {
                ++child;
            }
        }

        if (*(A[parent]->distance) < *(A[child]->distance))
        {
            SwapInt(A[parent]->HeapIndex, A[child]->HeapIndex);
            Swap(A+parent, A+child);
        }

        parent=child;
        child = 2*parent + 1;
    }

    return A;

}

int FindParent(int child)
{
    if(child%2==0)
        return child/2;

    return (child-1)/2;

}

//O(log N)
MinHeap UpHeap(MinHeap A, int NumElem, int index)
{
    int child = index;
    int parent = FindParent(child);

    while(parent>=0)
    {
        if (*(A[child]->distance)< *(A[parent]->distance))
        {
            SwapInt(A[parent]->HeapIndex, A[child]->HeapIndex);
            Swap(A+parent, A+child);
        }
        child=parent;
        parent=FindParent(child);
    }

    return A;
}

//O(N)
MinHeap BuildHeap(MinHeap A, int NumElem)
{
    for (int i= (NumElem-1)/2; i>=0; ++i)
    {
        DownHeap(A, NumElem, i);
    }

    return A;
}

void Swap(ElementType* X, ElementType* Y)
{
    Node temp= *X;
    *X=*Y;
    *Y=temp;

    return;
}


void SwapInt(int* X, int* Y)
{
    int temp= *X;
    *X=*Y;
    *Y=temp;

    return;
}

//O(N) to search and O(log N) to delete
MinHeap DeleteMinHeapElement(MinHeap A, int NumElem, int index)
{
    SwapInt(A[index]->HeapIndex, A[NumElem-1]->HeapIndex);
    Swap(A+index, A+NumElem-1);
    DownHeap(A, NumElem-1, index);

    return A;
}

//O(log N)
MinHeap InsertMinHeapElement(MinHeap A, int NumElem, ElementType X)
{
    A[NumElem]=X;
    A[NumElem]->HeapIndex=NumElem;
    NumElem++;

    A=UpHeap(A, NumElem, NumElem-1);

    return A;
}

//O(log N)
Vertex ExtractMin(MinHeap A, int NumElem)
{
    Node MinElem = A[0];
    A= DeleteMinHeapElement(A, NumElem, 0);

    return MinElem->VertexID;
}