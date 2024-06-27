#include "../../include/bmp/Point2D.hpp"

Point2D::operator std::string() const {
    return "Point2D {" + std::to_string(x) + ", " + std::to_string(y) + "}";
}

bool Point2D::operator==(const Point2D &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Point2D::operator!=(const Point2D &rhs) const {
    return !(*this == rhs);
}

bool Point2D::operator<(const Point2D &rhs) const {
    return x < rhs.x && y < rhs.y;
}

bool Point2D::operator>(const Point2D &rhs) const {
    return x > rhs.x && y > rhs.y;
}

bool Point2D::operator<=(const Point2D &rhs) const {
    return x <= rhs.x && y <= rhs.y;
}

bool Point2D::operator>=(const Point2D &rhs) const {
    return x >= rhs.x && y >= rhs.y;
}

std::pair<Point2D, Point2D> arrangePointsCoordinates(const Point2D &point1, const Point2D &point2) {
    Point2D start{std::min(point1.x, point2.x),
                  std::min(point1.y, point2.y)};
    Point2D end{std::max(point1.x, point2.x),
                std::max(point1.y, point2.y)};
    return std::make_pair(start, end);
}
