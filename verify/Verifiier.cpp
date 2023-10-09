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
bool isCyclicUtil(vertex* v, bool visited[], bool* recStack)
{
    if (visited[v->name] == false) {
        // Mark the current node as visited
        // and part of recursion stack
        visited[v->name] = true;
        recStack[v->name] = true;
 
        // Recur for all the vertices adjacent to this
        // vertex
        for (int i = 0; i < (v->adj.size()); ++i) {
            vertex* end = v->adj[i];
            if (!visited[end->name] && isCyclicUtil(end, visited, recStack))
                return true;
            else if (recStack[end->name])
                return true;
        }
    }
 
    // Remove the vertex from recursion stack
    recStack[v->name] = false;
    return false;
}

int main(int argc,  char **argv)
{
    string GraphGiven(argv[1]);
    string TreeGiven(argv[2]);
    //1. read in the given file and store edges in list
    ifstream in_s(GraphGiven);
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
        requiredVertices[a] = node;
    }   
    vector<map<int, int>>adjList;
    int startNode;
    int endNode;
    int weight;
    for(int a = 0; a < numEdges; a++){
        in_s >> startNode;
        in_s >> endNode;
        in_s >> weight;
        adjList[startNode][endNode] = weight;
        adjList[endNode][startNode] = weight;
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
    in_new >> numEdges;
    int totalCost;
    for(int a = 0; a < numEdgesGraph; a++){
        in_s >> startNode;
        in_s >> endNode;
        if(adjList[startNode].find(endNode) != adjList[startNode].end()){
            nodes[startNode]->adj.push_back(nodes[endNode]);
            nodes[endNode]->adj.push_back(nodes[startNode]);
            totalCost += adjList[startNode][endNode];
        }
        else{
            printf("Edge given not in list");
            return(1);
        }
    }
    if(totalCost != expectedCost){
        printf("total cost incorrect");
        return(1);
    }
    //4. check DFS
    bool* visited = new bool[numberNodes];
    bool* recStack = new bool[numberNodes];
    for (int i = 0; i < numberNodes; i++) {
        visited[i] = false;
        recStack[i] = false;
    }
    vertex * start = nodes[requiredVertices[0]];
    isCyclicUtil(start, visited, recStack);
    for(int i = 0; i<numReqVertices; i++){
        if(!visited[requiredVertices[i]]){
            printf("Required Vertex is not connected");
            return(1);
        }
    }
    printf("Graph is correct");
    return(0);
}