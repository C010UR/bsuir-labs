#include "dijsktra.hpp"
#include "floyd.hpp"
#include "graph.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector>

int main(void)
{
    // Some random C++ bullsh*t
    std::random_device rd;
    // seed value is designed specifically to make initialization
    // parameters of std::mt19937 (instance of std::mersenne_twister_engine<>)
    // different across executions of application
    std::mt19937::result_type seed =
        rd()
        ^ ((std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::system_clock::now().time_since_epoch())
               .count()
           + (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(
                 std::chrono::high_resolution_clock::now().time_since_epoch())
                 .count());

    std::mt19937 gen(seed);

    std::uniform_int_distribution<Graph::cost_t> location_distribution(1, 12);
    std::uniform_real_distribution<double>       percentage_distribution(0, 1);

    std::cout << "Enter amount of edges: ";

    unsigned edges_amount;
    std::cin >> edges_amount;

    std::cout << "Enter chance of an edge: ";

    double edge_chance;
    std::cin >> edge_chance;

    std::vector<std::vector<Graph::cost_t>> matrix(edges_amount);

    for (unsigned i = 0; i < edges_amount; i++) {
        // matrix.push_back(std::vector<Graph::cost_t>(edges_amount));

        for (unsigned j = 0; j < edges_amount; j++) {
            if (i != j && percentage_distribution(gen) <= edge_chance) {
                matrix[i].push_back(location_distribution(gen));
            } else {
                matrix[i].push_back(std::numeric_limits<typename Graph::cost_t>::max());
            }
        }
    }

    Graph graph(matrix);

    std::cout << "Graph: " << std::endl;
    graph.show();

    Graph::location_t start = 0;

    std::cout << "Path: " << std::endl;

    std::cout << "Dijkstra:" << std::endl;
    for (Graph::location_t i = 0; i < (Graph::location_t)matrix.size(); i++) {
        auto dijkstraPath = Dijkstra<Graph>::search(graph, start, i);

        Dijkstra<Graph>::show(dijkstraPath, start, i);
    }

    std::cout << std::endl << "Floyd:" << std::endl;
    for (Graph::location_t i = 0; i < (Graph::location_t)matrix.size(); i++) {
        auto floydPath = Floyd<Graph>::search(graph, start, i);

        Floyd<Graph>::show(floydPath, start, i);
    }

    return EXIT_SUCCESS;
}