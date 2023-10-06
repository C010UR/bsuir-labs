#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "colors.h"

template <typename T> class AVLBST
{
  public:
    struct Node
    {
        T     value;
        Node *parent;
        Node *left;
        Node *right;
        int   height;

        Node(T value, Node *parent) : value(value), parent(parent), left(nullptr), right(nullptr), height(1)
        {
        }
    };

  private:
    AVLBST<T>::Node *tree = nullptr;

    void showNode(AVLBST<T>::Node *node)
    {
        if (!node->parent)
        {
            std::cout << COLOR_GREEN;
        }
        else if (node->parent->left == node)
        {
            std::cout << COLOR_YELLOW;
        }
        else
        {
            std::cout << COLOR_CYAN;
        }

        std::cout << node->value << COLOR_RESET << " ";
    }

    void showPreOrder(AVLBST<T>::Node *node)
    {
        if (!node)
        {
            return;
        }

        this->showNode(node);
        this->showPreOrder(node->left);
        this->showPreOrder(node->right);
    }

    void showInOrder(AVLBST<T>::Node *node)
    {
        if (!node)
        {
            return;
        }

        this->showInOrder(node->left);
        this->showNode(node);
        this->showInOrder(node->right);
    }

    void showPostOrder(AVLBST<T>::Node *node)
    {
        if (!node)
        {
            return;
        }

        this->showPostOrder(node->left);
        this->showPostOrder(node->right);
        this->showNode(node);
    }

    const std::string left_string  = COLOR_YELLOW + "left" + COLOR_RESET;
    const std::string right_string = COLOR_CYAN + "right" + COLOR_RESET;

    void showMoveLeft(int spacing = 2)
    {
        std::cout << std::string(spacing, ' ') << "- moving " << this->left_string << std::endl;
    }

    void showMoveRight(int spacing = 2)
    {
        std::cout << std::string(spacing, ' ') << "- moving " << this->right_string << std::endl;
    }

    std::string valueString(T value)
    {
        return "'" + COLOR_YELLOW + std::to_string(value) + COLOR_RESET + "'";
    }

    void updateHeight(AVLBST<T>::Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        node->height = std::max(this->getHeight(node->left), this->getHeight(node->right)) + 1;
    }

    int getHeight(AVLBST<T>::Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return node->height;
    }

    int getBalance(AVLBST<T>::Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return this->getHeight(node->left) - this->getHeight(node->right);
    }

    AVLBST<T>::Node *rotateRight(AVLBST<T>::Node *node)
    {
        AVLBST<T>::Node *left      = node->left;
        AVLBST<T>::Node *leftRight = left->right;

        left->parent = node->parent;
        node->parent = left;

        if (leftRight != nullptr)
        {
            leftRight->parent = node;
        }

        left->right = node;
        node->left  = leftRight;

        this->updateHeight(node);
        this->updateHeight(left);

        return left;
    }

    AVLBST<T>::Node *rotateLeft(AVLBST<T>::Node *node)
    {
        AVLBST<T>::Node *right     = node->right;
        AVLBST<T>::Node *rightLeft = right->left;

        right->parent = node->parent;
        node->parent  = right;
        if (rightLeft != nullptr)
        {
            rightLeft->parent = node;
        }

        right->left = node;
        node->right = rightLeft;

        this->updateHeight(node);
        this->updateHeight(right);

        return right;
    }

  public:
    void insert(T value)
    {
        this->tree = this->insertNode(this->tree, value);
    }

    AVLBST<T>::Node *insertNode(AVLBST<T>::Node *node, T value, AVLBST<T>::Node *previous = nullptr)
    {
        if (node == nullptr)
        {
            return new AVLBST<T>::Node(value, previous);
        }

        if (value < node->value)
        {
            node->left = insertNode(node->left, value, node);
        }
        else if (value > node->value)
        {
            node->right = insertNode(node->right, value, node);
        }
        else
        {
            return node;
        }

        this->updateHeight(node);
        int balance = this->getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->value)
            return this->rotateRight(node);

        // Right Right Case
        if (balance < -1 && value > node->right->value)
            return this->rotateLeft(node);

        // Left Right Case
        if (balance > 1 && value > node->left->value)
        {
            node->left = this->rotateLeft(node->left);
            return this->rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->value)
        {
            node->right = this->rotateRight(node->right);
            return this->rotateLeft(node);
        }

        return node;
    }

    AVLBST<T>::Node *search(T value)
    {
        if (!this->tree)
        {
            std::cout << "The tree is empty, cannot search" << std::endl;
            return nullptr;
        }

        AVLBST<T>::Node *current = this->tree;
        while (current)
        {
            if (current->value > value)
            {
                showMoveLeft();
                current = current->left;
            }
            else if (current->value < value)
            {
                showMoveRight();
                current = current->right;
            }
            else
            {
                std::cout << "The value " << this->valueString(value) << COLOR_GREEN << " was found" << COLOR_RESET
                          << std::endl;

                return current;
            }
        }

        std::cout << "The value " << this->valueString(value) << COLOR_RED << " was not found" << std::endl;

        return nullptr;
    }

    void show()
    {
        if (!this->tree)
        {
            std::cout << "The tree is empty, nothing to show." << std::endl;
            return;
        }

        std::cout << "Pre-order traversal: ";
        this->showPreOrder(this->tree);
        std::cout << std::endl;

        std::cout << "In-order traversal: ";
        this->showInOrder(this->tree);
        std::cout << std::endl;

        std::cout << "Post-order traversal: ";
        this->showPostOrder(this->tree);
        std::cout << std::endl;
    }
};