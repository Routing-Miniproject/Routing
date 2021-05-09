#include "dijkstra.h"



int GetWeight(Graph G, Node Current, Node Destination, int time)
{
    float weight;

    //printf("%d ----> %d\n", Current->VertexID, Destination->VertexID);
    //printf("%g %d %g\n", Destination->distance, Destination->SpeedLim, Destination->traf_density);
    //printf("%d\n", Current->NumHalls);
    //printf("%g\n\n", G->VertexList[Destination->VertexID]->IncTraff);
    
    float LOAD_FCT;
    if (time <= 22*60 && time >= 18*60)
    {
        LOAD_FCT = LOAD_FACTOR_IN;
    }
    else
    {
        LOAD_FCT = LOAD_FACTOR_OUT;
    }

    int TIME_CST;
    int PROP_CST;
    if (G->VertexList[Destination->VertexID]->IncTraff > 40)
    {
        TIME_CST = TIME_CONSTANT_AB;
        PROP_CST = PROPORTION_AB;
    }
    else
    {
        TIME_CST = TIME_CONSTANT_BE;
        PROP_CST = PROPORTION_BE;
    }

    float Traf_New = (Destination->traf_density) + (VEHICLE_CONS * LOAD_FCT) * (((float)Current->NumHalls) / ((float)Current->NumEdge) + 0.01);
    weight = ((Destination->distance) * (Traf_New)) / ((Destination->SpeedLim) * (Destination->traf_density));
    weight = weight * 60;
    weight += (TIME_CST) * ((G->VertexList[Destination->VertexID]->IncTraff) / PROP_CST);

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

    Vertex Path[V];
    for (int i = 0; i < V; ++i)
    {
        Path[i] = i;
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

                Path[Destination] = CurrentID;
                time[Destination] = time[CurrentID] + temp_weight;
                
                RelaxEdge(PriorityQueue, Destination, time[Destination]);
            }

            temp = temp->NextNode;
        }

        if (CurrentID == E)
            break;
    }

    PrintPath(S, E, time, Path, start_time);
}

void PrintPath(Vertex S, Vertex E, int* time, int* Path, int start_time)
{
    printf("Estimated Travel Duration: %d mins\n", time[E]);
    
    int H = (start_time + time[E])/60;
    int M = (start_time + time[E])%60;

    printf("Estimated Arrival Time: %2d:%2d\n", H, M);

    PathNode NewPath = (PathNode)malloc(sizeof(struct PathNode));
    NewPath->VertexID = S;
    NewPath->NextNode = NULL;

    Vertex in = E;
    while (in != S)
    {
        PathNode temp = (PathNode)malloc(sizeof(struct PathNode));

        temp->VertexID = in;
        temp->NextNode = NewPath->NextNode;
        NewPath->NextNode = temp;

        in = Path[in];
    }

    printf("%d ", S);
    int CurrentTime = 0;
    PathNode temp = NewPath->NextNode;

    while (temp != NULL)
    {
        printf("-- %d mins --> %d ",time[temp->VertexID]-CurrentTime, temp->VertexID);
        CurrentTime = time[temp->VertexID];
        temp = temp->NextNode;
    }

    printf("\n");
}