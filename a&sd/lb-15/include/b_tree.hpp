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

class BTreeNode
{
  private:
    int        *keys;
    BTreeNode **children;
    int         size;
    int         order;
    bool        isLeaf;

    void insertNonFull(int key);
    void splitChild(int idx, BTreeNode *y);

    void removeFromLeaf(int idx);
    void removeFromBranch(int idx);

    int getPredecessor(int idx);
    int getSuccessor(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);

    void merge(int idx);

  public:
    friend class BTree;

    BTreeNode(int order, bool isLeaf);
    BTreeNode *search(int k);

    void traverse(bool isRoot = false);

    int  find(int key);
    void remove(int key);
};

class BTree
{
    BTreeNode *root;
    int        order;

  public:
    BTree(int order)
    {
        root        = nullptr;
        this->order = order;
    }

    void       traverse();
    void       insert(int key);
    void       remove(int key);
    BTreeNode *search(int k);
};

