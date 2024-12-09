#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "Graph.h"

// Test for parsing a CSV file
TEST_CASE("ParseCSV correctly reads movies", "[parser]") {
    std::vector<Movie> movies;
    parseCSV("test_data.csv", movies);

    REQUIRE(movies.size() == 2);
    REQUIRE(movies[0].title == "Inception");
    REQUIRE(movies[1].title == "Forrest Gump");
}

// Test for graph construction
TEST_CASE("Graph is constructed correctly", "[graph]") {
    std::vector<Movie> movies;
    parseCSV("test_data.csv", movies);

    std::unordered_map<int, int> actorToVertex;
    int currentIndex = 0;

    for (const auto& movie : movies) {
        for (const auto& actor : movie.cast) {
            if (actorToVertex.find(actor.id) == actorToVertex.end()) {
                actorToVertex[actor.id] = currentIndex++;
            }
        }
    }

    Graph graph(currentIndex);
    REQUIRE(graph.getVertexCount() == currentIndex);
}

