#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "priority_queue.h"

template <typename Graph> class Dijkstra
{
  private:
    // Reconstruct a path from start to goal
    static std::vector<std::pair<typename Graph::location_t, typename Graph::cost_t>> reconstruct_path(
        const typename Graph::location_t                                           &start,
        const typename Graph::location_t                                           &goal,
        std::unordered_map<typename Graph::location_t, typename Graph::location_t> &came_from,
        std::unordered_map<typename Graph::location_t, typename Graph::cost_t>     &cost_so_far
    )
    {
        std::vector<std::pair<typename Graph::location_t, typename Graph::cost_t>> path;
        typename Graph::location_t                                                 current = goal;

        if (came_from.find(goal) == came_from.end())
        {
            return path; // no path can be found
        }

        while (current != start)
        {
            path.push_back({current, cost_so_far[current]});
            current = came_from[current];
        }

        path.push_back({start, (typename Graph::cost_t)0});

        // reconstructed path will start from end, reverse
        std::reverse(path.begin(), path.end());

        return path;
    }

  public:
    static void show(
        std::vector<std::pair<typename Graph::location_t, typename Graph::cost_t>> path,
        const typename Graph::location_t                                          &start,
        const typename Graph::location_t                                          &goal
    )
    {

        std::cout << "\033[31m" << std::setw(2) << start << "\033[0m"
                  << " -> "
                  << "\033[36m" << std::setw(2) << goal << "\033[0m"
                  << " | ";

        if (path.size() == 0)
        {
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
        }
        else if (path.size() == 1)
        {
            std::cout << "Moving to the same edge. (cost: "
                      << "\033[33m" << std::setw(2) << path[0].second << "\033[0m"
                      << ")." << std::endl;

            return;
        }

        std::cout << "\033[31m" << std::setw(2) << start << "\033[0m";

        for (size_t i = 1; i < path.size(); i++)
        {
            // cost from the first edge to current is stored, so subtract cost of prev from current
            std::cout << " -("
                      << "\033[33m" << std::setw(2) << path[i].second - path[i - 1].second << "/" << std::setw(3)
                      << path[i].second << "\033[0m"
                      << ")-> ";

            if (path[i].first == goal)
            {
                std::cout << "\033[32m";
            }
            else
            {
                std::cout << "\033[36m";
            }

            std::cout << std::setw(2) << path[i].first;

            std::cout << "\033[0m";
        }

        std::cout << std::endl;
    }

    static std::vector<std::pair<typename Graph::location_t, typename Graph::cost_t>> search(
        Graph &graph, const typename Graph::location_t &start, const typename Graph::location_t &goal
    )
    {
        std::unordered_map<typename Graph::location_t, typename Graph::cost_t>     cost_so_far;
        PriorityQueue<typename Graph::location_t, typename Graph::cost_t>          frontier;
        std::unordered_map<typename Graph::location_t, typename Graph::location_t> came_from;

        frontier.push(start, typename Graph::cost_t(0));
        came_from[start]   = start;
        cost_so_far[start] = typename Graph::cost_t(0);

        while (!frontier.empty())
        {
            typename Graph::location_t current = frontier.pop();

            if (current == goal)
            {
                break;
            }

            for (typename Graph::location_t next : graph.neighbors(current))
            {
                typename Graph::cost_t new_cost = cost_so_far[current] + graph.cost(current, next);
                if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
                {
                    cost_so_far[next] = new_cost;
                    came_from[next]   = current;
                    frontier.push(next, new_cost);
                }
            }
        }

        return Dijkstra<Graph>::reconstruct_path(start, goal, came_from, cost_so_far);
    }
};