#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T = int> class HashMap
{
  public:
    typedef unsigned key_t;

  private:
    struct HashEntry
    {
        HashMap::key_t key   = (HashMap::key_t)-1;
        T              value = (T)0;
    };

    unsigned               capacity;
    std::vector<HashEntry> map;

    unsigned hash(key_t key)
    {
        return 10 + (key % 5);
    }

    void showMap(HashMap::key_t hash, std::string label, unsigned ansi_color)
    {
        std::cout << "  map["
                  << "\033[36m" << std::setw(2) << hash << "\033[0m"
                  << "] - "
                  << "\033[" << ansi_color << "m" << label << "\033[0m" << std::endl;
    }

  public:
    HashMap(HashMap::key_t capacity) : capacity(capacity), map(std::vector<HashEntry>(capacity))
    {
    }

    void show()
    {
        std::cout << "Hash table: " << std::endl;

        for (HashMap::key_t i = 0; i < map.size(); i++)
        {
            if (this->map[i].key != (HashMap::key_t)-1)
            {
                this->showMap(
                    i,
                    "Key: \033[36m" + std::to_string(this->map[i].key) + "\033[0m" + "; Value: " + "\033[33m"
                        + std::to_string(this->map[i].value),
                    0
                );
            }
            else
            {
                this->showMap(i, (std::string) "Empty", 32);
            }
        }
    }

    void insert(HashMap::key_t key, T value)
    {
        HashMap::key_t hash    = this->hash(key);
        HashMap::key_t initial = hash;

        std::cout << "Inserting '"
                  << "\033[33m" << value << "\033[0m"
                  << "' with key '"
                  << "\033[36m" << key << "\033[0m"
                  << "':" << std::endl;

        // Find empty cell
        if (this->map[hash].key != (HashMap::key_t)-1)
        {
            do
            {
                if (this->map[hash].key != (HashMap::key_t)-1)
                {
                    this->showMap(hash, "FILLED", 31);
                }

                hash = map.size() - 1 == hash ? 0 : hash + 1;
            } while (initial != hash && this->map[hash].key != (HashMap::key_t)-1);
        }

        if (initial == hash && this->map[hash].key != (HashMap::key_t)-1)
        {
            std::cout << "  "
                      << "\033[31m"
                      << "Hash map is filled. Skipping."
                      << "\033[0m" << std::endl;
        }
        else
        {
            this->showMap(hash, "EMPTY \033[0m - filling", 32);
            this->map[hash] = HashMap::HashEntry{key, value};
        }
    }

    T *find(HashMap::key_t key)
    {
        HashMap::key_t hash    = this->hash(key);
        HashMap::key_t initial = hash;

        do
        {
            if (this->map[hash].key == key)
            {

                this->showMap(hash, "HIT", 32);
                return &(this->map[hash].value);
            }

            this->showMap(hash, "MISS", 31);

            hash = map.size() - 1 == hash ? 0 : hash + 1;
        } while (initial != hash);

        return nullptr;
    }
};