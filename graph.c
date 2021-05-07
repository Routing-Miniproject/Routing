#include "graph.h"

//time complexity of CreateGraph is O(V)
Graph CreateGraph(int NumVertex)
{
    Graph G;
    G = (Graph)malloc(sizeof(struct GraphInfo));
    assert(G != NULL);

    G->NumVertex = NumVertex;

    G->VertexList = (Node *)malloc(2 * NumVertex * sizeof(Node));
    assert(G->VertexList != NULL);

    for (int i = 0; i < 2 * NumVertex; ++i)
    {
        G->VertexList[i] = (Node)malloc(sizeof(struct NodeInfo));
        assert(G->VertexList[i] != NULL);

        if (i < NumVertex)
            G->VertexList[i]->VertexID = i;
        else
            G->VertexList[i]->VertexID = -1;

        G->VertexList[i]->distance = (int *)malloc(sizeof(int));
        assert(G->VertexList[i]->distance != NULL);
        G->VertexList[i]->HeapIndex = (int *)malloc(sizeof(int));
        assert(G->VertexList[i]->HeapIndex != NULL);
        G->VertexList[i]->predecessor = (Vertex *)malloc(sizeof(Vertex));
        assert(G->VertexList[i]->predecessor != NULL);
        G->VertexList[i]->data = (int *)malloc(sizeof(int));
        assert(G->VertexList[i]->data != NULL);

        *(G->VertexList[i]->predecessor) = -1;
        G->VertexList[i]->NextNode = NULL;
    }
}

//time complexity of DeleteGraph is O(V+E)
Graph DeleteGraph(Graph G)
{
    Node temp;

    for (int i = 0; i < G->NumVertex; ++i)
    {
        temp = G->VertexList[i]->NextNode;

        while (temp != NULL)
        {
            G->VertexList[i]->NextNode = temp->NextNode;
            DeleteNode(temp);
            temp = G->VertexList[i]->NextNode;
        }

        DeleteNode(G->VertexList[i]);
    }

    free(G->VertexList);
    free(G);
    G = NULL;

    return G;
}

Node MakeNode()
{
    Node N = (Node)malloc(sizeof(struct NodeInfo));
    assert(N != NULL);

    N->distance = (int *)malloc(sizeof(int));
    assert(N->distance != NULL);
    N->HeapIndex = (int *)malloc(sizeof(int));
    assert(N->HeapIndex != NULL);
    N->predecessor = (Vertex *)malloc(sizeof(Vertex));
    assert(N->predecessor != NULL);
    N->data = (int *)malloc(sizeof(int));
    assert(N->data != NULL);

    *(N->predecessor) = -1;
    N->NextNode = NULL;

    return N;
}

Node DeleteNode(Node N)
{
    free(N->data);
    free(N->distance);
    free(N->HeapIndex);
    free(N->predecessor);
    free(N);
    N = NULL;

    return N;
}

//InsertEdge replaces a vertex if it already exists
//w is weight of edge (u,v) and is stored in vertex v in adjacency list
//data is the information in the vertex v and is stored in v
//worst case time complexity is O(E)

Graph InsertEdge(Graph G, Vertex u, Vertex v, int w)
{
    Node N = MakeNode;
    N->VertexID = v;
    N->data = G->VertexList[v]->data;
    N->predecessor = G->VertexList[v]->predecessor;
    N->HeapIndex = G->VertexList[v]->HeapIndex;
    N->distance = G->VertexList[v]->distance;
    N->weight = w;

    //search if vertex v already exists

    Node temp = G->VertexList[u];

    while (temp->NextNode != NULL)
    {
        if (temp->NextNode->VertexID == v)
        {
            N->NextNode = temp->NextNode->NextNode;
            DeleteNode(temp->NextNode);
            temp->NextNode = N;

            return G;
        }

        temp = temp->NextNode;
    }

    //if v does not exist already
    temp->NextNode = N;
    N->NextNode = NULL;

    return G;
}

//worst case time complexity of DeleteEdge is O(E)
Graph DeleteEdge(Graph G, Vertex u, Vertex v)
{
    Node temp = G->VertexList[u];

    while (temp->NextNode != NULL)
    {
        if (temp->NextNode->VertexID == v)
        {
            Node N = temp->NextNode->NextNode;
            DeleteNode(temp->NextNode);
            temp->NextNode = N;

            return G;
        }

        temp = temp->NextNode;
    }

    return G;
}

