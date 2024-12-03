#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

#include <nlohmann/json.hpp>
#include <rapidcsv.h>
// import a csv file to create a struct
// The header is movie_id, title, cast, crew
// the move_id is an integer
// the title is a string
// the cast is an array of objects
// the crew is an array of objects
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
  // vector<Crew> crew;
};

// Create a helper function which will help me create a vector of movies.
// The function will take in a string which is the path to the csv file
// The function will return a vector of movies
// The function will read the csv file and create a vector of movies
// The function will help parse each line to obtaine the Movie, Actor and Crew data
void parseCSV(const string& filename, std::vector<Movie>& movies) {
  // Load the CSV File
  rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));
  // Loop through each row and prin
  for(size_t i = 0; i < doc.GetRowCount(); ++i){
    // Parse the movie
    Movie movie;
    // Safely parse movie_id
    string:: movieIDStr = doc.GetCell<std::string>(0,i);
    try{
      movie.movie_id = std::stoi(movieIDStr);
    } catch(const std::invalid_argument& ia){
      std::err << "Error: Invalid movie_id at row: " << i << movieIDStr << "\n";
      continue;
    } catch(const std::out_of_rang& ia){
      std::err << "Error: Out of range movie_id at row: " << i << movieIDStr << "\n";
      continue;
    }
    movie.title = doc.GetCell<string>(1, i);
    // Parse the cast 
    string castJSON = json::parse(doc.GetCell<string>(2, i));
    for (auto& cast : castJSON) {
      Actor actor;
      actor.cast_id = cast["cast_id"];
      actor.character = cast["character"];
      actor.credit_id = cast["credit_id"];
      movie.cast.push_back(actor);
    }
    movies.push_back(movie);
    // Display parsed data
  }
    for (const auto& movie : movies) {
        std::cout << "Movie ID: " << movie.movie_id << "\n";
        std::cout << "Title: " << movie.title << "\n";
        std::cout << "Cast:\n";
        for (const auto& actor : movie.cast) {
            std::cout << "  - ID: " << actor.id
                      << ", Name: " << actor.name
                      << ", Character: " << actor.character << "\n";
        }
        std::cout << "--------------------------\n";
    }
}
int main(){
  std::vector<Movie> movies;
  const std::string filename = "./public/tmdb_5000_credits.csv";

  try {
    parseCSV(filename, movies);
    for (const auto& movie : movies) {
        std::cout << "Movie ID: " << movie.movie_id << "\n";
        std::cout << "Title: " << movie.title << "\n";
        std::cout << "Cast:\n";
        for (const auto& actor : movie.cast) {
            std::cout << "  - ID: " << actor.id
                      << ", Name: " << actor.name
                      << ", Character: " << actor.character << "\n";
        }
        std::cout << "--------------------------\n";
    }
  } catch (const std::exception& ex) {
      std::cerr << "Error: " << ex.what() << "\n";
  }

    // Loop through each row and print
  return 0;
}
