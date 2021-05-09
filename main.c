#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date_time.h"
#include "graph.h"
#include "SPG.h"

int main()
{
    Graph G = getmap(); //generate_map
    int V = G->NumVertex;

    /* Considering the vertices names to be characters from a to z */
    char source, destination;
    date_time D;

    printf("Enter the following information:\n"); // Taking input of source, destination, date and time from the user
    printf("Starting Point: ");
    scanf("%c", &source);
    printf("Destination: ");
    scanf("%c", &destination);
    printf("Time: "); // hours:minutes (24-hr format)
    scanf("%d:%d", &D.hours, &D.minutes);
    printf("Date: "); // dd/mm format
    scanf("%d/%d", &D.day, &D.month);

    weightage_calculator(D); // uses the map data and also checks the time and date to calculate and store optimised weightages into the edge data

    int source_id = source - 'a';           // Converting the vertex names to int since
    int destination_id = destination - 'a'; // algorithm handles vertices in form on int

    SPG **Result = dijkstra(G, source); // Passing graph and source node as parameters and returns a structure (SPG)
                                        // which consists of distance from source, parent data for each vertex

    display_SPG(Result, destination_id, V); // Function which prints the shortest path graph, in basic form (i.e. A-->B-->E-->T)
                                            // and also the total time taken and total distance to be travelled to reach the destination

    return 0;
}
