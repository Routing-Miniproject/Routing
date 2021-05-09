#include "graph.h"
#include "Heaps.h"
#include "dijkstra.h"

int main()
{
    Graph G = getmap();

    printf("Operation Codes:\n");
    printf("0. Exit\n");
    printf("1. Find Shortest Path\n");
    printf("2. Add Edge\n");
    printf("3. Delete Edge\n");
    printf("4. Print Graph\n");
    printf("5. Get Weight\n");

    printf("\n");

    int Operation;
    printf("Operation Code: ");
    scanf("%d", &Operation);

    while (Operation != 0)
    {
        if (Operation == 1)
        {
            Vertex S, E;
            int H, M;
            printf("Enter Starting Vertex: ");
            scanf("%d", &S);
            printf("Enter Destination Vertex: ");
            scanf("%d", &E);
            printf("Enter time of travel (HH:MM): ");
            scanf("%d:%d", &H, &M);

            int time  = (H*60)+M;

            printf("\n");
            dijkstra(G, S, E, time);
        }
        else if (Operation == 2)
        {
            int S, E;
            float distance, traf_density;
            int speed;

            printf("Enter Starting Vertex: ");
            scanf("%d", &S);
            printf("Enter Destination Vertex: ");
            scanf("%d", &E);
            printf("Enter length of the road (Km): ");
            scanf("%f", &distance);
            printf("Enter speed limit of the road (Km/hr): ");
            scanf("%d", &speed);
            printf("Enter traffic density of the road: ");
            scanf("%f", &traf_density);

            InsertEdge(G, S, E, distance, speed, traf_density);
            printf("Done!\n");
        }
        else if (Operation == 3)
        {
            Vertex S, E;
            printf("Enter Starting Vertex: ");
            scanf("%d", &S);
            printf("Enter Destination Vertex: ");
            scanf("%d", &E);

            DeleteEdge(G, S, E);
        }
        else if (Operation == 4)
        {
            printf("\n");
            PrintGraph(G);
        }
        else if (Operation == 5)
        {
            Vertex S, E;
            int H, M;

            printf("Enter Starting Vertex: ");
            scanf("%d", &S);
            printf("Enter Destination Vertex: ");
            scanf("%d", &E);
            printf("Enter time of travel (HH:MM): ");
            scanf("%d:%d", &H, &M);

            int time  = (H*60)+M;

            Node temp = G->VertexList[S]->NextNode;
            while (temp != NULL)
            {
                if (temp->VertexID == E)
                    break;
                
                temp = temp->NextNode;
            }

            if (temp != NULL)
            {
                float weight = GetWeight(G, G->VertexList[S], temp, time);
                printf("%g mins\n", weight);
            }
            else if (temp == NULL)
            {
                printf("No such road exists\n");
            }
        }

        printf("\n");
        printf("Operation Code: ");
        scanf("%d", &Operation);
    }

    return 0;
}
