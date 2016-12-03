#include "KDTree.hpp"
#include <iostream>

KDTree::KDTree(std::vector<std::vector<int> > points, int dimensions) {
  this->dimensions = dimensions;
  root = new KDTreeNode();
  root->axis = 0;
  createTree(points, root);
}

void KDTree::deleteNode(KDTreeNode* node) {
  if (node != nullptr) delete node;
}

void KDTree::createTree(std::vector<std::vector<int> > points,
                        KDTreeNode* treeRoot) {
  if (points.size() > 1) {
    std::sort(points.begin(), points.end(),
              [treeRoot](std::vector<int> a, std::vector<int> b) {
                return a[treeRoot->axis] < b[treeRoot->axis];
              });
    int middleIndex = (points.size() / 2);
    treeRoot->value = points[middleIndex][treeRoot->axis];
    int axis{(treeRoot->axis + 1) % dimensions};
    treeRoot->left = new KDTreeNode{axis};
    treeRoot->right = new KDTreeNode{axis};
    treeRoot->right->axis = treeRoot->left->axis;
    std::vector<std::vector<int> > leftPoints{points.begin(),
                                              points.begin() + middleIndex};
    std::vector<std::vector<int> > rightPoints{points.begin() + middleIndex,
                                               points.end()};
    if (leftPoints.size() > 0) {
      createTree(leftPoints, treeRoot->left);
    }
    if (rightPoints.size() > 0) {
      createTree(rightPoints, treeRoot->right);
    }
  }
  if (points.size() == 1) {
    treeRoot->point = points[0];
  }
}

bool KDTree::isLeaf(KDTreeNode* node) {
  return node->left == nullptr && node->right == nullptr;
}
