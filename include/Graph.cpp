#include "Graph.h"
#include <iostream>
#include <queue>

Graph::Graph(int numVertices) {
  this->numVertices = numVertices;
  adjList.resize(numVertices);
}

// Add edge to the graph
void Graph::addEdge(int src, int dest) {
  adjList[src].push_back(dest);
  adjList[dest].push_back(src);
}

// Print the adjacency list representation of the graph
void Graph::printGraph() {
  for (int i = 0; i < numVertices; ++i) {
    std::cout << "Vertex " << i << " has the following neighbors: ";
    for (const auto& neighbor : adjList[i]) {
      std::cout << neighbor << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<int> Graph::calculateDegreeCentrality() const {
  std::vector<int> degreeCentrality(numVertices, 0);
  for (int i = 0; i < numVertices; ++i) {
    degreeCentrality[i] = adjList[i].size();
  }
  return degreeCentrality;
}

bool Graph::isConnected() const {
  std::vector<bool> visited(numVertices, false);
  DFS(0, visited);
  for (const auto& vertex : visited) {
    if (!vertex) {
      return false;
    }
  }
  return true;
}

int Graph::countConnectedComponents() const {
  std::vector<bool> visited(numVertices, false);
  int count = 0;
  for (int i = 0; i < numVertices; ++i) {
    if (!visited[i]) {
      DFS(i, visited);
      count++;
    }
  }
  return count;
}

void Graph::DFS(int vertex, std::vector<bool>& visited) const {
  visited[vertex] = true;
  for (const auto& neighbor : adjList[vertex]) {
    if (!visited[neighbor]) {
      DFS(neighbor, visited);
    }
  }
}

// Shortest Degree of Separation
int Graph::shortestDegreeOfSeparation(int startIndex, int endIndex) const {
    if (startIndex == endIndex) {
        return 0; // Same vertex.
    }

    // Validate indices
    if (startIndex < 0 || startIndex >= numVertices || endIndex < 0 || endIndex >= numVertices) {
        std::cerr << "Error: Invalid startIndex or endIndex.\n";
        return -1;
    }

    // Ensure adjacency list is not empty
    if (adjList.empty()) {
        std::cerr << "Error: Adjacency list is empty.\n";
        return -1;
    }

    std::queue<int> q;
    std::vector<bool> visited(numVertices, false);
    std::vector<int> distance(numVertices, -1); // Initialize distances as -1

    // Start BFS
    q.push(startIndex);
    visited[startIndex] = true;
    distance[startIndex] = 0;

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        std::cout << "Processing vertex: " << vertex << "\n"; // Debugging

        for (const auto& neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[vertex] + 1;

                std::cout << "  Visiting neighbor: " << neighbor << ", Distance: " << distance[neighbor] << "\n"; // Debugging

                if (neighbor == endIndex) {
                    return distance[neighbor]; // Found the shortest path
                }

                q.push(neighbor);
            } else {
                std::cout << "  Skipping visited neighbor: " << neighbor << "\n"; // Debugging
            }
        }
    }

    // If we exit the loop without finding the endIndex
    std::cerr << "No path exists between the specified vertices.\n";
    return -1;
}

