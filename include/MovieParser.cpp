#include "MovieParser.h"
#include <rapidcsv.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

void parseCSV(const std::string& filename, std::vector<Movie>& movies) {
    try {
        rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));

        for (size_t i = 1; i < doc.GetRowCount(); ++i) {
            try {
                // Parse Movie
                Movie movie;
                movie.movie_id = stoi(doc.GetCell<std::string>(0, i));
                movie.title = doc.GetCell<std::string>(1, i);

                // Parse Cast JSON
                std::string castJsonStr = doc.GetCell<std::string>(2, i);
                json castJson = json::parse(castJsonStr);

                for (const auto& cast : castJson) {
                    Actor actor;
                    actor.cast_id = cast.at("cast_id").get<int>();
                    actor.character = cast.at("character").get<std::string>();
                    actor.credit_id = cast.at("credit_id").get<std::string>();
                    actor.gender = cast.value("gender", -1); // Optional
                    actor.id = cast.at("id").get<int>();
                    actor.name = cast.at("name").get<std::string>();
                    actor.order = cast.at("order").get<int>();
                    movie.cast.push_back(actor);
                }

                // Parse Crew JSON
                std::string crewJsonStr = doc.GetCell<std::string>(3, i);
                json crewJson = json::parse(crewJsonStr);

                for (const auto& crew : crewJson) {
                    Crew crewmember;
                    crewmember.credit_id = crew.at("credit_id").get<std::string>();
                    crewmember.department = crew.at("department").get<std::string>();
                    crewmember.job = crew.at("job").get<std::string>();
                    crewmember.name = crew.at("name").get<std::string>();
                    movie.crew.push_back(crewmember);
                }

                movies.push_back(movie);

            } catch (const json::parse_error& e) {
                std::cerr << "JSON Parsing Error at row " << i << ": " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error processing row " << i << ": " << e.what() << std::endl;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error reading CSV file: " << e.what() << std::endl;
    }
}

