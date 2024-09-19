#pragma once
#include "common.h"
#include <cassert>
#include <cmath>
#include <ostream>

template <typename scalar_t = double_t>
struct vec3_t {
    using vec_t = vec3_t<scalar_t>;
    scalar_t x, y, z;
    constexpr vec_t operator+(const vec_t p) const {
        return { x + p.x, y + p.y, z + p.z };
    }
    constexpr vec_t operator-(const vec_t p) const {
        return { x - p.x, y - p.y, z - p.z };
    }
    constexpr vec_t operator-() const {
        return { -x, -y, -z };
    }
    constexpr vec_t operator*(scalar_t k) const {
        return { x * k, y * k, z * k };
    }
    constexpr vec_t operator/(scalar_t k) const {
        return { x / k, y / k, z / k };
    }
    constexpr scalar_t operator%(const vec_t p) const {
        return x * p.x + y * p.y + z * p.z;
    }
    constexpr vec_t operator*(const vec_t p) const {
        return { y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x };
    }
    constexpr bool operator==(const vec_t other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    constexpr scalar_t length_squared() const {
        return *this % *this;
    }
    constexpr scalar_t length() const {
        return std::sqrt(length_squared());
    }
    constexpr scalar_t distance(const vec_t p) const {
        return (*this - p).length();
    }
    constexpr scalar_t distance(const vec_t A, const vec_t B) const {
        assert(!(B - A).is_zero());
        return ((*this - A) * (*this - B)).length() / A.distance(B);
    }
    constexpr scalar_t signed_distance(const vec_t A, const vec_t B, const vec_t C) const {
        const vec_t N{ (B - A) * (C - A) };
        const auto D{ A % N };
        return (*this % N - D) / N.length();
    }
    constexpr vec_t normalize(scalar_t k = 1) const {
        assert(!is_zero());
        return (*this) * (k / length());
    }
    constexpr vec_t get_projection(const vec_t A, const vec_t B) const {
        const vec_t v{ B - A };
        return A + v.normalize((v % (*this - A)) / v.length());
    }
    constexpr vec_t rotate(const vec_t normal) const {
        // normal must have length 1 and be orthogonal to the vector
        assert(std::abs(normal.length_squared() - 1) <= EPS<scalar_t>);
        return *this * normal;
    }
    constexpr vec_t rotate(scalar_t alpha, const vec_t normal) const {
        return *this * cos(alpha) + rotate(normal) * sin(alpha);
    }
    constexpr vec_t rotate_around_point(const vec_t O, const vec_t axe, scalar_t alpha) const {
        const vec_t Z{ axe.normalize(axe % (*this - O)) };
        return O + Z + (*this - O - Z).rotate(alpha, O);
    }
    constexpr bool is_zero() const {
        return std::abs(x) <= EPS<scalar_t> && std::abs(y) <= EPS<scalar_t> && std::abs(z) <= EPS<scalar_t>;
    }
    constexpr scalar_t get_angle() const {
        return atan2(y, x);
    }
    constexpr scalar_t get_angle(const vec_t u) const {
        return atan2((*this * u).length(), *this % u);
    }
};


template <typename T = double_t>
std::ostream &operator<<(std::ostream &outs, const vec3_t<T> &p) {
    outs << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return outs;
}

template <typename T = double_t>
constexpr double mixed_product(const vec3_t<T> a, const vec3_t<T> b, const vec3_t<T> c) {
    // The (signed) volume of the parallelepiped defined by the three vectors given.
    return a % (b * c);
}
