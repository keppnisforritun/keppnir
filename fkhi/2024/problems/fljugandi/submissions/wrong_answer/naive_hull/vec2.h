#pragma once
#include "common.h"
#include <cmath>

template <typename scalar_t = double_t>
struct vec2_t {
    scalar_t x, y;
    constexpr vec2_t operator+(const vec2_t p) const {
        return { x + p.x, y + p.y };
    }
    constexpr vec2_t operator-(const vec2_t p) const {
        return { x - p.x, y - p.y };
    }
    constexpr vec2_t operator-() const {
        return { -x, -y };
    }
    constexpr vec2_t operator*(scalar_t k) const {
        return { x * k, y * k };
    }
    constexpr vec2_t operator/(scalar_t k) const {
        return { x / k, y / k };
    }
    constexpr scalar_t operator%(const vec2_t p) const {
        return x * p.x + y * p.y;
    }
    constexpr scalar_t operator*(const vec2_t p) const {
        return x * p.y - y * p.x;
    }
    constexpr bool operator==(const vec2_t other) const {
        return x == other.x && y == other.y;
    }
    constexpr scalar_t length_squared() const {
        return *this % *this;
    }
    constexpr scalar_t length() const {
        return std::sqrt(length_squared());
    }
    constexpr scalar_t distance(const vec2_t p) const {
        return (*this - p).length();
    }
    constexpr scalar_t distance_squared(const vec2_t p) const {
        return (*this - p).length_squared();
    }
    constexpr scalar_t ccw(const vec2_t a, const vec2_t b) const {
        return (a - *this) * (b - a);
    }
    constexpr bool collinear(const vec2_t a, const vec2_t b) const {
        return abs(ccw(a, b)) <= EPS<scalar_t>;
    }
    constexpr intx progress(const vec2_t a, const vec2_t b) const {
        return (abs(a.x - b.x) <= EPS<scalar_t>) ? (y - a.y) / (b.y - a.y) : (x - a.x) / (b.x - a.x);
    }
};

template <typename T = double_t>
std::ostream &operator<<(std::ostream &outs, const vec2_t<T> &p) {
    outs << "(" << p.x << ", " << p.y << ")";
    return outs;
}
