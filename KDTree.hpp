#include <vector>
#include <algorithm>

class KDTree{
private:
    class KDTreeNode{
	std::vector<int> point;
	// bool isLeaf = false;
	int axis;
	int value;
	KDTreeNode * left;
	KDTreeNode * right;
    };
public:
    int dimensions;
    KDTreeNode * root;
    KDTreeNode(std::vector<std::vector<int> > points, int dimensions);
    void createTree(std::vector<std::vector<int> > points, KDTreeNode * treeRoot);
};
