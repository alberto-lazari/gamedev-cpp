#include <iostream>
#include <format>

/**
 * A 2D point:
 *   |
 * y |  *
 *   |
 * --+-------
 *   |  x
 */
struct point {
  double x;
  double y;
};

/**
 * A 2D box, identified by 2 unordered points:
 *  |
 *  | origin
 *  |   *-----+
 *  |   |     |
 *  |   +-----*
 *  |        end
 * -+-----------
 *  |
 *
 * Warning: `origin` and `end` could be swapped:
 *  |
 *  |  end
 *  |   *-----+
 *  |   |     |
 *  |   +-----*
 *  |      origin
 * -+-----------
 *  |
 */
struct box {
  point origin;
  point end;
};

/**
 * Return minimum between `a` and `b`
 */
double min(double a, double b) {
  return a < b ? a : b;
}

/**
 * Return maximum between `a` and `b`
 */
double max(double a, double b) {
  return a > b ? a : b;
}

/**
 * Returns true iff `p` is within range [`a`, `b`]
 * Ex:
 * p in in range:
 *   a    p      b
 *   *----*------*
 *   a          p b
 *   *-----------*
 *
 * p is not in range:
 *   a           b    p
 *   *-----------*    *
 *   p     a           b
 *   *     *-----------*
 */
bool is_in_range(double a, double b, double p) {
  return min(a, b) <= p && p <= max(a, b);
}

bool isInside(
    double x0, double y0,
    double x1, double y1,
    double xp, double yp
) {
  return is_in_range(x0, x1, xp) && is_in_range(y0, y1, yp);
}

/**
 * Returns true iff `p` is a point inside box `b`:
 *
 * origin
 *   *-----+   p1 (not inside)
 *   | p   |   *
 *   | *   |
 *   |     |
 *   +-----*
 *        end
 *
 * Mind that `b` `origin` and `end` could be swapped:
 *
 * end
 *   *-----+
 *   | p   |
 *   | *   |
 *   |     |
 *   +-----*
 *       origin
 */
bool is_inside(const box& b, const point& p) {
  return isInside(b.origin.x, b.origin.y, b.end.x, b.end.y, p.x, p.y);
}

/**
 * Read a point from x, y coordinates from stdin
 */
point read_point() {
  double x;
  double y;
  std::cin >> x;
  std::cin >> y;
  return point(x, y);
}

box read_box() {
  return box(read_point(), read_point());
}

bool is_same_pixel(double a, double b) {
  return (int) a == (int) b;
}

void pretty_print(const box& b, const point& p) {
  const double min_x = min(min(b.origin.x, b.end.x), p.x);
  const double max_x = max(max(b.origin.x, b.end.x), p.x);
  const double min_y = min(min(b.origin.y, b.end.y), p.y);
  const double max_y = max(max(b.origin.y, b.end.y), p.y);

  for (double row = max_y; row >= min_y; --row) {
    for (double col = min_x; col <= max_x; ++col) {
      const bool is_vedge = is_in_range(b.origin.y, b.end.y, row)
        && ( is_same_pixel(col, b.origin.x) || is_same_pixel(col, b.end.x) );
      const bool is_hedge = is_in_range(b.origin.x, b.end.x, col)
        && ( is_same_pixel(row, b.origin.y) || is_same_pixel(row, b.end.y) );
      const bool is_point = is_same_pixel(col, p.x) && is_same_pixel(row, p.y);
      const char pixel = is_point ? '*'
        : is_vedge ? (is_hedge ? '+' : '|')
        : is_hedge ? '-'
        : ' ';
      std::cout << pixel;
    }
    std::cout << std::endl;
  }
}

int main() {
  const box b = read_box();
  std::cout << std::format("B = origin: ({}, {}), end: ({}, {})",
      b.origin.x, b.origin.y,
      b.end.x, b.end.y
  ) << std::endl;

  const point p = read_point();
  std::cout << std::format("P = ({}, {})", p.x, p.y) << std::endl;

  pretty_print(b, p);

  const bool inside = is_inside(b, p);
  std::cout << std::format("\nP {} inside B", (inside ? "is" : "is not")) << std::endl;

  // Return error code 1 if point is not inside box
  return inside ? 0 : 1;
}