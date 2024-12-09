#ifndef MOVIEPARSER_H
#define MOVIEPARSER_H

#include <string>
#include <vector>

struct Actor {
    int cast_id;
    std::string character;
    std::string credit_id;
    int gender;
    int id;
    std::string name;
    int order;
};

struct Crew {
    std::string credit_id;
    std::string department;
    int gender;
    int id;
    std::string job;
    std::string name;
};

struct Movie {
    int movie_id;
    std::string title;
    std::vector<Actor> cast;
    std::vector<Crew> crew;
};

// Function declaration
void parseCSV(const std::string& filename, std::vector<Movie>& movies);

#endif // MOVIEPARSER_H

