#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>

template <size_t D>
struct Point;
template <size_t D>
double distance(const Point<D>&, const Point<D>&);

template <size_t D>
struct Point {
  Point(std::initializer_list<double> v) {
    size_t i = 0;
    for (auto e : v) {
      coordinates_[i++] = e;
    }
  }

  double operator[](size_t dimension) const { return coordinates_[dimension]; }
  std::array<double, D> coordinates_;
};

/*
 * Finds euclidian distance between two Point classes of same dimension
 */
template <size_t D>
double distance(const Point<D>& lhs, const Point<D>& rhs) {
  double dist = 0;
  for (size_t i = 0; i < D; i++)
    dist += sqrt(std::abs(pow(2, lhs[i]) - pow(2, rhs[i])));
  return dist;
}

/*
 * Print the point components of a Point in ascending order.
 * Prints in the form {x, y, z} with no newline.
 */
template <size_t D>
std::ostream& operator<<(std::ostream& os, const Point<D>& point) {
  os << "{";
  for (size_t i = 0; i < D - 1; i++) {
    os << point[i] << ", ";
  }
  os << point[D - 1] << "}";
  return os;
}

template <size_t D>
bool operator==(const Point<D>& lhs, const Point<D>& rhs) {
  return lhs.coordinates_ == rhs.coordinates_;
}

namespace std {
/*
 * Make our Point class hashable
 */
template <size_t D>
struct hash<Point<D>> {
  size_t operator()(const Point<D>& x) const {
    /* your code here, e.g. "return hash<int>()(x.value);" */
    return hash<array<double, D>>()(x.coordinates_);
  }
};

/*
 * Also make it swappable for sorting
 */
template <size_t D>
void swap(Point<D>& lhs, Point<D>& rhs) {
  swap(lhs.coordinates_, rhs.coordinates_);
}
}

#endif  // POINT_HPP
