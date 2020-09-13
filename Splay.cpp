//
// Created by Darin Lee on 12/19/2019.
//

#include "Splay.h"

SplayTree::SplayTree() : AVL() {}

void SplayTree::Insert(int key) {
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
  BSTNode* newNode = new BSTNode(key, lastNode);
  if (key < lastNode->getKey()) {
    lastNode->setLeft(newNode);
  } else {
    lastNode->setRight(newNode);
  }
  size++;
  Splay(newNode);
}

void SplayTree::Delete(int key) {
  BSTNode* currentNode = root;
  while (currentNode != nullptr) {
    if (currentNode->getKey() == key) {
      Splay(currentNode);
      // node is leaf
      if (currentNode->isLeaf()) {
        delete currentNode;
        size--;
        root = nullptr;
      }
        // node has only a left child
      else if (currentNode->HasLeftChild() && !currentNode->HasRightChild()) {
        root = currentNode->getLeft();
        delete currentNode;
        size--;
      }
        // node has only a right child
      else if (currentNode->HasRightChild() && !currentNode->HasLeftChild()) {
        root = currentNode->getRight();
        delete currentNode;
        size--;
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

// move the node to the root
void SplayTree::Splay(BSTNode* node) {
  BSTNode* currentNode = node;
  while (currentNode != root) {
    if (currentNode->getParent() == root) {
      // zig case
      if (currentNode->getKey() < root->getKey()) {
        rightRotation(root);
      }
      // zag case
      else {
        leftRotation(root);
      }
    }
    else {
      if (currentNode->getKey() < currentNode->getParent()->getKey()) {
        // zig zig case
        if (currentNode->getParent()->getKey() < currentNode->getParent()->getParent()->getKey()) {
          rightRotation(currentNode->getParent()->getParent());
          rightRotation(currentNode->getParent());
        }
        // zag zig case
        else {
          rightRotation(currentNode->getParent());
          leftRotation(currentNode->getParent());
        }
      }
      else {
        // zig zag case
        if (currentNode->getParent()->getKey() < currentNode->getParent()->getParent()->getKey()) {
          leftRotation(currentNode->getParent());
          rightRotation(currentNode->getParent());
        }
        // zag zag case
        else {
          leftRotation(currentNode->getParent()->getParent());
          leftRotation(currentNode->getParent());
        }
      }
    }
  }
}
