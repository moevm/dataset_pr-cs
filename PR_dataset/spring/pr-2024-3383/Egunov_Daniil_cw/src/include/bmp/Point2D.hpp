#ifndef BMP_POINT2D_HPP
#define BMP_POINT2D_HPP

#include <cstdint>
#include <string>

struct Point2D {
    int64_t x;
    int64_t y;

    Point2D() : x(0), y(0) {}

    Point2D(int64_t x, int64_t y) : x(x), y(y) {}

    ~Point2D() = default;

    explicit operator std::string() const;

    friend std::pair<Point2D, Point2D> arrangePointsCoordinates(const Point2D &point1, const Point2D &point2);

    bool operator==(const Point2D &rhs) const;

    bool operator!=(const Point2D &rhs) const;

    bool operator<(const Point2D &rhs) const;

    bool operator>(const Point2D &rhs) const;

    bool operator<=(const Point2D &rhs) const;

    bool operator>=(const Point2D &rhs) const;
};


#endif //BMP_POINT2D_HPP
