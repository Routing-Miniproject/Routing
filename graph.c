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

        G->VertexList[i]->data = 0;
        G->VertexList[i]->weight = 0;
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

    return N;
}

Node DeleteNode(Node N)
{
    free(N);
    N = NULL;

    return N;
}

//InsertEdge replaces a vertex if it already exists
//w is weight of edge (u,v) and is stored in vertex v in adjacency list
//data is the information in the vertex v and is stored in v
//worst case time complexity is O(E)

Graph InsertEdge(Graph G, Vertex u, Vertex v, Weight w)
{
    Node N = MakeNode;
    N->VertexID = v;
    N->data = G->VertexList[v]->data;
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

        G->VertexList[temp]->data = 0;
        G->VertexList[temp]->weight = 0;
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

        NewGraph->VertexList[temp]->data = 0;
        NewGraph->VertexList[temp]->weight = 0;
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
            G->VertexList[i]->data = 0;
            G->VertexList[i]->weight = 0;
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
