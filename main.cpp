#include <vector>
#include "KDTree.hpp"

int main() {
  std::vector<std::vector<int> > points = {
      {3, 1, 4}, {2, 3, 7}, {4, 3, 4}, {2, 1, 3}, {2, 4, 5}, {6, 1, 4},
      {1, 4, 4}, {0, 5, 7}, {5, 2, 5}, {4, 0, 6}, {7, 1, 6}};
  KDTree kdTree{points, 3};
  return 0;
}
