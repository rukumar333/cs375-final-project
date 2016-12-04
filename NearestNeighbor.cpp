#include "NearestNeighbor.hpp"

void run_tests() {
  auto cloud = generate_point_cloud<3>(10000, {-100.0, 100.0});
  auto v = makeDecorator(brute_force<3>)(cloud[0], cloud, 2);
  std::cout << "Closest points to " << cloud[0] << std::endl;
  for (auto e : v) {
    std::cout << e << std::endl;
  }
}
