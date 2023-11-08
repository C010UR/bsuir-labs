#include "b_tree.hpp"

BTreeNode::BTreeNode(int order, bool isLeaf)
{
    this->order  = order;
    this->isLeaf = isLeaf;

    this->keys     = new int[2 * order - 1];
    this->children = new BTreeNode *[2 * order];

    this->size = 0;
}

int BTreeNode::find(int key)
{
    int idx = 0;

    while (idx < size && keys[idx] < key) {
        ++idx;
    }

    return idx;
}

void BTreeNode::remove(int key)
{
    int idx = this->find(key);

    if (idx < this->size && keys[idx] == key) {
        if (this->isLeaf) {
            this->removeFromLeaf(idx);
        } else {
            this->removeFromBranch(idx);
        }
    } else {
        if (this->isLeaf) {
            std::cout << Color::RED << "The key " << Color::YELLOW << key << Color::RED << " does not exist in the tree"
                      << Color::RESET << std::endl;
            return;
        }

        bool flag = idx == this->size;

        if (this->children[idx]->size < order) {
            this->fill(idx);
        }

        if (flag && idx > this->size) {
            this->children[idx - 1]->remove(key);
        } else {
            this->children[idx]->remove(key);
        }
    }
}

void BTreeNode::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < this->size; ++i) {
        keys[i - 1] = keys[i];
    }

    this->size--;
}

void BTreeNode::removeFromBranch(int idx)
{
    int key = keys[idx];

    if (this->children[idx]->size >= this->order) {
        int pred  = this->getPredecessor(idx);
        keys[idx] = pred;
        this->children[idx]->remove(pred);
    } else if (this->children[idx + 1]->size >= this->order) {
        int succ  = this->getSuccessor(idx);
        keys[idx] = succ;
        this->children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        this->children[idx]->remove(key);
    }
}

int BTreeNode::getPredecessor(int idx)
{
    BTreeNode *cur = this->children[idx];

    while (!cur->isLeaf) {
        cur = cur->children[cur->size];
    }

    return cur->keys[cur->size - 1];
}

int BTreeNode::getSuccessor(int idx)
{
    BTreeNode *cur = this->children[idx + 1];

    while (!cur->isLeaf) {
        cur = cur->children[0];
    }

    return cur->keys[0];
}

void BTreeNode::fill(int idx)
{
    if (idx != 0 && this->children[idx - 1]->size >= this->order) {
        this->borrowFromPrev(idx);
    } else if (idx != this->size && this->children[idx + 1]->size >= this->order) {
        this->borrowFromNext(idx);
    } else {
        if (idx != this->size) {
            this->merge(idx);
        } else {
            this->merge(idx - 1);
        }
    }
}

void BTreeNode::borrowFromPrev(int idx)
{
    BTreeNode *child   = this->children[idx];
    BTreeNode *sibling = this->children[idx - 1];

    for (int i = child->size - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->isLeaf) {
        for (int i = child->size; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = keys[idx - 1];

    if (!child->isLeaf) {
        child->children[0] = sibling->children[sibling->size];
    }

    keys[idx - 1] = sibling->keys[sibling->size - 1];

    child->size += 1;
    sibling->size -= 1;
}

void BTreeNode::borrowFromNext(int idx)
{
    BTreeNode *child   = this->children[idx];
    BTreeNode *sibling = this->children[idx + 1];

    child->keys[child->size] = keys[idx];

    if (!child->isLeaf) {
        child->children[child->size + 1] = sibling->children[0];
    }

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->size; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->size; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->size += 1;
    sibling->size -= 1;
}

void BTreeNode::merge(int idx)
{
    BTreeNode *child   = this->children[idx];
    BTreeNode *sibling = this->children[idx + 1];

    child->keys[this->order - 1] = keys[idx];

    for (int i = 0; i < sibling->size; ++i) {
        child->keys[i + this->order] = sibling->keys[i];
    }

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->size; ++i) {
            child->children[i + this->order] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < this->size; ++i) {
        keys[i - 1] = keys[i];
    }

    for (int i = idx + 2; i <= this->size; ++i) {
        this->children[i - 1] = this->children[i];
    }

    child->size += sibling->size + 1;
    this->size--;

    delete (sibling);
}

void BTree::insert(int key)
{
    if (root == nullptr) {
        root          = new BTreeNode(this->order, true);
        root->keys[0] = key;
        root->size    = 1;
    } else {
        if (this->search(key)) {
            std::cout << Color::RED << "Value already exists" << Color::RESET << std::endl;
            return;
        }

        if (root->size == 2 * this->order - 1) {
            BTreeNode *node = new BTreeNode(this->order, false);

            node->children[0] = root;

            node->splitChild(0, root);

            int i = 0;
            if (node->keys[0] < key) i++;
            node->children[i]->insertNonFull(key);

            root = node;
        } else
            root->insertNonFull(key);
    }
}

void BTreeNode::insertNonFull(int key)
{
    int i = this->size - 1;

    if (this->isLeaf == true) {
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = key;
        this->size  = this->size + 1;
    } else {
        while (i >= 0 && keys[i] > key)
            i--;

        if (children[i + 1]->size == 2 * this->order - 1) {
            splitChild(i + 1, this->children[i + 1]);

            if (keys[i + 1] < key) {
                i++;
            }
        }

        this->children[i + 1]->insertNonFull(key);
    }
}

void BTreeNode::splitChild(int idx, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->order, y->isLeaf);
    z->size      = this->order - 1;

    for (int j = 0; j < this->order - 1; j++) {
        z->keys[j] = y->keys[j + this->order];
    }

    if (y->isLeaf == false) {
        for (int j = 0; j < this->order; j++) {
            z->children[j] = y->children[j + this->order];
        }
    }

    y->size = this->order - 1;

    for (int j = this->size; j >= idx + 1; j--) {
        this->children[j + 1] = this->children[j];
    }

    this->children[idx + 1] = z;

    for (int j = this->size - 1; j >= idx; j--) {
        keys[j + 1] = keys[j];
    }

    keys[idx] = y->keys[this->order - 1];

    this->size = this->size + 1;
}

void BTreeNode::traverse(bool isRoot)
{
    int i;

    for (i = 0; i < this->size; i++) {
        if (this->isLeaf == false) this->children[i]->traverse();

        std::cout << " " << (isRoot ? Color::GREEN : (this->isLeaf ? Color::CYAN : Color::YELLOW)) << keys[i]
                  << Color::RESET;
    }

    if (this->isLeaf == false) {
        this->children[i]->traverse();
    }
}

void BTree::remove(int key)
{
    if (!root) {
        std::cout << Color::RED << "The tree is empty" << Color::RESET << std::endl;
        return;
    }

    root->remove(key);

    if (root->size == 0) {
        BTreeNode *tmp = root;

        if (root->isLeaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }

        delete tmp;
    }
}

void BTree::traverse()
{
    if (this->root != nullptr) {
        this->root->traverse(true);

        std::cout << std::endl;
    }
}

BTreeNode *BTreeNode::search(int key)
{
    int idx = this->find(key);

    if (keys[idx] == key) {
        return this;
    }

    if (this->isLeaf == true) {
        return nullptr;
    }

    return this->children[idx]->search(key);
}

BTreeNode *BTree::search(int key)
{
    return this->root == nullptr ? nullptr : this->root->search(key);
}