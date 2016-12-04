#include <algorithm>
#include <functional>
#include <vector>
#include "KDTree.hpp"

void run_tests();

template <size_t D>
std::vector<Point<D>> brute_force(const Point<D>& point,
                                  std::vector<Point<D>> neighbors, size_t num) {
  auto it = std::find(neighbors.begin(), neighbors.end(), point);
  if (it != neighbors.end()) neighbors.erase(it);
  std::vector<Point<D>> nearest;
  for (size_t i = 0; i < num; i++) {
    auto neighbor =
        std::min_element(neighbors.begin(), neighbors.end(),
                         [point](const Point<D> lhs, const Point<D> rhs) {
                           return distance(point, lhs) < distance(point, rhs);
                         });
    nearest.push_back(*neighbor);
    neighbors.erase(neighbor);
  }
  return nearest;
}

template <typename>
struct Decorator;

template <typename R, typename... Args>
struct Decorator<R(Args...)> {
  Decorator(std::function<R(Args...)> f) : f_(f) {}

  R operator()(Args... args) {
    std::cout << "Calling the decorated function.\n";
    return f_(args...);
  }
  std::function<R(Args...)> f_;
};

template <typename R, typename... Args>
Decorator<R(Args...)> makeDecorator(R (*f)(Args...)) {
  return Decorator<R(Args...)>(std::function<R(Args...)>(f));
}
