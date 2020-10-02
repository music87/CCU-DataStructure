In this program, you should input what algorithm you want to implement.
1 represent finding a graph’s minimum spanning tree with Kruskal algorithm, and program will show the edge , two vertices on it and the weight in processing order.
2 represent finding a graph’s minimum spanning tree with Prim algorithm, and program will show the edge , two vertices on it and the weight in processing order.
3 represent finding a graph’s shortest path between any two vertices by Dijkstra algorithm, and program will show the minimum cost between them.User should input the start and end vertices.

Here are the core concept over these three algorithms.

Kruskal algorithm
1.Read graph with “adjacency matrix” and “build a min heap” to store the edge’s weight and two vertices incident on it.Default every vertex is an independent tree/subset and using “subset’s array representation” to store them.
2.”Pop min heap” to get the edge with smallest weight and print it.
3.Check whether the two vertices which is incident by the edge picking from step 2 is in the same tree ,which means checking in the same subset or not by “collapsing finding” their root are same or not.
If two vertices are in the same subset, skip it to prevent creating cycle.
Else “union” them by weighted union.
4.Repeat step2 and step3 until the min heap is empty.

Prim algorithm
1.Read graph with adjacency matrix.Default every vertex’s from edge’s weight is oo,from vertex is -1, and has not been visited yet.
2.Scan all vertices’ from edge’s weight and pick the minimal one.
3.Visit the picking vertex from step2 and print it.
4. If the vertex is adjacency to the picking vertex ,has not been visited yet, and the edge’s weight between them < the vertex’s from edge’s weight,then,update vertex’s from edge’s weight and from vertex.
5.Repeat step2 , step3 ,and step4 until all vertices have been visited.

Dijkstra algorithm
1.Read graph with adjacency matrix.Default every vertex’s distance from source vertex is oo,through vertex is -1, and has not been visited yet.
2.Choose the source vertex.Update the distance whose vertex is adjacency to the source ,let it change to the edge’s weight.
3.Scan all vertices’ distance and pick the minimal one.
4.Visit the picking vertex from step3.
5. If the vertex is adjacency to the picking vertex ,has not been visited yet, and (picking vertex’s distance + edge’s weight between picking vertex and the vertex meeting the criteria) < the vertex meeting the criteria ’s distance ,then,update the vertex meeting the criteria ’s distance and from vertex.
6.Repeat step3 ,step4, and step5 until all vertices have been visited.


