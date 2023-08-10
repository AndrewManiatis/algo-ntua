#include<iostream>
#include<vector>
#include<set>

#include <bits/stdc++.h>  
using namespace std;
typedef pair<int,unsigned long long> PII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

//dijkstra implementation
//https://www.algotree.org/algorithms/single_source_shortest_path/dijkstras_shortest_path_c++/
vector<unsigned long long> DijkstrasShortestPath (int source_node, int node_count, VVPII& graph) {

    // Assume that the distance from source_node to other nodes is infinite 
    // in the beginnging, i.e initialize the distance vector to a max value
    const long long INF = 1e8;
    vector<unsigned long long> dist(node_count, INF);
    set<PII> set_length_node;
    
    // Distance from starting vertex to itself is 0
    dist[source_node] = 0;
    set_length_node.insert(PII(0,source_node));

    while (!set_length_node.empty()) {

        PII top = *set_length_node.begin();
        set_length_node.erase(set_length_node.begin());

        int current_source_node = top.second;

        for (auto& it : graph[current_source_node]) {

            int adj_node = it.first;
            int length_to_adjnode = it.second;
    
            // Edge relaxation 
            if (dist[adj_node] > length_to_adjnode + dist[current_source_node]) {
    
                // If the distance to the adjacent node is not INF, means the pair <dist, node> is in the set
                // Remove the pair before updating it in the set.
                if (dist[adj_node] != INF) {
                   set_length_node.erase(set_length_node.find(PII(dist[adj_node],adj_node))); 
                }
                dist[adj_node] = length_to_adjnode + dist[current_source_node];
                set_length_node.insert(PII(dist[adj_node], adj_node));
            }
        }
    }   
    return dist;
}

int main(){
	const long long INF = 1e8;
	
    int N, M; // number of nodes and number of edges  
    int s,t; //start and end node  
    int B;  
    cin >> N >> M >> s >> t >> B; // read input 
		
	int node_count = N*N;
    vector<VPII> graph(node_count, VPII());
    
    for (int i = 0; i < M; i++) {  
        int u, v, w;  
        cin >> u >> v >> w;  
          
        //edges between states with the same number of nullified edges  
        for (int k = 0; k < N; k++){  
			graph[u+k*N-1].push_back(make_pair(v+k*N-1, w));
        }  
        //edges between states with a difference of one nullified edges  
        for (int k = 1; k < N; k++){  
            graph[u+(k-1)*N-1].push_back(make_pair(v+k*N-1, 0)); 
        }               
    }
    
    vector<unsigned long long> dist(node_count, INF);   
    dist = DijkstrasShortestPath(s-1, node_count, graph);
    
    // if a path with j nullified edges has 0 cost then we accept that a path with j+1 will also need to have 0 cost
    for (int i=0; i<node_count; i++){
    	if(dist[i]==0){
    		int j = i;
			while(j<node_count-N){
				j += N;
				dist[j]=0;
			}    		
		}
	}

	//binary search for minimum number ïf zero edges
    int L=0;  
    int R=N-1;  
    while(L<R){  
        int m = (L+R)/2;  
        if (B < dist[t+m*N-1]){  
            L = m+1;  
        }  
        else{  
            R = m;  
        }  
    } 
    cout <<R<<endl;  
    return 0;
}
