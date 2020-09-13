//
// Created by Darin Lee on 12/19/2019.
//

#ifndef BINARYSEARCHTREES_SPLAY_H
#define BINARYSEARCHTREES_SPLAY_H

#include "AVL.h"

class SplayTree : public AVL {
 public:
  SplayTree();
  void Insert(int key) override;
  void Delete(int key) override;

 private:
  void Splay(BSTNode* node);
};

#endif //BINARYSEARCHTREES_SPLAY_H
