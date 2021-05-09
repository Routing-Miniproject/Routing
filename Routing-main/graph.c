#include "graph.h"

Graph CreateGraph(int NumVertex)
{
    Graph G;
    G = (Graph)malloc(sizeof(struct GraphInfo));
    assert(G != NULL);

    G->NumVertex = NumVertex;
    G->NumEdge = 0;

    G->VertexList = (Node *)malloc(NumVertex * sizeof(Node));
    assert(G->VertexList != NULL);

    for (int i = 0; i < NumVertex; ++i)
    {
        G->VertexList[i] = (Node)malloc(sizeof(struct NodeInfo));
        assert(G->VertexList[i] != NULL);

        if (i < NumVertex)
            G->VertexList[i]->VertexID = i;
        else
            G->VertexList[i]->VertexID = -1;

        G->VertexList[i]->NumHalls = 0;
        G->VertexList[i]->NumEdge = 0;
        G->VertexList[i]->IncTraff = 0;

        G->VertexList[i]->EdgeID = -1;
        G->VertexList[i]->traf_density = 0;
        G->VertexList[i]->distance = 0;
        G->VertexList[i]->SpeedLim = 0;

        G->VertexList[i]->NextNode = NULL;
    }

    return G;
}

Node MakeNode()
{
    Node N = (Node)malloc(sizeof(struct NodeInfo));
    assert(N != NULL);

    N->NumHalls = 0;
    N->NumEdge = 0;

    N->NextNode = NULL;

    return N;
}

void InsertEdge(Graph G, Vertex Start, Vertex End, float distance, int speed, float traf_density)
{
    G->NumEdge += 1;

    Node N = MakeNode();

    N->VertexID = End;
    N->EdgeID = G->NumEdge;
    N->distance = distance;
    N->traf_density = traf_density;
    N->SpeedLim = speed;

    Node Temp = G->VertexList[Start]->NextNode;
    N->NextNode = Temp;
    G->VertexList[Start]->NextNode = N;

    G->VertexList[Start]->NumEdge += 1;

    G->VertexList[End]->IncTraff += traf_density;
}

void DeleteEdge(Graph G, Vertex u, Vertex v)
{
    Node temp = G->VertexList[u];

    while (temp->NextNode != NULL)
    {
        if (temp->NextNode->VertexID == v)
        {
            Node N = temp->NextNode->NextNode;
            free(temp->NextNode);
            temp->NextNode = N;

            break;
        }

        temp = temp->NextNode;
    }
}

Graph getmap()
{
    int V, E;

    FILE *fp = fopen("graphinput.txt", "r");
    fscanf(fp, "%d", &V); 

    Graph G = CreateGraph(V);

    int NumHalls;
    for (int i = 0; i < V; ++i)
    {
        fscanf(fp, "%d", &NumHalls);
        G->VertexList[i]->NumHalls = NumHalls;
    }

    fscanf(fp, "%d", &E);

    int Start, End;
    float distance, traf_density;
    int speed;

    for (int i = 0; i < E; ++i)
    {

        fscanf(fp, "%d %d", &Start, &End);
        fscanf(fp, "%f %d %f", &distance, &speed, &traf_density);

        InsertEdge(G, Start, End, distance, speed, traf_density);
    }

    return G;
}

void PrintGraph(Graph G)
{
    Node temp;
    for (int i = 0; i < G->NumVertex; ++i)
    {
        temp = G->VertexList[i]->NextNode;

        printf("%d --> {", G->VertexList[i]->VertexID);

        while (temp != NULL)
        {
            printf(" %d", temp->VertexID);
            temp = temp->NextNode;
        }

        printf("}\n");
    }
}
