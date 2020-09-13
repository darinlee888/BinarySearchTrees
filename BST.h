//
// Created by Darin Lee on 12/15/2019.
//

#ifndef BINARYSEARCHTREES_BST_H
#define BINARYSEARCHTREES_BST_H

#include "json.hpp"

class BST;

class BSTNode {
 public:
  BSTNode(int key);
  BSTNode(int key, BSTNode* parent);
  BSTNode(int key, BSTNode* left, BSTNode* right);
  BSTNode(int key, BSTNode* p, BSTNode* l, BSTNode* r);
  int getKey();
  BSTNode* getParent();
  BSTNode* getLeft();
  BSTNode* getRight();
  void setKey(int k);
  void setParent(BSTNode* p);
  void setLeft(BSTNode* l);
  void setRight(BSTNode* r);
  bool isLeaf() const;
  bool HasLeftChild() const;
  bool HasRightChild() const;

 private:
  int key;
  BSTNode* parent;
  BSTNode* left;
  BSTNode* right;
};

class BST {
 public:
  BST();
  virtual void Insert(int key);
  virtual void Delete(int key);
  nlohmann::json JSON() const;
  int getSize() const;
  bool empty() const;

 protected:
  int FindMin(BSTNode* subtree);
  BSTNode* DeleteMin(BSTNode* subtree);
  BSTNode* root;
  int size;
};

#endif //BINARYSEARCHTREES_BST_H
