#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date_time date_time;         // A simple data structure to store the date and time of travel
struct date_time
{
    int day;
    int month;
    int hours;
    int minutes;
};