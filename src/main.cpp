#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

#include "Graph.h"
#include "MovieParser.h"

#include <nlohmann/json.hpp>
#include <rapidcsv.h>

using namespace std;
int main() {
  vector<Movie> movies;
  const string filename = "./public/tmdb_5000_credits.csv";
  parseCSV(filename, movies);
  unordered_map<int, int> actorToVertex;
  unordered_map<int, string> vertexToActorName; // For mapping back to names
  int currentIndex = 0;
  // Construct an adjacency list where the vertices are actors and the edges are movies
  try {
      for (const auto& movie : movies) {
        for (const auto& actor : movie.cast) {
            if (actorToVertex.find(actor.id) == actorToVertex.end()) {
                actorToVertex[actor.id] = currentIndex;
                vertexToActorName[actor.id] = actor.name;
                currentIndex++;
            }
        }
    }

    // 2. Create the graph and add edges
    // This graph is for the actors
    Graph graph(currentIndex);
    for (const auto& movie : movies) {
      for (size_t i = 0; i < movie.cast.size(); ++i) {
          for (size_t j = i + 1; j < movie.cast.size(); ++j) {
              int actor1 = actorToVertex[movie.cast[i].id];
              int actor2 = actorToVertex[movie.cast[j].id];
              graph.addEdge(actor1, actor2);
          }
      }
    }

    graph.printGraph();

    std::vector<std::pair<int,int>> degreeCentrality = graph.calculateDegreeCentrality();
      
    // Determine if the graph is connected
    if (graph.isConnected()) {
      cout << "The graph is connected." << endl;
    } else {
      cout << "The graph is not connected." << endl;
    }

    // Determine the number of connected components
    int numConnectedComponents = graph.countConnectedComponents();
    cout << "The number of connected components is " << numConnectedComponents << endl;


    // Create an actorToIndex map
    std::unordered_map<std::string, int> actorToIndex;
    for (size_t i = 0; i < movies.size(); ++i) {
      for (const auto& actor : movies[i].cast) {
      actorToIndex[actor.name] = actor.id;
      }
    }

    std::string actor1 = "Leonardo DiCaprio";
    std::string actor2 = "Tom Hanks";
  
    int start = actorToIndex[actor1];
    int end = actorToIndex[actor2];

    int degree = graph.shortestDegreeOfSeparation(start, end);

    if(degree != -1) {
      cout << "The shortest path between " << actor1 << " and " << actor2 << " is " << degree << endl;
    } else {
      cout << "There is no path between " << actor1 << " and " << actor2 << endl;
    }

    cout << "Top 5 actors with the highest degree centrality are: " << endl;
    auto top5 = graph.getTopDegreeCentrality(5);
    std::cout << "Top 5 actors by degree centrality:\n";
        // Print sorted results
    for (const auto& pair : top5) {
        std::cout << "Actor ID: " << pair.first << ", Degree Centrality: " << pair.second << std::endl;
        std::cout << "Actor Name: " << vertexToActorName[pair.first] << std::endl;
    }

      

  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  } 


  return 0;
}

