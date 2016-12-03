#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <cmath>
#include <initializer_list>

template <size_t D>
struct Point {
  Point(std::initializer_list<double> v) {
    size_t i = 0;
    for (auto e : v) {
      coordinates_[i++] = e;
    }
  }

  double operator[](size_t dimension) { return coordinates_[dimension]; }
  double distance(const Point& other) { return distance(*this, other); }

  std::array<double, D> coordinates_;
};

template <size_t D>
double distance(const Point<D>& lhs, const Point<D>& rhs) {
  double dist = 0;
  for (size_t i = 0; i < D; i++)
    dist += sqrt(abs(pow(2, lhs[i]) - pow(2, rhs[i])));
  return dist;
}

#endif  // POINT_HPP
