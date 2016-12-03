#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>

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

template <size_t D>
std::ostream& operator<<(std::ostream& os, const Point<D>& point) {
  os << "{";
  for (size_t i = 0; i < D - 1; i++) {
    os << point[i] << ", ";
  }
  os << point[D - 1] << "}";
  return os;
}

/*
 * Make our Point class hashable
 */
namespace std {
template <size_t D>
struct hash<Point<D>> {
  size_t operator()(const Point<D>& x) const {
    /* your code here, e.g. "return hash<int>()(x.value);" */
    return hash<array<double, D>>()(x.coordinates_);
  }
};
}

#endif  // POINT_HPP
