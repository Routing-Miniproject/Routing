# Routing - Mini Project

## Objective
---
    Improving Google Map's shortest path algorithm by implementing Dijkstra Algorithm with revised weightages to take into account indeterminable events like marriage processions while travelling.


## Calculating weightages
---
### Dataset Provided:
     1. Intersections
     2. Roads
     3. Traffic Density/Flow
     4. Traffic light data
     5. Number of paths from a node
     6. Marraige Season and usual time of occurence of processions
     7. Speed limits
     8. Number of roads from an intersection

### User Input Data:
     1. Start(vertex ID -integer)
     2. Destination(vertex ID -integer)
     3. Time(only hour -integer)
     
### Formulas Used:

### Text File format:

The first line contains an integer |V| denoting the number of intersection(nodes). The ID of each intersection is between 0 and |V| - 1.
The next |V| lines contain an integer denoting the time delay caused by a traffic light on each node(the value is 0 if there is no traffic light).
The next line contains an integer |E| denoting the number of roads(edges). The next |E| lines contains 2 space seperated integers denoting the start and end nodes of the road.
Each of the next |E| lines contains the traffic contains a floating number denoting the traffic density of the corresponding road.
Each of the next |E| lines contains an integer denoting the number of turns present in the corresponding road.
Each of the next |E| lines contains a floating point denoting the average number of marriages in that given road.
Each of the next |E| lines contains a boolean value, such that 1 denotes the corresponding road is inside the city and 0 otherwise.
Each of the next |E| lines contains an integer denoting the average speed with which any vehicle travels on the corresponding road.
