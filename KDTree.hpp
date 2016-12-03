#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <algorithm>
#include <vector>

class KDTree {
 private:
  class KDTreeNode {
   public:
    /* Constructors */
    KDTreeNode() : KDTreeNode{0, 0} {}
    KDTreeNode(int axis) : KDTreeNode{axis, 0} {}
    KDTreeNode(int axis, int value)
        : KDTreeNode{{}, axis, value, nullptr, nullptr} {}
    KDTreeNode(const std::vector<int>& point, int axis, int value,
               KDTreeNode* left, KDTreeNode* right)
        : point{point}, axis{axis}, value{value}, left{left}, right{right} {}
    /**
     * Deep destructor
     *
     */
    ~KDTreeNode() {
      if (left != nullptr) delete left;
      if (right != nullptr) delete right;
    }

    std::vector<int> point;
    int axis;
    int value;
    KDTreeNode* left;
    KDTreeNode* right;
  };

 public:
  KDTreeNode* root;
  KDTree(std::vector<std::vector<int> > points, int dimensions);
  ~KDTree() { delete root; }
  void deleteNode(KDTreeNode* node);
  void createTree(std::vector<std::vector<int> > points, KDTreeNode* treeRoot);
  bool isLeaf(KDTreeNode* node);

  int dimensions;
};

#endif
