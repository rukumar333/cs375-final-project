#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <utility>
#include <vector>
#include "KDTree.hpp"

static std::random_device rand_dev;

template <typename>
struct Decorator;

void run_tests();

/*
 * For creating a single point.
 * Not used in generate_point_cloud because of efficiency
 */
template <size_t D>
Point<D> random_point(const std::pair<double, double>& range) {
  std::default_random_engine e1(rand_dev());
  std::uniform_real_distribution<double> uniform_dist{range.first,
                                                      range.second};
  std::array<double, D> components;
  for (size_t j = 0; j < D; j++) {
    components[j] = uniform_dist(e1);
  }
  return Point<D>{components};
}

template <size_t D>
std::vector<Point<D>> generate_point_cloud(
    size_t number, const std::pair<double, double>& range) {
  std::default_random_engine e1(rand_dev());
  std::uniform_real_distribution<double> uniform_dist{range.first,
                                                      range.second};
  std::vector<Point<D>> ret;
  for (size_t i = 0; i < number; i++) {
    std::array<double, D> components;
    for (size_t j = 0; j < D; j++) {
      components[j] = uniform_dist(e1);
    }
    ret.emplace_back(components);
  }
  return ret;
}

template <size_t D>
std::vector<Point<D>> brute_force(const Point<D>& point,
                                  std::vector<Point<D>> neighbors, size_t num) {
  std::vector<Point<D>> nearest;
  for (size_t i = 0; i < num; i++) {
    auto neighbor =
        std::min_element(neighbors.begin(), neighbors.end(),
                         [point](const Point<D>& lhs, const Point<D>& rhs) {
                           return distance(point, lhs) < distance(point, rhs);
                         });
    nearest.push_back(*neighbor);
    neighbors.erase(neighbor);
  }
  return nearest;
}

template <size_t D>
Point<D> kd_tree_nns(const Point<D>& point, KDTree<D>& kdTree) {
  return kdTree.nns(point);
}

template <size_t D>
KDTree<D> initialize_kd_tree(const std::vector<Point<D>>& neighbors) {
  return KDTree<D>{neighbors};
}

template <size_t D>
Point<D> kd_nearest_neighbor(const Point<D>& point, const KDTree<D>& kdTree) {
  Point<D> nearestNeighbor = kd_tree_nns(point, kdTree);
  return nearestNeighbor;
}

/* http://stackoverflow.com/questions/30679445/python-like-c-decorators */
template <typename R, typename... Args>
struct Decorator<R(Args...)> {
  Decorator(std::function<R(Args...)> f) : f_(f) {}

  R operator()(Args... args) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    R ret = f_(args...);
    end = std::chrono::system_clock::now();
    std::chrono::nanoseconds elapsed_nanos =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Execution took " << elapsed_nanos.count() << "ns"
              << std::endl;
    return ret;
  }
  std::function<R(Args...)> f_;
};

template <typename R, typename... Args>
Decorator<R(Args...)> makeDecorator(R (*f)(Args...)) {
  return Decorator<R(Args...)>(std::function<R(Args...)>(f));
}
