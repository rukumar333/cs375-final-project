#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <utility>
#include <vector>
#include "KDTree.hpp"

template <typename>
struct Decorator;

void run_tests();

template <size_t D>
std::vector<Point<D>> generate_point_cloud(
    size_t number, const std::pair<double, double>& range) {
  std::random_device r;
  std::default_random_engine e1(r());
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
  auto it = std::find(neighbors.begin(), neighbors.end(), point);
  if (it != neighbors.end()) neighbors.erase(it);
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
