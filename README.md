# Routing - Mini Project

## Objective
---
    Improving Google Map's shortest path algorithm by implementing Dijkstra Algorithm with revised weightages to take into account indeterminable events like marriage processions while travelling.


## Calculating weightages
---
### Dataset Provided:
     1. Intersections (nodes)
     2. Roads (edges)
     3. Length of the road
     4. Traffic Density/Flow
     5. Time delay due to traffic signals
     6. Marraige Season - depicts the presence of function halls 
     7. Speed limits

### User Input Data:
     1. Start(vertex ID -integer)
     2. Destination(vertex ID -integer)
     3. Time(only hour -integer)
     
### Formulas Used:

### Text File format:

- The first line contains an integer |V| denoting the number of intersection(nodes). The ID of each intersection is between 0 and |V| - 1.
- The next |V| lines contain an integer denoting the time delay caused by a traffic light on each node(the value is 0 if there is no traffic light).
- The next |V| lines contain a boolean value for each node denoting the presence of function halls (0 for none and 1 if any present).
- The next line contains an integer |E| denoting the number of roads(edges). 
- The next |E| lines contains 2 space seperated integers denoting the start and end vertices of the road.
- The next |E| lines contains 3 space seperated floating point values denoting the length (in meters), the traffic density (number of cars per kilometers) and the     speed limit (in kmph) of the given road.
