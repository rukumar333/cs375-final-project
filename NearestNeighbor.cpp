#include "NearestNeighbor.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

#define DIMENSION 3
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

  std::ofstream file{"results.csv"};
  if (!file.is_open()) throw std::runtime_error{"Unable to open file"};
  file << "Points,Construction Time (ns),NNS Time (ns)" << std::endl;
  file << std::fixed;
  for (int i = 0; i < 8; i++) {
    std::cout << "10^" << i << " points" << std::endl;
    cloud = generate_point_cloud<DIMENSION>(pow(10, i), {-100.0, 100.0});
    point = random_point<DIMENSION>({-100.0, 100.0});
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    initialize_kd_tree<DIMENSION>(cloud);
    end = std::chrono::system_clock::now();
    std::chrono::nanoseconds kd_time = end - start;

    start = std::chrono::system_clock::now();
    kd_tree_nns<DIMENSION>(point, kdTree);
    end = std::chrono::system_clock::now();
    std::chrono::nanoseconds nns_time = end - start;
    file << static_cast<int>(pow(10, i)) << "," << kd_time.count() << ","
         << nns_time.count() << std::endl;
  }
}
