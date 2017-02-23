#include<iostream>
#include<sys/time.h>
using namespace std;
  
// Number of vertices in the graph
const int V=12;
  
// A function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
   int min = INT_MAX, min_index;
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
   return min_index;
}
  
// A function to print the constructed distance array
int printSolution(int dist[], int n,int src)
{
	cout<<"\n\n For node "<<src<<endl;
   	for (int i = 0; i < V; i++)
      cout<<"\t\nTo node "<<i<<"\tDistance is "<<dist[i];
}
  
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
     int dist[V];     
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
  
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
  
     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
  
       // Mark the picked vertex as processed
       sptSet[u] = true;
  
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)
  
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
     printSolution(dist, V,src);
}

int main()
{
	struct timeval tv1,tv2;
   	int graph[V][V] = {{0,1,1,0,0,0,0,0,0,0,0,0},
						{1,0,1,1,0,0,0,0,0,0,0,0},
						{1,1,0,0,0,0,0,0,0,0,0,1},
						{0,1,0,0,1,1,0,0,0,0,0,0},
						{0,0,0,1,0,0,1,0,0,0,0,0},
						{0,0,0,1,0,0,1,0,0,0,0,0},
						{0,0,0,0,1,1,0,1,0,0,0,0},
						{0,0,0,0,0,0,1,0,1,1,0,0},
						{0,0,0,0,0,0,0,1,0,0,0,1},
						{0,0,0,0,0,0,0,1,0,0,1,0},
						{0,0,0,0,0,0,0,0,0,1,0,1},
						{0,0,1,0,0,0,0,0,1,0,1,0},
					};
	gettimeofday(&tv1,NULL);
  	for(int i=0;i<V;i++)
    	dijkstra(graph, i);
  	gettimeofday(&tv2,NULL);
    cout<<endl<<tv2.tv_usec<<endl<<tv1.tv_usec;
	cout<<"\nTotal time taken : "<<(double)(tv2.tv_usec-tv1.tv_usec);
    return 0;
}
