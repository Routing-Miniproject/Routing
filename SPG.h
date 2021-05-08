#ifndef _SPG_
#define _SPG_

#include <stdio.h>
#include <stdlib.h>

typedef struct SPG SPG;

struct SPG
{
    int parent;
    float distance_from_source;
};

// FUNCTIONS

void display_SPG(SPG *Result[], int destination_id, int V);

#endif