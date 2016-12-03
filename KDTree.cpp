#include <iostream>
#include "KDTree.hpp"

KDTree::KDTree(std::vector<std::vector<int> > points, int dimensions){
    this->dimensions = dimensions;
    root = new KDTreeNode();
    root->axis = 0;
    createTree(points, root);
}

void KDTree::createTree(std::vector<std::vector<int> > points, KDTreeNode * treeRoot){
    
}
