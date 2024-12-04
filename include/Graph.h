#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

class Graph {
public:
  Graph(int numVertices);
  void addEdge(int v, int w);
  // void BFS(int s);
  void printGraph();
  std::vector<int> calculateDegreeCentrality() const;
  
  // Function to check if the graph is connected;
  bool isConnected() const;

  // Function to determine the number of connected components.
  int countConnectedComponents() const;

  // Shortest path between any two vertices
  int shortestDegreeOfSeparation(int startIndex, int endIndex) const;

private:
  int numVertices;
  std::vector<std::list<int>> adjList;
  void DFS(int vertex, std::vector<bool>& visited) const;
};

#endif // GRAPH_H
