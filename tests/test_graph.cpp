#include <catch2/catch.hpp>
#include "Graph.h"

TEST_CASE("Graph calculates degree centrality correctly", "[graph]") {
    Graph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);

    auto centrality = graph.calculateDegreeCentrality();
    REQUIRE(centrality[0] == 1);
    REQUIRE(centrality[1] == 2);
    REQUIRE(centrality[2] == 1);
}

// Test for degree centrality
void testDegreeCentrality() {
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

    for (const auto& movie : movies) {
        for (size_t i = 0; i < movie.cast.size(); ++i) {
            for (size_t j = i + 1; j < movie.cast.size(); ++j) {
                int actor1 = actorToVertex[movie.cast[i].id];
                int actor2 = actorToVertex[movie.cast[j].id];
                graph.addEdge(actor1, actor2);
            }
        }
    }

    auto degreeCentrality = graph.calculateDegreeCentrality();
    assert(degreeCentrality.size() == 3);
    assert(degreeCentrality[actorToVertex[6193]] == 1); // Leonardo DiCaprio
    assert(degreeCentrality[actorToVertex[6195]] == 0); // Tom Hanks

    std::cout << "testDegreeCentrality passed!" << std::endl;
}

// Test shortest path
void testShortestPath() {
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

    for (const auto& movie : movies) {
        for (size_t i = 0; i < movie.cast.size(); ++i) {
            for (size_t j = i + 1; j < movie.cast.size(); ++j) {
                int actor1 = actorToVertex[movie.cast[i].id];
                int actor2 = actorToVertex[movie.cast[j].id];
                graph.addEdge(actor1, actor2);
            }
        }
    }

    int start = actorToVertex[6193]; // Leonardo DiCaprio
    int end = actorToVertex[6195];   // Tom Hanks

    int degree = graph.shortestDegreeOfSeparation(start, end);
    assert(degree == -1); // No connection between Inception and Forrest Gump

    std::cout << "testShortestPath passed!" << std::endl;
}
