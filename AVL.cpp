//
// Created by Darin Lee on 12/17/2019.
//

#include "AVL.h"
#include <algorithm>

AVL::AVL() : BST() {}

void AVL::Insert(int key) {
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
  BSTNode* unbalancedNode = lastNode;
  while (unbalancedNode != nullptr) {
    if (balanceFactor(unbalancedNode) < -1) {
      if (height(unbalancedNode->getLeft()->getLeft()) >= height(unbalancedNode->getLeft()->getRight())) {
        rightRotation(unbalancedNode);        // left left case
      } else {
        leftRotation(unbalancedNode->getLeft());  // left right case
        rightRotation(unbalancedNode);
      }
    }
    else if (balanceFactor(unbalancedNode) > 1) {
      if (height(unbalancedNode->getRight()->getRight()) >= height(unbalancedNode->getRight()->getLeft())) {
        leftRotation(unbalancedNode);           // right right case
      } else {
        rightRotation(unbalancedNode->getRight());  // right left case
        leftRotation(unbalancedNode);
      }
    }
    unbalancedNode = unbalancedNode->getParent();
  }
}

void AVL::Delete(int key) {
  BSTNode* currentNode = root;
  BSTNode* unbalancedNode = nullptr;
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
          unbalancedNode = currentNode->getParent();
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
          unbalancedNode = root;
          delete currentNode;
          size--;
        }
        else {
          currentNode->getLeft()->setParent(currentNode->getParent());
          unbalancedNode = currentNode->getParent();
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
          unbalancedNode = root;
          delete currentNode;
          size--;
        }
        else {
          currentNode->getRight()->setParent(currentNode->getParent());
          unbalancedNode = currentNode->getParent();
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
        unbalancedNode = DeleteMin(currentNode->getRight());
      }
      while (unbalancedNode != nullptr) {
        if (balanceFactor(unbalancedNode) < -1) {
          if (height(unbalancedNode->getLeft()->getLeft()) >= height(unbalancedNode->getLeft()->getRight())) {
            rightRotation(unbalancedNode);        // left left case
          } else {
            leftRotation(unbalancedNode->getLeft());  // left right case
            rightRotation(unbalancedNode);
          }
        }
        else if (balanceFactor(unbalancedNode) > 1) {
          if (height(unbalancedNode->getRight()->getRight()) >= height(unbalancedNode->getRight()->getLeft())) {
            leftRotation(unbalancedNode);           // right right case
          } else {
            rightRotation(unbalancedNode->getRight());  // right left case
            leftRotation(unbalancedNode);
          }
        }
        unbalancedNode = unbalancedNode->getParent();
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

int AVL::balanceFactor(BSTNode* currentNode) const {
  if (currentNode == nullptr) {
    return 0;
  }
  return height(currentNode->getRight()) - height(currentNode->getLeft());
}

int AVL::height(BSTNode* currentNode) const {
  if (currentNode == nullptr) {
    return -1;
  }
  else if (currentNode->isLeaf()) {
    return 0;
  }
  else if (currentNode->HasLeftChild() && !(currentNode->HasRightChild())) {
    return 1 + height(currentNode->getLeft());
  }
  else if (!(currentNode->HasLeftChild()) && currentNode->HasRightChild()) {
    return 1 + height(currentNode->getRight());
  }
  return 1 + std::max(height(currentNode->getLeft()), height(currentNode->getRight()));
}

void AVL::leftRotation(BSTNode* currentNode) {
  BSTNode* childNode = currentNode->getRight();
  BSTNode* subtree = childNode->getLeft();
  childNode->setLeft(currentNode);
  currentNode->setRight(subtree);
  childNode->setParent(currentNode->getParent());
  if (currentNode == BST::root) {
    BST::root = childNode;
  }
  currentNode->setParent(childNode);
  if (subtree != nullptr) {
    subtree->setParent(currentNode);
  }
  if (childNode->getParent() != nullptr) {
    if (childNode->getKey() < childNode->getParent()->getKey()) {
      childNode->getParent()->setLeft(childNode);
    }
    else {
      childNode->getParent()->setRight(childNode);
    }
  }
}

void AVL::rightRotation(BSTNode* currentNode) {
  BSTNode* childNode = currentNode->getLeft();
  BSTNode* subtree = childNode->getRight();
  childNode->setRight(currentNode);
  currentNode->setLeft(subtree);
  childNode->setParent(currentNode->getParent());
  if (currentNode == BST::root) {
    BST::root = childNode;
  }
  currentNode->setParent(childNode);
  if (subtree != nullptr) {
    subtree->setParent(currentNode);
  }
  if (childNode->getParent() != nullptr) {
    if (childNode->getKey() < childNode->getParent()->getKey()) {
      childNode->getParent()->setLeft(childNode);
    }
    else {
      childNode->getParent()->setRight(childNode);
    }
  }
}

