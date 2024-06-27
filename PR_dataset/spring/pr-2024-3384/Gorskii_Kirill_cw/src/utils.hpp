#ifndef CW_UTILS_HPP
#define CW_UTILS_HPP

#include <cstdint>
#include <cmath>

template<typename T>
struct vec2
{
    T x, y;

    vec2() {}
    vec2(T x, T y) : x(x), y(y) {}

    inline void operator+=(vec2 a) { x += a.x; y += a.y; }
    inline void operator-=(vec2 a) { x -= a.x; y -= a.y; }
    inline void operator*=(T a)    { x *= a;   y *= a;   }
    inline void operator/=(T a)    { x /= a;   y /= a;   }

    inline vec2 operator+(vec2 a)  { return { x + a.x, y + a.y }; }
    inline vec2 operator-(vec2 a)  { return { x - a.x, y - a.y }; }
    inline vec2 operator*(T a)     { return { x * a,   y * a}; } 
    inline vec2 operator/(T a)     { return { x / a,   y / a}; }

    inline vec2 operator-()        { return { -x, -y }; }

    inline T len() { return std::sqrt(x*x + y*y); }
    inline T cross_z(vec2<T> b) { return b.y * x - b.x * y; }

    template<typename TO>
    inline operator vec2<TO>() { return { TO(x), TO(y) }; }
    
};

typedef vec2<float> vec2f;
typedef vec2<int> vec2i;

union rgba32
{
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    uint32_t i32;

    rgba32() {}
    rgba32(uint32_t i32) : i32(i32) {}
    rgba32(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : r(r), g(g), b(b), a(a) {}

    bool operator==(rgba32 b) { return this->i32 == b.i32; }
    bool operator!=(rgba32 b) { return this->i32 != b.i32; }
};

struct rgb24
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    rgb24() {}
    rgb24(uint8_t r, uint8_t g, uint8_t b)
        : r(r), g(g), b(b) {}
};

template<typename T>
struct rect2 {
    vec2<T> min;
    vec2<T> max;

    rect2() {}
    rect2(vec2<T> min, vec2<T> max) : min(min), max(max) {}

    inline T area() { return (max.x - min.x) * (max.y - min.y); }
    inline void operator+=(vec2<T> a) { min += a; max += a; }
    inline rect2 operator+(vec2<T> a) { return { min + a, max + a }; }
};

typedef rect2<float> rect2f;
typedef rect2<int>   rect2i;

#endif