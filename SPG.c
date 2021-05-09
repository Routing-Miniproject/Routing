#include "SPG.h"

void display_SPG(SPG *Result[], int destination_id, int V)
{
    float total_distance = Result[destination_id]->distance_from_source;
    int path[V];
    int idx = destination_id;
    int i = 0;
    while (Result[idx]->parent != idx)
    {
        path[i] = idx;
        idx = Result[idx]->parent;
        i++;
    }
    for (int k = i; k > 0; k--)
    {
        printf("%d-->", path[i]);
    }
    printf("%d\n", path[0]);
    printf("Total Distance: %f m\n", total_distance);
}
