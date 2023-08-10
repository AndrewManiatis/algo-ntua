#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
using namespace std;
//DFS adapted from https://www.geeksforgeeks.org/connected-components-in-an-undirected-graph/
struct PairHash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& p) const {
        std::size_t hash1 = std::hash<T>()(p.first);
        std::size_t hash2 = std::hash<U>()(p.second);
        return hash1 ^ hash2;
    }
};
 
// Graph class represents a undirected graph
// using adjacency list representation
class Graph {
    int V; // No. of vertices
    // Pointer to an array containing adjacency lists
    list<int>* adj;
	int csize = 0;
    // A function used by DFS
    void DFSUtil(int v, bool visited[], int component[], int comp_index);
 
public:
    Graph(int V); // Constructor
    ~Graph();
    void addEdge(int v, int w);
    void connectedComponents(int component[], unordered_map<int, int>& component_size);
    unordered_map<int, std::unordered_set<int>> compSets;
    int max_comp_size;
    void printAdjList();
};
 
// Method to print connected components in an
// undirected graph
void Graph::connectedComponents(int component[], unordered_map<int, int>& component_size)
{
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int v = 0; v < V; v++)
        visited[v] = false;
        
 	int comp_index = 0;
 	
    for (int v = 0; v < V; v++) {
        if (visited[v] == false) {
            // print all reachable vertices
            // from v
            DFSUtil(v, visited, component, comp_index);
			component_size[comp_index] = this->csize;
			
			if(component_size[comp_index] > this->max_comp_size)
				this->max_comp_size = component_size[comp_index];
			this->csize = 0;
            comp_index += 1;
        }
    }
    delete[] visited;
}
 
void Graph::DFSUtil(int v, bool visited[], int component[], int comp_index)
{
    visited[v] = true;
    component[v] = comp_index;
    this->compSets[comp_index].insert(v);
    this->csize += 1;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
			DFSUtil(*i, visited, component, comp_index);
}
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    this->max_comp_size=0;
}
 
Graph::~Graph() { delete[] adj; }
 
// method to add an undirected edge
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
void Graph::printAdjList() {
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (auto v : adj[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
    
int main(){
	int minus = 0;
	int same = 0;
	int N;
	int F;
	cin >> N;
	cin >> F;
	Graph g(N);
	vector<int> P;
	
	vector<std::pair<int, int>> pairs;
	unordered_map<pair<int, int>, int, PairHash> pairCounts;
	
	int nloops=0;
	int nreps=0;

	for (int i=0; i<61; i+=2){
		int p1, p2;
		cin >> p1 >> p2;
		P.push_back(p1);
		P.push_back(p2);
		g.addEdge(P[i],P[i+1]);
	
		pair<int, int> new_pair = {p1,p2};
		if(p1==p2){
			same++;
			pairCounts[new_pair] +=1;
		}
		else{
		pair<int, int> revPair = {p2,p1};
		if (pairCounts.find(revPair) != pairCounts.end()) {
            minus++;
        }
        pairCounts[new_pair] +=1;
        //only count the first time it is repeated
        if(pairCounts[new_pair]==2){
        	minus++;
        }
        if(pairCounts[new_pair]>2)
        	minus++;
        }
	}
	int p63;
	cin >> p63;
	P.push_back(p63);
	
	int* component = new int[N];
	unordered_map<int, int> component_size;
    
	g.connectedComponents(component,component_size);
	
	int i = 62;
	int temp_max = g.max_comp_size;
	
	while((float)100*temp_max/N < (float) F){
		int first, second;
		if(i==62){
			first = P[i];
			second = ((P[++i-63]+P[i-31]) % N);
			P.push_back(second);
		}
		else{
			//produce next pair-contact
			first = ((P[++i-63]+P[i-31]) % N);
			P.push_back(first);
			second = ((P[++i-63]+P[i-31]) % N);
			P.push_back(second);
	}
		pair<int, int> new_pair = {first, second};
		pair<int, int> revPair = {second, first};
		if(first==second){
			same++;
			pairCounts[new_pair] +=1;
	}	else{
		if (pairCounts.find(revPair) != pairCounts.end()) {
            minus++;
        }
        pairCounts[new_pair] +=1;
        //only count the first time it is repeated
        if(pairCounts[new_pair]==2){
        	minus++;
        }
        if(pairCounts[new_pair]>2)
        	minus++;	
        	
		if(component[first] != component[second]){
			int small, large;
			
			if(component_size[component[first]] < component_size[component[second]]){
				small = component[first];
				large = component[second];
			}
			else{
				small = component[second];
				large = component[first];
		}
			//merge the two components / migrate all nodes of the small component to the large one for efficiency
			//update the size of the larger component
			component_size[large] += component_size[small];
			component_size[small] = 0;
			
			if(component_size[large]>temp_max)
				temp_max = component_size[large];
			
			//merge the two sets
			//change the label(component) of each "node"
			for (int value : g.compSets[small]){
				g.compSets[large].insert(value);
				component[value] = large;
			}
		}
	}
}
	
	for (const auto& pair_count : pairCounts) {
    	const auto& pair0 = pair_count.first;
    	const auto& count = pair_count.second;
    	pair<int, int> rev = {pair0.second, pair0.first};
    	
		if(count>1){
    		nreps++;
		}
		if (pair0.first!=pair0.second and pairCounts.find(rev) != pairCounts.end()){
    		nloops++;
		}
}
	
	cout << (int) i/2 - same - minus +1 << " " << minus << " " << same <<endl;

    return 0;	
}
