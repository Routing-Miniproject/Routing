#include "dijkstra.h"

int GetWeight(Graph G, Node Current, Node Destination, int time)
{
    float weight;
    float Traf_New = (Destination->traf_density) + (VEHICLE_CONS * LOAD_FACTOR) * (((float)Current->NumHalls) / ((float)Current->NumEdge) + 0.01);

    weight = ((Destination->distance) * (Traf_New)) / ((Destination->SpeedLim) * (Destination->traf_density));
    weight = weight * 60;
    weight += (TIME_CONSTANT) * ((G->VertexList[Destination->VertexID]->IncTraff) / PROPORTION);

    return ceil(weight);
}

void dijkstra(Graph G, Vertex S, Vertex E, int start_time)
{
    int V = G->NumVertex;

    MinHeap PriorityQueue = BuildHeap(V);

    int time[V];
    for (int i = 0; i < V; ++i)
    {
        time[i] = INT_MAX;
    }

    for (int i = 0; i < V; ++i)
    {
        PriorityQueue->Array[i] = newMinHeapNode(i, time[i]);
        PriorityQueue->IDK[i] = i;
    }

    Vertex Path[V][2];
    for (int i = 0; i < V; ++i)
    {
        Path[i][0] = i;
        Path[i][1] = -1;
    }

    PriorityQueue->Array[S] = newMinHeapNode(S, time[S]);
    PriorityQueue->IDK[S] = S;
    time[S] = 0;
    RelaxEdge(PriorityQueue, S, time[S]);

    PriorityQueue->size = V;

    while (!(IsEmpty(PriorityQueue)))
    {
        HeapNode Current = ExtractMin(PriorityQueue);

        Vertex CurrentID = Current->VertexID;
        float CurrentWeight = Current->Weight;

        Node temp = G->VertexList[CurrentID]->NextNode;

        while (temp != NULL)
        {
            int time_travel = time[CurrentID] + start_time;
            int temp_weight = GetWeight(G, G->VertexList[CurrentID], temp, time_travel);
            Vertex Destination = temp->VertexID;

            if (isInMinHeap(PriorityQueue, Destination) && time[CurrentID] != INT_MAX && temp_weight + time[CurrentID] < time[Destination])
            {
                Path[Destination][0] = CurrentID;
                Path[Destination][1] = temp->EdgeID;
                time[Destination] = time[CurrentID] + temp_weight;

                // update distance
                // value in min heap also
                RelaxEdge(PriorityQueue, Destination, time[Destination]);
            }

            temp = temp->NextNode;
        }

        if (CurrentID == E)
            break;
    }

    PrintPath(time, Path);
}

void PrintPath(int* time, int* Path)
{
    
}