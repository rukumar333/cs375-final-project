#include "NearestNeighbor.hpp"

void run_tests() {
  auto cloud = generate_point_cloud<3>(10000, {-100.0, 100.0});
  std::cout << "---------- Brute Force Method ---------- " << std::endl;
  auto v = makeDecorator(brute_force<3>)(cloud[0], cloud, 2);
  std::cout << "Closest points to " << cloud[0] << std::endl;
  for (auto e : v) {
    std::cout << e << std::endl;
    std::cout << "Distance: " << distance(cloud[0], e) << std::endl;
  }
  std::cout << "---------- KD-Tree Method ---------- " << std::endl;
  auto nearestNeighbor = run_kd_test(cloud[0], cloud);
  std::cout << "Closest point to " << cloud[0] << std::endl;  
  std::cout << nearestNeighbor << std::endl;
  std::cout << "Distance: " << distance(cloud[0], nearestNeighbor) << std::endl;
}
