#include <vector>
#include <algorithm>

class KDTree{
private:
    class KDTreeNode{
    public:
	std::vector<int> point;
	// bool isLeaf = false;
	int axis;
	int value;
	KDTreeNode * left;
	KDTreeNode * right;
	KDTreeNode(){
	    left = nullptr;
	    right = nullptr;
	}
    };
public:
    int dimensions;
    KDTreeNode * root;
    KDTree(std::vector<std::vector<int> > points, int dimensions);
    void createTree(std::vector<std::vector<int> > points, KDTreeNode * treeRoot);
};
