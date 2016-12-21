#ifndef KDTREE_HPP_
#define KDTREE_HPP_

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
    KDTreeNode(size_t axis) : KDTreeNode{axis, 0} {}
    KDTreeNode(size_t axis, double value)
        : KDTreeNode{{}, axis, value, nullptr, nullptr} {}
    KDTreeNode(size_t axis, Point<D> point)
        : KDTreeNode{point, axis, point[axis], nullptr, nullptr} {}
    KDTreeNode(const Point<D>& point, size_t axis, double value,
               KDTreeNode* left, KDTreeNode* right)
        : point_{point},
          axis_{axis},
          value_{value},
          left_{left},
          right_{right} {}
    /**
     * Deep destructor
     */
    ~KDTreeNode() {
      if (left_ != nullptr) delete left_;
      if (right_ != nullptr) delete right_;
    }
    bool isLeaf() const { return left_ == nullptr && right_ == nullptr; }
    Point<D> point_;
    size_t axis_;
    double value_;
    KDTreeNode* left_;
    KDTreeNode* right_;
  };

 public:
  KDTreeNode* root;

  KDTree(std::vector<Point<D>> points) : root{createTree(points, 0)} {}
  ~KDTree() {
    if (root != nullptr) delete root;
  }

  void deleteNode(KDTreeNode* node) {
    if (node != nullptr) delete node;
  }

  KDTreeNode* createTree(std::vector<Point<D>> points, size_t depth) {
    size_t axis = depth % D;
    std::sort(points.begin(), points.end(),
              [axis](const Point<D>& a, const Point<D>& b) {
                return a[axis] < b[axis];
              });
    if (points.size() == 1) {
      return new KDTreeNode{axis, points[0]};
    } else if (points.size() < 1) {
      return nullptr;
    }
    size_t middleIndex = points.size() / 2;  // For indexing points
    int midInc = middleIndex;                // For adding to iterator
    KDTreeNode* node = new KDTreeNode{axis, points[middleIndex]};
    node->left_ =
        createTree({points.begin(), points.begin() + midInc}, depth + 1);
    node->right_ =
        createTree({points.begin() + midInc, points.end()}, depth + 1);
    return node;
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
      double pointsDistance = distance(point, node->point_);
      if (radius > pointsDistance) {
        radius = pointsDistance;
        nearestNeighbor = node->point_;
      }
      return;
    }
    if (point[node->axis_] < node->value_) {
      nnsRecurse(point, node->left_, radius, nearestNeighbor);
      if (radius == DBL_MAX || point[node->axis_] + radius >= node->value_) {
        nnsRecurse(point, node->right_, radius, nearestNeighbor);
      }
    } else {
      nnsRecurse(point, node->right_, radius, nearestNeighbor);
      if (radius == DBL_MAX || point[node->axis_] - radius < node->value_) {
        nnsRecurse(point, node->left_, radius, nearestNeighbor);
      }
    }
  }
};

#endif  // KDTREE_HPP_
