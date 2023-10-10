#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <map>

using namespace std;

struct vertex {
    vector<vertex*> adj; //cost of edge, destination vertex
    int name;
    vertex(int s) : name(s) {}
};
//return true if graph contains cycle
bool isCyclicUtil(vector<vertex*> nodes, vertex * v, bool visited[], int parent)
{
 
    // Mark the current node as visited
    visited[v->name] = true;
 
    // Recur for all the vertices
    // adjacent to this vertex
    for (auto i : v->adj) {
 
        // If an adjacent vertex is not visited,
        // then recur for that adjacent
        if (!visited[i->name]) {
            if (isCyclicUtil(nodes, i, visited, v->name))
                return true;
        }
 
        // If an adjacent vertex is visited and
        // is not parent of current vertex,
        // then there exists a cycle in the graph.
        else if (i->name != parent)
            return true;
    }
    return false;
}
void addEdge(vector <pair<int, int> > adj[], int u,
                                     int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}


int main(int argc,  char **argv)
{
    string GraphGiven(argv[1]);
    string TreeGiven(argv[2]);
    //1. read in the given file and store edges in list
    ifstream in_s;
    in_s.open (GraphGiven, ifstream::in);
    int numberNodes;
    int numEdges;
    int numReqVertices;
    in_s >> numberNodes;
    in_s >> numEdges;
    in_s >> numReqVertices;
    vector<int> requiredVertices(numReqVertices);  
    for(int a = 0; a < numReqVertices; a++){
        int node;
        in_s >> node;
        requiredVertices[a] = node-1;
    }   
    vector<pair<int, int> > adj[numberNodes];
    int startNode;
    int endNode;
    int weight;
    for(int a = 0; a < numEdges; a++){
        in_s >> startNode;
        in_s >> endNode;
        in_s >> weight;
        addEdge(adj, startNode-1, endNode-1, weight);
    }
    //2. create all nodes from given file
    vector<vertex*> nodes(numberNodes);
    for(int a = 0; a < numberNodes; a++){
        vertex *v;
        v = new vertex(a);
        nodes[a] = v;
    }
    //3. make paths from given tree and check paths are valid + weight
    ifstream in_new(TreeGiven);
    int expectedCost;
    in_new >> expectedCost;
    int numEdgesGraph;
    in_new >> numEdgesGraph;
    int totalCost = 0;
    for(int a = 0; a < numEdgesGraph; a++){
        in_new >> startNode;
        startNode -= 1;
        in_new >> endNode;
        endNode -= 1;
        int weightGiven = -1;
        for(auto it = adj[startNode].begin(); it!=adj[startNode].end(); it++ ){ 
            if(it->first == endNode){ 
                weightGiven = it->second; 
            }
        }
        if(weightGiven != -1){
            nodes[startNode]->adj.push_back(nodes[endNode]);
            nodes[endNode]->adj.push_back(nodes[startNode]);
            totalCost += weightGiven;
            cout << startNode << " " << weightGiven << " " << totalCost << "\n";
        }
        else{
            printf("Edge given not in list \n");
            return(0);
        }
    }
    if(totalCost != expectedCost){
        printf("total cost incorrect \n");
        return(0);
    }
    //4. check DFS
    bool* visited = new bool[numberNodes];
    for (int i = 0; i < numberNodes; i++) {
        visited[i] = false;
    }
    vertex * start = nodes[requiredVertices[0]];
    if(isCyclicUtil(nodes, start, visited, -1)){
        printf("Cycle detected\n");
        return(0);
     }
    for(int i = 0; i<numReqVertices; i++){
        if(!visited[requiredVertices[i]]){
            printf("Required Vertex is not connected\n");
            return(0);
        }
    }
    printf("Graph is correct\n");
    return(0);
}