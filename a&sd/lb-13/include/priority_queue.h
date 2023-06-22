#include <queue>
#include <utility>
#include <vector>

// Modified version of std::priority_queue. Use vector instead of heap and change priority direction
template <typename T, typename priority_t> struct PriorityQueue
{
  public:
    typedef std::pair<priority_t, T> PQElement;

    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

    inline bool empty() const
    {
        return elements.empty();
    }

    inline void push(T item, priority_t priority)
    {
        elements.emplace(priority, item);
    }

    T pop()
    {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};