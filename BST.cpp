//
// Created by Darin Lee on 12/15/2019.
//

#include "BST.h"
#include <queue>

BSTNode::BSTNode(int key) : key(key), parent(nullptr), left(nullptr), right(nullptr) {}

BSTNode::BSTNode(int key, BSTNode* parent) : key(key), parent(parent), left(nullptr), right(nullptr) {}

BSTNode::BSTNode(int key, BSTNode* left, BSTNode* right) : key(key), parent(nullptr), left(left), right(right) {}

BSTNode::BSTNode(int key, BSTNode* p, BSTNode* l, BSTNode* r) : key(key), parent(p), left(l), right(r) {}

int BSTNode::getKey() {
  return key;
}

BSTNode* BSTNode::getParent() {
  return parent;
}

BSTNode* BSTNode::getLeft() {
  return left;
}

BSTNode* BSTNode::getRight() {
  return right;
}

void BSTNode::setKey(int k) {
  key = k;
}

void BSTNode::setParent(BSTNode* p) {
  parent = p;
}

void BSTNode::setLeft(BSTNode* l) {
  left = l;
}

void BSTNode::setRight(BSTNode* r) {
  right = r;
}

bool BSTNode::isLeaf() const {
  return left == nullptr && right == nullptr;
}

bool BSTNode::HasLeftChild() const {
  return left != nullptr;
}

bool BSTNode::HasRightChild() const {
  return right != nullptr;
}

BST::BST() : root(nullptr), size(0) {}

void BST::Insert(int key) {
  if (root == nullptr) {
    root = new BSTNode(key);
    size++;
    return;
  }
  BSTNode* currentNode = root;
  BSTNode* lastNode = nullptr;
  while (currentNode != nullptr) {
    lastNode = currentNode;
    currentNode = (key < currentNode->getKey()) ?
                  currentNode->getLeft() : currentNode->getRight();
  }
  if (key < lastNode->getKey()) {
    lastNode->setLeft(new BSTNode(key, lastNode));
  } else {
    lastNode->setRight(new BSTNode(key, lastNode));
  }
  size++;
}

void BST::Delete(int key) {
  // assume the key will be in the tree
  BSTNode* currentNode = root;
  while (currentNode != nullptr) {
    if (currentNode->getKey() == key) {
      // node is leaf
      if (currentNode->isLeaf()) {
        // node is root (parent is nullptr)
        if (currentNode == root) {
          delete currentNode;
          size--;
          root = nullptr;
        }
        else {
          if (key < currentNode->getParent()->getKey()) {
            currentNode->getParent()->setLeft(nullptr);
            delete currentNode;
            size--;
          }
          else {
            currentNode->getParent()->setRight(nullptr);
            delete currentNode;
            size--;
          }
        }
      }
      // node has only a left child
      else if (currentNode->HasLeftChild() && !currentNode->HasRightChild()) {
        if (currentNode == root) {
          root = currentNode->getLeft();
          delete currentNode;
          size--;
        }
        else {
          currentNode->getLeft()->setParent(currentNode->getParent());
          if (currentNode->getLeft()->getKey() < currentNode->getParent()->getKey()) {
            currentNode->getParent()->setLeft(currentNode->getLeft());
          }
          else {
            currentNode->getParent()->setRight(currentNode->getLeft());
          }
          delete currentNode;
          size--;
        }
      }
      // node has only a right child
      else if (currentNode->HasRightChild() && !currentNode->HasLeftChild()) {
        if (currentNode == root) {
          root = currentNode->getRight();
          delete currentNode;
          size--;
        }
        else {
          currentNode->getRight()->setParent(currentNode->getParent());
          if (currentNode->getRight()->getKey() < currentNode->getParent()->getKey()) {
            currentNode->getParent()->setLeft(currentNode->getRight());
          }
          else {
            currentNode->getParent()->setRight(currentNode->getRight());
          }
          delete currentNode;
          size--;
        }
      }
      // node has two children
      else {
        currentNode->setKey(FindMin(currentNode->getRight()));
        DeleteMin(currentNode->getRight());
      }
      return;
    }
    else if (currentNode->getKey() > key) {
      currentNode = currentNode->getLeft();
    }
    else {
      currentNode = currentNode->getRight();
    }
  }
}

nlohmann::json BST::JSON() const {
  nlohmann::json result;
  std::queue<BSTNode*> nodes;
  if (root != nullptr) {
    result["root"] = root->getKey();
    nodes.push(root);
    while (!nodes.empty()) {
      auto v = nodes.front();
      nodes.pop();
      std::string key = std::to_string(v->getKey());
      if (v->getLeft() != nullptr) {
        result[key]["left"] = v->getLeft()->getKey();
        nodes.push(v->getLeft());
      }
      if (v->getRight() != nullptr) {
        result[key]["right"] = v->getRight()->getKey();
        nodes.push(v->getRight());
      }
      if (v->getParent() != nullptr) {
        result[key]["parent"] = v->getParent()->getKey();
      } else {
        result[key]["root"] = true;
      }
    }
  }
  result["size"] = size;
  return result;
}

int BST::getSize() const {
  return size;
}

bool BST::empty() const {
  return size == 0;
}

// private method in case of deletion with two children
// used to find the min of right subtree
BSTNode* BST::DeleteMin(BSTNode* subtree) {
  BSTNode* currentNode = subtree;
  while (currentNode->getLeft() != nullptr) {
    currentNode = currentNode->getLeft();
  }
  BSTNode* parentNode = nullptr;
  // currentNode is a leaf
  if (currentNode->isLeaf()) {
    if (currentNode->getParent() == root) {
      parentNode = root;
      delete currentNode;
      size--;
      root->setRight(nullptr);
    }
    else {
      parentNode = currentNode->getParent();
      currentNode->getParent()->setLeft(nullptr);
      delete currentNode;
      size--;
    }
  }
  // currentNode has a right child
  else if (currentNode->HasRightChild()) {
    currentNode->getRight()->setParent(currentNode->getParent());
    parentNode = currentNode->getParent();
    if (currentNode->getRight()->getKey() < currentNode->getParent()->getKey()) {
      currentNode->getParent()->setLeft(currentNode->getRight());
    }
    else {
      currentNode->getParent()->setRight(currentNode->getRight());
    }
    delete currentNode;
    size--;
  }
  return parentNode;
}

int BST::FindMin(BSTNode* subtree) {
  BSTNode* currentNode = subtree;
  while (currentNode->getLeft() != nullptr) {
    currentNode = currentNode->getLeft();
  }
  return currentNode->getKey();
}
