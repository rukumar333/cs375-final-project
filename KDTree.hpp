#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <algorithm>
#include <cfloat>
#include <vector>
#include "Point.hpp"

template <size_t D>
class KDTree {
 private:
  class KDTreeNode {
   public:
    /* Constructors */
    KDTreeNode() : KDTreeNode{0, 0} {}
    KDTreeNode(int axis) : KDTreeNode{axis, 0} {}
    KDTreeNode(int axis, double value)
        : KDTreeNode{{}, axis, value, nullptr, nullptr} {}
    KDTreeNode(const Point<D>& point, int axis, double value, KDTreeNode* left,
               KDTreeNode* right)
        : point{point}, axis{axis}, value{value}, left{left}, right{right} {}
    /**
     * Deep destructor
     */
    ~KDTreeNode() {
      if (left != nullptr) delete left;
      if (right != nullptr) delete right;
    }
    bool isLeaf() const { return left == nullptr && right == nullptr; }
    Point<D> point;
    int axis;
    double value;
    KDTreeNode* left;
    KDTreeNode* right;
  };

 public:
  KDTreeNode* root;

  KDTree(std::vector<Point<D> > points) : root{new KDTreeNode{0}} {
    createTree(points, root);
  }

  ~KDTree() {
    if (root != nullptr) delete root;
  }

  void deleteNode(KDTreeNode* node) {
    if (node != nullptr) delete node;
  }

  void createTree(std::vector<Point<D> > points, KDTreeNode* treeRoot) {
    if (points.size() > 1) {
      std::sort(points.begin(), points.end(),
                [treeRoot](const Point<D>& a, const Point<D>& b) {
                  return a[treeRoot->axis] < b[treeRoot->axis];
                });
      int middleIndex = (points.size() / 2);
      treeRoot->value = points[middleIndex][treeRoot->axis];
      int axis = (treeRoot->axis + 1) % D;
      treeRoot->left = new KDTreeNode{axis};
      treeRoot->right = new KDTreeNode{axis};
      std::vector<Point<D> > leftPoints{points.begin(),
                                        points.begin() + middleIndex};
      std::vector<Point<D> > rightPoints{points.begin() + middleIndex,
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

  Point<D> nns(const Point<D>& point) {
    double infinity = DBL_MAX;
    Point<D> nearestNeighbor{};
    nnsRecurse(point, root, infinity, nearestNeighbor);
    return nearestNeighbor;
  }

  void nnsRecurse(const Point<D>& point, KDTreeNode* node, double& radius,
                  Point<D>& nearestNeighbor) {
    if (node == nullptr) return;
    if (node->isLeaf()) {
      double pointsDistance = distance(point, node->point);
      if (radius > pointsDistance) {
        radius = pointsDistance;
        nearestNeighbor = node->point;
      }
    } else {
      // Check if hypersphere includes hyperplane
      if (distance(point, node->value, node->axis) < radius) {
        if (point[node->axis] < node->value) {
          nnsRecurse(point, node->left, radius, nearestNeighbor);
          nnsRecurse(point, node->right, radius, nearestNeighbor);
        } else {
          nnsRecurse(point, node->right, radius, nearestNeighbor);
          nnsRecurse(point, node->left, radius, nearestNeighbor);
        }
      }
    }
  }
};

#endif
