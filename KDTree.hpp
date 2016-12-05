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
    KDTreeNode(int axis, Point<D> point)
        : KDTreeNode{point, axis, point[axis], nullptr, nullptr} {}
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

  KDTree(std::vector<Point<D>> points) : root{createTree(points, 0)} {}

    ~KDTree() {
	if (root != nullptr) delete root;
    }

    void deleteNode(KDTreeNode* node) {
	if (node != nullptr) delete node;
    }

  KDTreeNode* createTree(std::vector<Point<D>> points, int depth) {
    int axis = depth % D;
    std::sort(points.begin(), points.end(),
              [axis](const Point<D>& a, const Point<D>& b) {
                return a[axis] < b[axis];
              });
    if (points.size() == 1) {
      return new KDTreeNode{axis, points[0]};
    } else if (points.size() < 1) {
      return nullptr;
    }
    size_t middleIndex = points.size() / 2;
    KDTreeNode* node = new KDTreeNode{axis, points[middleIndex]};
    node->point = points[middleIndex];
    node->left =
        createTree({points.begin(), points.begin() + middleIndex}, depth + 1);
    node->right =
        createTree({points.begin() + middleIndex, points.end()}, depth + 1);
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
	    double pointsDistance = distance(point, node->point);
	    if (radius > pointsDistance) {
		radius = pointsDistance;
		nearestNeighbor = node->point;
	    }
	} else {
	    if (point[node->axis] < node->value) {
		nnsRecurse(point, node->left, radius, nearestNeighbor);
		if(radius == DBL_MAX || point[node->axis] + radius >= node->value){
		    nnsRecurse(point, node->right, radius, nearestNeighbor);   
		}
	    } else {
		nnsRecurse(point, node->right, radius, nearestNeighbor);
		if(radius == DBL_MAX || point[node->axis] - radius < node->value){		    
		    nnsRecurse(point, node->left, radius, nearestNeighbor);
		}
	    }
	}
    }
};

#endif

//{-36.8033, -27.1832, 88.0916}
