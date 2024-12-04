#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

#include "Graph.h"

#include <nlohmann/json.hpp>
#include <rapidcsv.h>

using namespace std;
using json = nlohmann::json;

struct Actor {
  int cast_id;
  string character;
  string credit_id;
  int gender;
  int id;
  string name;
  int order;
};

struct Crew {
  string credit_id;
  string department;
  int gender;
  int id;
  string job;
  string name;
};

struct Movie {
  int movie_id;
  string title;
  vector<Actor> cast;
  vector<Crew> crew;
};

void parseCSV(const string& filename, vector<Movie>& movies) {
  try {
    rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));

    for (size_t i = 1; i < doc.GetRowCount(); ++i) {
      try {
        // Parse Movie
        Movie movie;
        movie.movie_id = stoi(doc.GetCell<string>(0, i));
        movie.title = doc.GetCell<string>(1, i);

        // Parse Cast JSON
        string castJsonStr = doc.GetCell<string>(2, i);
        json castJson = json::parse(castJsonStr);

        for (const auto& cast : castJson) {
          Actor actor;
          actor.cast_id = cast.at("cast_id").get<int>();
          actor.character = cast.at("character").get<string>();
          actor.credit_id = cast.at("credit_id").get<string>();
          actor.gender = cast.value("gender", -1); // Optional
          actor.id = cast.at("id").get<int>();
          actor.name = cast.at("name").get<string>();
          actor.order = cast.at("order").get<int>();
          movie.cast.push_back(actor);
        }
        // Parse Crew JSON
        string crewJsonStr = doc.GetCell<string>(3, i);
        json  crewJson = json::parse(crewJsonStr);

        for(const auto& crew : crewJson) {
          Crew crewmember;
          crewmember.credit_id = crew.at("credit_id").get<string>();
          crewmember.department = crew.at("department").get<string>();
          crewmember.job = crew.at("job").get<string>();
          crewmember.name = crew.at("name").get<string>();
          movie.crew.push_back(crewmember);
        }

        movies.push_back(movie);

      } catch (const json::parse_error& e) {
        cerr << "JSON Parsing Error at row " << i << ": " << e.what() << endl;
      } catch (const exception& e) {
        cerr << "Error processing row " << i << ": " << e.what() << endl;
      }
    }

  } catch (const exception& e) {
    cerr << "Error reading CSV file: " << e.what() << endl;
  }
}

int main() {
  vector<Movie> movies;
  const string filename = "./public/tmdb_5000_credits.csv";

  // Construct an adjacency list where the vertices are actors and the edges are movies
  try {
    parseCSV(filename, movies);

    // 1. Create a map of actors to movie indices
    std::unordered_map<int, std::vector<int>> actorToMovies;
    for (size_t i = 0; i < movies.size(); ++i) {
      for (const auto& actor : movies[i].cast) {
        actorToMovies[actor.id].push_back(i); 
      }
    }

    // 2. Create the graph and add edges
    Graph graph(movies.size());
    for (const auto& [actorId, movieIndices] : actorToMovies) {
      for (size_t i = 0; i < movieIndices.size(); ++i) {
        for (size_t j = i + 1; j < movieIndices.size(); ++j) {
          graph.addEdge(movieIndices[i], movieIndices[j]);
        }
      }
    }

    graph.printGraph();

    std::vector<int> degreeCentrality = graph.calculateDegreeCentrality();
    for (size_t i = 0; i < degreeCentrality.size(); ++i) {
      // print the name of the actor
      cout << "Actor " << i << " has degree centrality " << degreeCentrality[i] << endl;
    }
      
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
    std::string actor2 = "Jack Nicholson";
  
    int start = actorToIndex[actor1];
    int end = actorToIndex[actor2];

    int degree = graph.shortestDegreeOfSeparation(start, end);

    if(degree != -1) {
      cout << "The shortest path between " << actor1 << " and " << actor2 << " is " << degree << endl;
    } else {
      cout << "There is no path between " << actor1 << " and " << actor2 << endl;
    }
      

  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  } 


  return 0;
}

