//
// Created by Darin Lee on 12/17/2019.
//

#ifndef BINARYSEARCHTREES_AVL_H
#define BINARYSEARCHTREES_AVL_H

#include "BST.h"

class AVL: public BST {
 public:
  AVL();
  void Insert(int key) override;
  void Delete(int key) override;

 protected:
  int balanceFactor(BSTNode* currentNode) const;
  int height(BSTNode* currentNode) const;
  void leftRotation(BSTNode* currentNode);
  void rightRotation(BSTNode* currentNode);
};

#endif //BINARYSEARCHTREES_AVL_H
