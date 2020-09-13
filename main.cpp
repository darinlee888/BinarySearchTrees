#include "BST.h"
#include "AVL.h"
#include "Splay.h"
#include "json.hpp"
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <queue>
#include <fstream>

bool inTree(std::vector<int> values, int value) {
  for (unsigned int i = 0; i < values.size(); i++) {
    if (value == values[i]) {
      return true;
    }
  }
  return false;
}

int main() {
  BST binaryTree;
  AVL AVLTree;
  SplayTree splay;

  nlohmann::json instructions;

  std::vector<int> values;
  std::queue<int> tree;

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(1,100);

  int value = distribution(generator);
  instructions["0"]["operation"] = "insert";
  instructions["0"]["key"] = value;
  values.push_back(value);
  tree.push(value);
  binaryTree.Insert(value);
  AVLTree.Insert(value);
  splay.Insert(value);
  for (int i = 1; i < 10; i++) {
    value = distribution(generator);
    while (inTree(values, value)) {
      value = distribution(generator);
    }
    int option = distribution(generator);
    std::string key = std::to_string(i);
    if (option % 3 != 0 || values.empty()) {
      instructions[key]["operation"] = "insert";
      instructions[key]["key"] = value;
      values.push_back(value);
      tree.push(value);
      binaryTree.Insert(value);
      AVLTree.Insert(value);
      splay.Insert(value);
    }
    else {
      instructions[key]["operation"] = "delete";
      instructions[key]["key"] = tree.front();
      binaryTree.Delete(tree.front());
      AVLTree.Delete(tree.front());
      splay.Delete(tree.front());
      tree.pop();
    }
  }

  std::ofstream instructionFile("instructions.txt");
  std::ofstream BSTFile("bst_output.txt");
  std::ofstream AVLFile("avl_output.txt");
  std::ofstream SplayFile("splay_output.txt");

  instructionFile << instructions.dump(2);
  BSTFile << binaryTree.JSON().dump(2);
  AVLFile << AVLTree.JSON().dump(2);
  SplayFile << splay.JSON().dump(2);

  return 0;
}
