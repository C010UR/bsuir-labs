#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Color
{
  public:
    inline static const std::string RED    = "\033[31m";
    inline static const std::string GREEN  = "\033[32m";
    inline static const std::string YELLOW = "\033[33m";
    inline static const std::string CYAN   = "\033[36m";
    inline static const std::string RESET  = "\033[0m";
};

template<typename T = int>
class HashMap
{
  public:
    const std::string   path = "map";
    typedef std::string key_t;

  private:
    std::size_t capacity;

    std::string hash(key_t key)
    {
        return this->path + "/key-" + std::to_string(key.size() % this->capacity);
    }

    void showMap(HashMap::key_t key, T label)
    {
        std::cout << "  map[" << Color::CYAN << key << Color::RESET << "] - " << Color::YELLOW << label << Color::RESET
                  << std::endl;
    }

    T convertToScalar(const std::string &str)
    {
        std::istringstream iss(str);
        T                  value;
        iss >> value;

        return value;
    }

  public:
    HashMap(std::size_t capacity): capacity(capacity)
    {
        std::filesystem::create_directory(this->path);
    }

    void show()
    {
        std::cout << "Hash table: " << std::endl;

        for (const auto &entry : std::filesystem::directory_iterator(this->path)) {
            if (entry.is_regular_file()) {
                std::ifstream file(entry.path());

                if (file.good()) {
                    std::string line;
                    std::cout << "Reading file: " << entry.path() << std::endl;

                    while (std::getline(file, line)) {
                        std::istringstream iss(line);
                        std::string        key, value;

                        if (std::getline(iss, key, '=')) {
                            if (std::getline(iss, value)) {
                                this->showMap(key, this->convertToScalar(value));
                            } else {
                                std::cout << Color::RED << "Error parsing value in line: " << line << Color::RESET
                                          << std::endl;
                            }
                        } else {
                            std::cout << Color::RED << "Error parsing key-value pair in line: " << line << Color::RESET
                                      << std::endl;
                        }
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << Color::RED << "Error opening file: " << entry.path() << Color::RESET << std::endl;
                }
            }
        }
    }

    void insert(const std::string &key, const T &value)
    {
        std::cout << "Inserting '" << Color::YELLOW << value << Color::RESET << "' with key '" << Color::CYAN << key
                  << Color::RESET << "':" << std::endl;

        std::string hash = this->hash(key);

        std::ofstream file(hash, std::ios::app);

        if (!file.good()) {
            std::cerr << "Error opening file: " << hash << std::endl;
            return;
        }

        file << key << "=" << value << std::endl;

        file.close();
    }

    T find(const std::string &key)
    {
        std::string hash = this->hash(key);

        std::ifstream file(hash);

        if (!file.good()) {
            std::cout << Color::RED << "Value not found!" << Color::RESET << std::endl;
            return T();
        }

        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string        _key, value;

            if (std::getline(iss, _key, '=')) {
                if (_key == key) {
                    std::getline(iss, value);
                    std::cout << Color::GREEN << "Found: " << Color::YELLOW << value << Color::RESET << std::endl;
                    return this->convertToScalar(value);
                }
            } else {
                std::cout << Color::RED << "Error parsing key-value pair in line: " << line << Color::RESET
                          << std::endl;
            }
        }

        file.close();

        std::cout << Color::RED << "Value not found!" << Color::RESET << std::endl;

        return T();
    }

    void remove(const std::string &key)
    {
        std::string hash = this->hash(key);

        std::string tempFile = hash + ".tmp";

        std::ifstream inputFile(hash);
        std::ofstream outputFile(tempFile);

        if (!inputFile) {
            std::cout << Color::RED << "Value not found!" << Color::RESET << std::endl;
            return;
        }

        std::string line;

        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string        _key, value;

            if (std::getline(iss, _key, '=')) {
                if (key != _key) {
                    outputFile << line << std::endl;
                }
            } else {
                std::cout << Color::RED << "Error parsing key-value pair in line: " << line << Color::RESET
                          << std::endl;
            }
        }

        inputFile.close();
        outputFile.close();

        std::remove(hash.c_str());
        std::rename(tempFile.c_str(), hash.c_str());
    }
};