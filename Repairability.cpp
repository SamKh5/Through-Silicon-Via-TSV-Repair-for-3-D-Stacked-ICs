// C++ program for implementation of Ford Fulkerson
// algorithm
#include<bits/stdc++.h>
using namespace std;

bool bfs(int V, vector<vector<float>>& rGraph, int s, int t, int parent[])
{

    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // BFS 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
               
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    return false;
}
 
float fordFulkerson(int V,vector<vector<float>>& graph, int source, int sink)
{
    int u, v;
 
    vector<vector<float>> rGraph( V , vector<float> (V));
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
 
    int parent[V]; // This array is filled by BFS and to
                   // store path
 
    float max_flow = 0; 
 
    while (bfs(V, rGraph, source, sink, parent)) {
        
        float path_flow = FLT_MAX;
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        max_flow += path_flow;
    }
 
    return max_flow;
}
 

int32_t main()
{
	int n;
	cout<<"Enter side length of grid : "<<endl;
	cin>>n;
	
	// total vertices in graph (V) = n*n + one source + one sink node
	int V = n*n + 2;
	
	int n_fault;
	cout<<"Enter the number of faulty TSV's : "<<endl;
    cin>>n_fault;
    
	vector<int> faulty;
	cout<<"Enter the faulty TSV's positions(row and coloumn number) : "<<endl;
	
	/*
	A 3X3 TSV Grid (flow is west to east and north to south)
	
	1--2--3
	|  |  |
	|  |  |
	4--5--6
	|  |  |
	|  |  |
	7--8--9
	
	For example if positions of faulty TSV's are 4,5,7 then the input to be given is -
	2 1
	2 2
	3 1
	
	*/
	
	for(int i=0;i<n_fault;i++) 
	{
		int x,y;
		cin>>x>>y;
		faulty.push_back(n*(x-1)+y);
	}
    
    vector<vector<float>> graph( V , vector<float> (V));
    for(int i=0;i<V;i++) for(int j=0;j<V;j++) graph[i][j]=0;
    
    // set up west to east flow
    for(int i=1;i<n*n;i+=n)
    {
      for(int j=i;j<i+n-1;j++)
      {
      	graph[j][j+1]=1;
      }
    }
    
    // set up north to south flow
    for(int i=1;i<=n;i++)
    {
      for(int j=i;j<n*n;j+=n)
      {
      	graph[j][j+n]=1;
      }
    }
    
    // set up diagonal flows
    
    for(int i=1;i<n;i++)
    {
    	for(int j=i;j<n*n;j+=(n+1))
    	{
    		graph[j][j+n+1]=1.414;
    	}
    }
    
    for(int i=1;i<n*n;i+=n)
    {
    	for(int j=i;j<n*n;j+=(n+1))
    	{
    		graph[j][j+n+1]=1.414;
    	}
    }
    /*
    A 3X3 TSV Grid with diagonal flows added 
	
	1--2--3
	|\ |\ |
	| \| \|
	4--5--6
	|\ |\ |
	| \| \|
	7--8--9
	
	*/
    
    // connect source node to faulty TSV's
    for(int i=0;i<n_fault;i++)
    {
    	graph[0][faulty[i]]=1;
    }
    
    // connect right and bottom boundary to sink node
    for(int i=n;i<=n*n;i+=n) graph[i][V-1]=1;
    for(int i=n*(n-1)+1;i<=n*n;i++) graph[i][V-1]=1;
  
    // find max flow of graph
    float max_flow = fordFulkerson(V, graph, 0, V-1);
    
    cout<<"maximum flow of TSV grid = "<<max_flow<<endl;
    
    if(max_flow == (float)n_fault) cout<<"TSV grid is repairable"<<endl;
    else cout<<"TSV grid is not repairable"<<endl;
 
    return 0;
}