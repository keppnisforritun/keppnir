#pragma once
#include "common.h"
#include "vec3.h"

template <typename scalar_t = double_t>
struct line3_t {
    using vec_t = vec3_t<scalar_t>;
    using line_t = line3_t<scalar_t>;
    vec_t p, q;
    struct line_intersect_t {
        intersection_t hits;
        vec3_t<scalar_t> point;
    };
    line_intersect_t intersect(const line_t other) {
        if (abs((q - p) * (other.p - p) % (other.q - p)) > EPS<scalar_t>) {
            return { intersection_t::none, {} };
        }
        if (((p - q) * (other.p - other.q)).length() <= EPS<scalar_t>) {
            return { p.is_on_line(other.p, other.q) ? intersection_t::infinite : intersection_t::none, {} };
        }
        const vec_t normal{ ((p - q) * (other.p - q)).normalize() };
        const double s1{ (other.p - p) * (other.q - p) % normal };
        return { intersection_t::one, p + ((q - p) / (s1 + ((other.q - q) * (other.p - q) % normal))) * s1 };
    }
    constexpr vec_t direction() const {
        return q - p;
    }
    constexpr bool contains(const vec_t point) const {
        return ((p - point) * (q - point)).is_zero();
    }
    constexpr bool segment_contains(const vec_t point) const {
        return is_on_line(point) && ((p - point) % (q - point)) <= EPS<scalar_t>;
    }
    constexpr bool segment_contains_strictly(const vec_t point) const {
        return is_on_line(point) && ((p - point) % (q - point)) <= -EPS<scalar_t>;
    }
};
