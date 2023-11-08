#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Graph
{
  public:
    // Types for graphs
    typedef int location_t;
    typedef int cost_t;

    std::size_t _size = 0;

  private:
    // Map of edges that stores every available edge from it
    std::map<location_t, std::vector<std::pair<Graph::location_t, Graph::cost_t>>> edges;

  public:
    // Constructor
    Graph(std::vector<std::vector<cost_t>> matrix)
    {
        // Convert matrix representation of a graph to map
        for (location_t i = 0; i < (Graph::location_t)matrix.size(); i++) {
            if (matrix.size() != matrix[i].size()) {
                throw std::invalid_argument(
                    "Matrix representation of a graph must be a square. Matrix size: " + std::to_string(matrix.size())
                    + "; Matrix[i] size: " + std::to_string(matrix[i].size()));
            }

            for (location_t j = 0; j < (Graph::location_t)matrix[i].size(); j++) {
                if (matrix[i][j] != std::numeric_limits<typename Graph::cost_t>::max()) {
                    edges[i].push_back({j, matrix[i][j]});
                }
            }
        }

        _size = matrix.size();
    }

    // Get all neighbors
    std::vector<Graph::location_t> neighbors(Graph::location_t id)
    {
        std::vector<Graph::location_t> result;

        for (auto location : edges[id]) {
            result.push_back(location.first);
        }

        return result;
    }

    bool hasEdge(Graph::location_t first, Graph::location_t second)
    {
        auto result = std::find_if(
            edges[first].begin(),
            edges[first].end(),
            [second](const std::pair<Graph::location_t, Graph::cost_t> &element) {
                return element.first == second;
            });

        return first == second || result != edges[first].end();
    }

    // Print graph to a console
    void show()
    {
        for (auto it : edges) {
            std::cout << "\033[36m" << it.first << "\033[0m" << std::endl;

            for (location_t i = 0; i < (Graph::location_t)it.second.size(); i++) {
                std::cout << "  -("
                          << "\033[33m" << it.second[i].first << "\033[0m"
                          << ")-> "
                          << "\033[36m" << it.second[i].second << "\033[0m" << std::endl;
            }
        }
    }

    // Get a cost of moving from one edge to another
    Graph::cost_t cost(Graph::location_t first, Graph::location_t second)
    {
        if (first == second) {
            return 0;
        }

        auto result = std::find_if(
            edges[first].begin(),
            edges[first].end(),
            [second](const std::pair<Graph::location_t, Graph::cost_t> &element) {
                return element.first == second;
            });

        if (result == edges[first].end()) {
            throw std::invalid_argument(
                "First edge '" + std::to_string(first) + "' does not a have a path to edge '" + std::to_string(second)
                + "'.");
        }

        return result->second;
    }

    std::size_t size()
    {
        return _size;
    }
};