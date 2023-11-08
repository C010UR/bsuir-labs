#pragma once

#include "priority_queue.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

template<typename Graph>
class Floyd
{
  public:
    static void show(
        std::vector<std::pair<typename Graph::location_t, typename Graph::cost_t>> path,
        const typename Graph::location_t                                          &start,
        const typename Graph::location_t                                          &goal)
    {
        std::cout << "\033[31m" << std::setw(2) << start << "\033[0m"
                  << " -> "
                  << "\033[36m" << std::setw(2) << goal << "\033[0m"
                  << " | ";

        if (path.size() == 0) {
            std::cout << "No path can be found from "
                      << "\033[36m"
                      << "'" << start << "'"
                      << "\033[0m"
                      << " to "
                      << "\033[36m"
                      << "'" << goal << "'"
                      << "\033[0m"
                      << "." << std::endl;

            return;
        } else if (path.size() == 1) {
            std::cout << "Moving to the same edge. (cost: "
                      << "\033[33m" << std::setw(2) << path[0].second << "\033[0m"
                      << ")." << std::endl;

            return;
        }

        std::cout << "\033[31m" << std::setw(2) << start << "\033[0m";

        for (size_t i = 1; i < path.size(); i++) {
            // cost from the first edge to current is stored, so subtract cost of prev from current
            std::cout << " -("
                      << "\033[33m" << std::setw(2) << path[i].second - path[i - 1].second << "/" << std::setw(3)
                      << path[i].second << "\033[0m"
                      << ")-> ";

            if (path[i].first == goal) {
                std::cout << "\033[32m";
            } else {
                std::cout << "\033[36m";
            }

            std::cout << std::setw(2) << path[i].first;

            std::cout << "\033[0m";
        }

        std::cout << std::endl;
    }

    static std::vector<std::pair<typename Graph::location_t, typename Graph::cost_t>>
    search(Graph &graph, const typename Graph::location_t &start, const typename Graph::location_t &goal)
    {
        std::vector<std::vector<typename Graph::cost_t>> dist(
            graph.size(),
            std::vector<typename Graph::cost_t>(graph.size()));
        std::vector<std::vector<typename Graph::location_t>> next(
            graph.size(),
            std::vector<typename Graph::location_t>(graph.size()));

        for (std::size_t i = 0; i < graph.size(); ++i) {
            for (std::size_t j = 0; j < graph.size(); ++j) {
                if (i == j) {
                    dist[i][j] = typename Graph::cost_t(0);
                } else if (graph.hasEdge(i, j)) {
                    dist[i][j] = graph.cost(i, j);
                    next[i][j] = i;
                } else {
                    dist[i][j] = std::numeric_limits<typename Graph::cost_t>::min();
                    next[i][j] = typename Graph::location_t(-1);
                }
            }
        }

        for (int i = 0; i < next.size(); i++) {
            for (int j = 0; j < next[i].size(); j++) {
                std::cout << " " << next[i][j];
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;

        for (int i = 0; i < dist.size(); i++) {
            for (int j = 0; j < dist[i].size(); j++) {
                std::cout << " " << dist[i][j];
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;

        for (std::size_t i = 0; i < graph.size(); ++i) {
            for (std::size_t j = 0; j < graph.size(); ++j) {
                if (i == j) {
                    dist[i][j] = typename Graph::cost_t(0);
                } else if (graph.hasEdge(i, j)) {
                    dist[i][j] = graph.cost(i, j);
                    next[i][j] = j;
                }
            }
        }

        for (std::size_t k = 0; k < graph.size(); ++k) {
            for (std::size_t i = 0; i < graph.size(); ++i) {
                for (std::size_t j = 0; j < graph.size(); ++j) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        for (int i = 0; i < next.size(); i++) {
            for (int j = 0; j < next[i].size(); j++) {
                std::cout << " " << next[i][j];
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;

        for (int i = 0; i < dist.size(); i++) {
            for (int j = 0; j < dist[i].size(); j++) {
                std::cout << " " << dist[i][j];
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;

        typename Graph::location_t current = start;

        std::vector<std::pair<typename Graph::location_t, typename Graph::cost_t>> path;

        while (current != goal) {
            typename Graph::location_t nextVertex = next[current][goal];

            if (nextVertex < typename Graph::location_t(0)) {
                // No path found
                return path;
            }

            path.push_back({nextVertex, dist[current][nextVertex]});

            current = nextVertex;
        }

        return path;
    }
};