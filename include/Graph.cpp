#include "Graph.h"
#include <iostream>
#include <queue>

Graph::Graph(int numVertices) {
  this->numVertices = numVertices;
  adjList.resize(numVertices);
}

// Add edge to the graph
void Graph::addEdge(int src, int dest) {
  if(src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
    std::cerr << "Error: Invalid vertices for add Edge.\n";
  }
  adjList[src].push_back(dest);
  adjList[dest].push_back(src);
}

// Print the adjacency list representation of the graph
void Graph::printGraph() {
  for (int i = 0; i < numVertices; ++i) {
    std::cout << "Actor " << i << " has connections with: ";
    for (const auto& neighbor : adjList[i]) {
      std::cout << neighbor << " ";
    }
    std::cout << std::endl;
  } 
}

std::vector<std::pair<int, int>> Graph::calculateDegreeCentrality() const {
    std::vector<std::pair<int, int>> degreeCentrality;
    for (int i = 0; i < numVertices; ++i) {
        degreeCentrality.emplace_back(i, adjList[i].size());
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

        // std::cout << "Processing vertex: " << vertex << "\n"; // Debugging

        for (const auto& neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[vertex] + 1;

                // std::cout << "  Visiting neighbor: " << neighbor << ", Distance: " << distance[neighbor] << "\n"; // Debugging

                if (neighbor == endIndex) {
                    return distance[neighbor]; // Found the shortest path
                }

                q.push(neighbor);
            } else {
                // std::cout << "  Skipping visited neighbor: " << neighbor << "\n"; // Debugging
            }
        }
    }

    // If we exit the loop without finding the endIndex
    std::cerr << "No path exists between the specified vertices.\n";
    return -1;
}

void Graph::mergeSort(std::vector<std::pair<int, int>>& vec, int left, int right) const {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

void Graph::merge(std::vector<std::pair<int, int>>& vec, int left, int mid, int right) const {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::pair<int, int>> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = vec[left + i];
    for (int i = 0; i < n2; ++i) R[i] = vec[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].second >= R[j].second) {
            vec[k++] = L[i++];
        } else {
            vec[k++] = R[j++];
        }
    }
    while (i < n1) vec[k++] = L[i++];
    while (j < n2) vec[k++] = R[j++];
}

std::vector<std::pair<int, int>> Graph::getTopDegreeCentrality(int topN) const {
    // Get degree centrality
    std::vector<std::pair<int, int>> degreeCentrality = calculateDegreeCentrality();

    // Create a local copy of the vector for sorting
    std::vector<std::pair<int, int>> sortedDegreeCentrality = degreeCentrality;

    // Sort the vector in descending order based on degree
    mergeSort(sortedDegreeCentrality, 0, sortedDegreeCentrality.size() - 1);

    // Return the top N elements
    return std::vector<std::pair<int, int>>(sortedDegreeCentrality.begin(),
                                            sortedDegreeCentrality.begin() + std::min(topN, (int)sortedDegreeCentrality.size()));
}

