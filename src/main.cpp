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

  try {
    parseCSV(filename, movies);

    // Map actor names to their IDs
    std::unordered_map<std::string, int> actorToIndex;
    for (const auto& movie : movies) {
      for (const auto& actor : movie.cast) {
        actorToIndex[actor.name] = actor.id;
      }
    }
    // Create a graph where vertices are actors and edges are their co-acting relationships

    // Create the graph
    Graph graph(actorToIndex.size()); // Pass the number of unique actors as the argument
    for (const auto& movie : movies) {
      const auto& cast = movie.cast;
      for (size_t i = 0; i < cast.size(); ++i) {
        for (size_t j = i + 1; j < cast.size(); ++j) {
          graph.addEdge(cast[i].id, cast[j].id);
        }
      }
    }

    // Print graph info
    graph.printGraph();

    // Degree centrality
    std::vector<int> degreeCentrality = graph.calculateDegreeCentrality();
    for (size_t i = 0; i < degreeCentrality.size(); ++i) {
      cout << "Actor " << i << " has degree centrality " << degreeCentrality[i] << endl;
    }

    // Check connectivity
    if (graph.isConnected()) {
      cout << "The graph is connected." << endl;
    } else {
      cout << "The graph is not connected." << endl;
    }

    int numConnectedComponents = graph.countConnectedComponents();
    cout << "The number of connected components is " << numConnectedComponents << endl;

    // Map actor names to IDs
    std::unordered_map<int, string> actorMap;
    for (const auto& movie : movies) {
      for (const auto& actor : movie.cast) {
        actorMap[actor.id] = actor.name;
      }
    }

    // Actors for shortest path calculation
    std::string actor1 = "Ving Rhames";
    std::string actor2 = "Leonardo DiCaprio";

    int start = actorToIndex[actor1];
    int end = actorToIndex[actor2];

    cout << "The start index is " << start << " and the end index is " << end << endl;

    int degree = graph.shortestDegreeOfSeparation(start, end);

    if (degree != -1) {
      cout << "The shortest path between " << actor1 << " and " << actor2 << " is " << degree << endl;
    } else {
      cout << "There is no path between " << actor1 << " and " << actor2 << endl;
    }

  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }

  return 0;
}

