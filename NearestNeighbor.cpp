#include "NearestNeighbor.hpp"

#define DIMENSION 6
#define NUM_POINTS 3e6

void run_tests() {
  std::cout << "# of points: " << NUM_POINTS << std::endl;
  auto cloud = generate_point_cloud<DIMENSION>(NUM_POINTS, {-100.0, 100.0});
  auto point = random_point<DIMENSION>({-100.0, 100.0});
  std::cout << "---------- Brute Force Method ---------- " << std::endl;
  auto v = makeDecorator(brute_force<DIMENSION>)(point, cloud, 1);
  std::cout << "Closest points to " << point << std::endl;
  for (auto e : v) {
    std::cout << e << std::endl;
    std::cout << "Distance: " << distance(point, e) << std::endl;
  }
  std::cout << "---------- KD-Tree Method ---------- " << std::endl;
  std::cout << "> Constructing tree..." << std::endl;
  auto kdTree = makeDecorator(initialize_kd_tree<DIMENSION>)(cloud);
  std::cout << "> Running NNS algorithm..." << std::endl;
  auto nearestNeighbor = makeDecorator(kd_tree_nns<DIMENSION>)(point, kdTree);
  std::cout << "Closest point to " << point << std::endl;
  std::cout << nearestNeighbor << std::endl;
  std::cout << "Distance: " << distance(point, nearestNeighbor) << std::endl;
}