Graph AddNode(Graph G)
{
    if (G->NumVertex < sizeof(*(G->VertexList)) / sizeof(Node))
    {
        G->NumVertex++;

        int temp = G->NumVertex;
        G->VertexList[temp]->VertexID = temp;

        G->VertexList[temp]->predecessor = -1;
        G->VertexList[temp]->NextNode = NULL;

        return G;
    }
    else
    {
        Graph NewGraph = CreateGraph(G->NumVertex);

        for (int i = 0; i < G->NumVertex; ++i)
        {
            NewGraph->VertexList[i] = G->VertexList[i];
        }

        NewGraph->NumVertex++;

        int temp = NewGraph->NumVertex;
        NewGraph->VertexList[temp]->VertexID = temp;

        G->VertexList[temp]->predecessor = -1;
        NewGraph->VertexList[temp]->NextNode = NULL;

        free(G);
        return NewGraph;
    }
}

Graph RemoveNode(Graph G, Vertex v)
{
    Node temp;

    for (int i = 0; i < G->NumVertex; ++i)
    {
        temp = G->VertexList[i];

        if (temp->VertexID == v)
        {
            temp = G->VertexList[i]->NextNode;

            while (temp != NULL)
            {
                G->VertexList[i]->NextNode = temp->NextNode;
                DeleteNode(temp);
                temp = G->VertexList[i]->NextNode;
            }

            G->VertexList[i]->VertexID = -1;
            G->VertexList[i]->predecessor = -1;
            G->VertexList[i]->NextNode = NULL;
        }
        else
        {
            while (temp->NextNode != NULL && temp->NextNode->VertexID != v)
            {
                temp = temp->NextNode;
            }

            if (temp->NextNode != NULL && temp->NextNode->VertexID == v)
            {
                Node TobeDeleted = temp->NextNode;
                temp->NextNode = temp->NextNode->NextNode;
                DeleteNode(TobeDeleted);
            }
        }
    }
}

//time complexity is O((V+E)log V)
void Dijkstra(Graph G)
{
    //Initialisation begins................................
    int N = G->NumVertex;
    int S[G->NumVertex];
    Node *Q = (Node *)malloc(G->NumVertex * sizeof(Node));
    assert(Q != NULL);

    S[0] = ABSENT;
    *(G->VertexList[0]->distance) = 0;

    Q = InsertMinHeapElement(Q, 0, G->VertexList[0]);

    for (int i = 1; i < G->NumVertex; ++i)
    {
        S[i] = ABSENT;

        *(G->VertexList[i]->distance) = INT_MAX;
        Q = InsertMinHeapElement(Q, i, G->VertexList[i]);
    }

    //Initialisation ends.....................................

    Vertex u, v;
    Node temp;
    while (N >= 0)
    {
        u = ExtractMin(Q, N);
        N--;
        S[u] = PRESENT;

        //Relaxation of the outgoing edges of u
        temp = G->VertexList[u]->NextNode;
        while (temp != NULL)
        {
            v = temp->VertexID;
            G = RelaxEdge(G, Q, N, u, v);

            temp = temp->NextNode;
        }
    }
    free(Q);

    return;
}

Graph RelaxEdge(Graph G, MinHeap A, int NumHeapElem, Vertex u, Vertex v)
{
    int NewDist = *(G->VertexList[u]->distance) + G->VertexList[v]->weight;
    int OldDist = *(G->VertexList[v]->distance);
    if (NewDist < OldDist)
    {
        *(G->VertexList[v]->distance) = NewDist;
        *(G->VertexList[v]->predecessor) = u;
        A = UpHeap(A, NumHeapElem, *(G->VertexList[v]->HeapIndex));
    }

    return G;
}

Graph getmap()
{
    int V, E;

    FILE *fp = fopen("graphinput.txt", "r");
    fscanf(fp, "%d", &V); //number of vertices

    int time_delay[V];
    for (int i = 0; i < V; i++)
    {
        fscanf(fp, "%d", &time_delay[i]);
    }

    fscanf(fp, "%d", &E); //number of edges

    int start[E], end[E]; //start and end points of an edge
    for (int j = 0; j < E; j++)
    {
        fscanf(fp, "%d %d", start[j], end[j]);
    }

    float length[E]; //length of edge
    for (int k = 0; k < E; k++)
    {
        fscanf(fp, "%f", &length[k]);
    }

    int traf_density[E], num_marriages[E], speed[E];
    for (int i = 0; i < E; i++)
    {
        fscanf(fp, "%d", &traf_density[i]);
    }
    for (int j = 0; j < E; j++)
    {
        fscanf(fp, "%d", &num_marriages[j]);
    }
    for (int k = 0; k < E; k++)
    {
        fscanf(fp, "%d", &speed[k]);
    }

    //function to calculate the weight of
    //each node based on above inputs
    getweight();

}